/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#include "layer_LeakyRelu.hpp"

namespace bmnet {

/*
 * dump
 */
void LeakyReluLayerPlugin::dump() {
  LOG(INFO) << layer_.type() << " param:";
}

void LeakyReluLayerPlugin::setup(TensorOp* op) {
  CustomizedCaffeLayer::setup(op);
  TGCustomizedParameter* param = op->mutable_tg_customized_param();
  param->set_sub_type("leakyrelu");
}

void LeakyReluLayerPlugin::codegen(TensorOp *op) {
  // This is an example of overwriting existing layer.
  // Orignally Relu runs on TPU, but here we changed to CPU.

  // get input shape
  const TensorShape & input_shape = op->input_shape(0);

  // get parameter from caffe proto
  const caffe::ReLUParameter &in_param = layer_.relu_param();
  float negative_slope = in_param.negative_slope();

  // set normal output shape
  TensorShape *output_shape = op->add_output_shape();
  output_shape->CopyFrom(input_shape);
  output_shape->set_data_type_size(sizeof(int8_t));

  // set out_param
  TGCustomizedParameter* out_param = op->mutable_tg_customized_param();
  out_param->add_f32_param(negative_slope);
}

} // end namespace of bmnet.
