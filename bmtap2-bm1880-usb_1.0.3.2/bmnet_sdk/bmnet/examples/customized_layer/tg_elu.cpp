/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#include <bmnet/utils/common.hpp>
#include <bmnet/targets/cpu/cpu.hpp>
#include "tg_elu.hpp"

namespace bmnet {

void TGEluFixedInst::dump() {
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

void TGEluFixedInst::compute() {
  const TGCustomizedParameter& param = op_.tg_customized_param();
  if (op_.input_shape(0).data_type_size() == sizeof(int8_t)) {
    op_.add_threshold_x(m_inputCalibrationParameter[0].blob_param(0).threshold_y());
  }
  if (op_.output_shape(0).data_type_size() == sizeof(int8_t)) {
    op_.add_threshold_y(m_calibrationParameter.blob_param(0).threshold_y());
  }
  add_cpu_op(_ctx->bm_get_bmk(),"ELU", op_);
}
} // end namespace of bmnet.
