/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#include <bmnet/utils/common.hpp>
#include <bmnet/targets/Target.hpp>
#include <bmnet/targets/cpu/cpu.hpp>
#include <bmnet/targets/plat-bm168x/LIR/lir.hpp>
#include "tg_elu.hpp"

namespace bmnet {

#define NPU_SHIFT (ctx_->hw.npu_shift)
#define EU_SHIFT (ctx_->hw.eu_shift)
#define LOCAL_MEM_ADDRWIDTH (ctx_->hw.local_mem_shift)
#define LOCAL_MEM_BANKS (ctx_->hw.local_mem_banks)
#define NPU_NUM (1 << NPU_SHIFT)
#define EU_NUM (1 << EU_SHIFT)
#define LOCAL_MEM_SIZE (1 << LOCAL_MEM_ADDRWIDTH)

void TGEluPluginInst::dump() {
  std::cout << op_.type() << " param:"<< std::endl;

  const TGCustomizedParameter& param = op_.tg_customized_param();
  const TensorShape& input_shape = op_.input_shape(0);
  const TensorShape& output_shape = op_.output_shape(0);
  float alpha = param.f32_param(0);

  std::cout << " input_shape " << DumpShape(input_shape)
            << " output_shape " << DumpShape(output_shape)
            << "  input " << op_.global_input(0)
            << ", output " << op_.global_output(0)
            << ", alpha " << alpha
            << std::endl;
}

void TGEluPluginInst::compute() {
  char *run_use_cpu = getenv("ELU_RUN_ON_CPU");
  if (run_use_cpu) {
    cpu_forward();
  } else {
    npu_forward();
  }
}

void TGEluPluginInst::cpu_forward() {
  add_cpu_op("ELU", op_);
}

void TGEluPluginInst::npu_forward() {
  const TGCustomizedParameter& param = op_.tg_customized_param();
  const TensorShape& input_shape = op_.input_shape(0);
  float alpha = param.f32_param(0);

  gaddr_t bottom_gaddr     = op_.global_input(0) + get_global_neuron_base();
  gaddr_t top_gaddr    = op_.global_output(0) + get_global_neuron_base();

  int input_n, input_c, input_h, input_w;

  if (input_shape.dim_size() == 2) {
    input_n = 1;
    input_c = 1;
    input_h = input_shape.dim(0);
    input_w = input_shape.dim(1);
  } else if (input_shape.dim_size() == 4) {
    input_n = input_shape.dim(0);
    input_c = input_shape.dim(1);
    input_h = input_shape.dim(2);
    input_w = input_shape.dim(3);
  } else {
    assert(0);
  }

  gaddr_t slice_bottom_gaddr    = bottom_gaddr;
  gaddr_t slice_top_gaddr       = top_gaddr;
  int count                     = input_n * input_c * input_h * input_w;
  int slice_num                 = get_slice_num_element_wise(*ctx_, 2, count);

  for(int slice_idx = 0; slice_idx < slice_num; slice_idx++){
    int count_sec           = count / slice_num + (slice_idx < count % slice_num);

    shape_t input_shape     = shape_t1(count_sec);
    tensor_lmem * tl_bottom = bmk1682_tl_alloc(input_shape, FMT_F32, CTRL_AL);
    tensor_lmem * tl_top    = bmk1682_tl_alloc(input_shape, FMT_F32, CTRL_AL);
    tensor_lmem * tl_alpha  = bmk1682_tl_alloc_const(alpha);
    tensor_lmem * tl_zero   = bmk1682_tl_alloc_const(0.0);
    tensor_lmem * tl_one    = bmk1682_tl_alloc_const(1.0);

    // elu calculation
    tl_load(tl_bottom, slice_bottom_gaddr, CTRL_NULL);
    // y = math_max(x, 0) and r = math_min(x, 0)
    tl_cmp(tl_top, tl_bottom, tl_bottom, tl_zero, tl_zero, tl_bottom);
    // r = exp(r)
    tl_ex(tl_bottom, tl_bottom);
    // r = 1 - exp(r)
    tl_sub(tl_bottom, tl_bottom, tl_one, CTRL_NULL);
    // y = r*alpah + y
    tl_mul(tl_top, tl_bottom, tl_alpha, CTRL_RA);

    // store result back to global memory
    tl_store(tl_top, slice_top_gaddr, CTRL_NULL);

    slice_bottom_gaddr += count_sec * FLOAT_SIZE;
    slice_top_gaddr += count_sec * FLOAT_SIZE;

    bmk1682_tl_free(tl_one);
    bmk1682_tl_free(tl_zero);
    bmk1682_tl_free(tl_alpha);
    bmk1682_tl_free(tl_top);
    bmk1682_tl_free(tl_bottom);
  }
}

void TGEluPluginFixedInst::dump() {
  std::cout << op_.type() << " param:"<< std::endl;

  const TGCustomizedParameter& param = op_.tg_customized_param();
  const TensorShape& input_shape = op_.input_shape(0);
  const TensorShape& output_shape = op_.output_shape(0);
  float alpha = param.f32_param(0);

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
            << ", alpha " << alpha
            << std::endl;
}

void TGEluPluginFixedInst::compute() {
  const TGCustomizedParameter& param = op_.tg_customized_param();
  if (op_.input_shape(0).data_type_size() == sizeof(int8_t)) {
    op_.add_threshold_x(m_inputCalibrationParameter[0].blob_param(0).threshold_y());
  }
  if (op_.output_shape(0).data_type_size() == sizeof(int8_t)) {
    op_.add_threshold_y(m_calibrationParameter.blob_param(0).threshold_y());
  }
  add_cpu_op(ctx_, "ELU", op_);
}

} // end namespace of bmnet.
