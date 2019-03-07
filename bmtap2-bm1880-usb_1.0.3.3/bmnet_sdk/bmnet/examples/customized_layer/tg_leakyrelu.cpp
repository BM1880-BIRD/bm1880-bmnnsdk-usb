/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#include <bmnet/utils/common.hpp>
#include <bmnet/targets/Target.hpp>
#include <bmnet/targets/cpu/cpu.hpp>
#include "tg_leakyrelu.hpp"

namespace bmnet {

void TGLeakyReluFixedInst::dump() {
  std::cout << op_.type() << " param:"<< std::endl;

  const TGCustomizedParameter& param = op_.tg_customized_param();
  const TensorShape& input_shape = op_.input_shape(0);
  const TensorShape& output_shape = op_.output_shape(0);
  float negative_slope = param.f32_param(0);

  if (input_shape.dim_size() == 2) {
    std::cout << "  input_shape " << input_shape.dim(0) << " "
                                  << input_shape.dim(1) << " "
              << ", output_shape " << output_shape.dim(0) << " "
                                  << output_shape.dim(1) << " "
              << std::endl;
  } else {
    std::cout << "  input_shape " << input_shape.dim(0) << " "
                                  << input_shape.dim(1) << " "
                                  << input_shape.dim(2) << " "
                                  << input_shape.dim(3) << " "
              << ", output_shape " << output_shape.dim(0) << " "
                                  << output_shape.dim(1) << " "
                                  << output_shape.dim(2) << " "
                                  << output_shape.dim(3) << " "
              << std::endl;
  }
  std::cout << "  input " << op_.global_input(0)
            << ", output " << op_.global_output(0)
            << ", negative_slope " << negative_slope
            << std::endl;
}

void TGLeakyReluFixedInst::compute() {
#if 0
  const TGCustomizedParameter& param = op_.tg_customized_param();
  if (op_.input_shape(0).data_type_size() == sizeof(int8_t)) {
    op_.add_threshold_x(m_inputCalibrationParameter[0].blob_param(0).threshold_y());
  }
  if (op_.output_shape(0).data_type_size() == sizeof(int8_t)) {
    op_.add_threshold_y(m_calibrationParameter.blob_param(0).threshold_y());
  }
  add_cpu_op(_ctx->bm_get_bmk(),"LeakyRelu", op_);
#else
  const TGCustomizedParameter& param = op_.tg_customized_param();
  const TensorShape& input_shape = op_.input_shape(0);
  float negative_slope = param.f32_param(0);
  assert(negative_slope > 0);
  gaddr_t input_data_gaddr     = op_.global_input(0) + get_global_neuron_base();
  gaddr_t output_data_gaddr    = op_.global_output(0) + get_global_neuron_base();

  int n, c, h, w;

  if (input_shape.dim_size() == 2) {
    n = 1;
    c = 1;
    h = input_shape.dim(0);
    w = input_shape.dim(1);
  } else if (input_shape.dim_size() == 4) {
    n = input_shape.dim(0);
    c = input_shape.dim(1);
    h = input_shape.dim(2);
    w = input_shape.dim(3);
  } else {
    assert(0);
  }

  forward (
      input_data_gaddr,
      output_data_gaddr,
      n,
      c,
      h,
      w);
#endif
}

void TGLeakyReluFixedInst::forward(
    gaddr_t               bottom_gaddr,
    gaddr_t               top_gaddr,
    int                   input_n,
    int                   input_c,
    int                   input_h,
    int                   input_w)
{
  gaddr_t slice_bottom_gaddr    = bottom_gaddr;
  gaddr_t slice_top_gaddr       = top_gaddr;
  int count                     = input_n * input_c * input_h * input_w;
  int slice_num                 = get_slice_num_element_wise(*_ctx, 3, count + 1);

  int gt_right_shift_width = m_calibrationParameter.relu_param().gt_right_shift_width();
  int le_right_shift_width = m_calibrationParameter.relu_param().le_right_shift_width();
  int gt_scale = m_calibrationParameter.relu_param().gt_scale();
  int le_scale = m_calibrationParameter.relu_param().le_scale();

  for (int slice_idx = 0; slice_idx < slice_num; slice_idx++) {
      int count_sec = count / slice_num + (slice_idx < count % slice_num);
      // set shape
      shape_t input_shape = shape_t1(count_sec);
      tensor_lmem *bottom = _ctx->tl_alloc(input_shape, FMT_I8, CTRL_AL);
      tensor_lmem *relu = _ctx->tl_alloc(input_shape, FMT_I8, CTRL_AL);
      tensor_lmem *neg = _ctx->tl_alloc(input_shape, FMT_I8, CTRL_AL);

      // load
      _ctx->gdma_load(bottom, slice_bottom_gaddr, CTRL_NEURON);
      // 0. relu = relu(bottom)
      // 1. relu = (relu * GT_scale) >> GT_right_shift_width
      // 2. neg = neg(0, botom)
      // 3. neg (n,c,h,w) = (neg(n,c,h,w) * slope) >> LE_right_shift_width
      // 4. bottom = or relu, neg
      bmk1880_relu_param_t p13;
      p13.ofmap = relu;
      p13.ifmap = bottom;
      _ctx->tpu_relu(&p13);
      bmk1880_mul_const_param_t p;
      p.res_high = NULL;
      p.res_low = relu;
      p.a = relu;
      p.b = gt_scale;
      p.b_is_signed = true;
      p.rshift_width = gt_right_shift_width;
      _ctx->tpu_mul_const(&p);
      bmk1880_min_const_param_t p1;
      p1.min = neg;
      p1.a = bottom;
      p1.b = 0;
      p1.b_is_signed = 1;
      _ctx->tpu_min_const(&p1);
      p.res_high = NULL;
      p.res_low = neg;
      p.a = neg;
      p.b = le_scale;
      p.b_is_signed = true;
      p.rshift_width = le_right_shift_width;
      _ctx->tpu_mul_const(&p);
      bmk1880_or_int8_param_t p2;
      p2.res = bottom;
      p2.a = relu;
      p2.b = neg;
      _ctx->tpu_or_int8(&p2);
      //move result to global
      _ctx->gdma_store(bottom, slice_top_gaddr, CTRL_NEURON);
      //free
      _ctx->tl_free(neg);
      _ctx->tl_free(relu);
      _ctx->tl_free(bottom);

      slice_bottom_gaddr += count_sec * INT8_SIZE;
      slice_top_gaddr += count_sec * INT8_SIZE;
  }
}

} // end namespace of bmnet.
