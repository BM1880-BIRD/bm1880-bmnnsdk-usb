/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#include "layer_Elu.hpp"

namespace bmnet {

/*
 * dump
 */
void EluLayer::dump() {
  LOG(INFO) << layer_.type() << " param:";
}

void EluLayer::codegen(TensorOp *op) {
  // get input shape
  const TensorShape & input_shape = op->input_shape(0);

  // get parameter from caffe proto
  const caffe::ELUParameter &in_param = layer_.elu_param();
  float alpha = in_param.alpha();

  // set normal output shape
  TensorShape *output_shape = op->add_output_shape();
  output_shape->CopyFrom(input_shape);
  output_shape->set_data_type_size(sizeof(int8_t));
  // set out_param
  TGCustomizedParameter* out_param = op->mutable_tg_customized_param();
  out_param->add_f32_param(alpha);
}

} // end namespace of bmnet.
