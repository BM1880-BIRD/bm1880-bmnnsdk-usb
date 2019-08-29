/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#include "layer_Elu.hpp"
#include "yaml-cpp/yaml.h"

namespace bmnet {

/*
 * dump
 */
void EluLayerPlugin::dump() {
  LOG(INFO) << layer_.type() << " param:";
}

void EluLayerPlugin::codegen(TensorOp *op) {
  // get input shape
  const TensorShape & input_shape = op->input_shape(0);

  // get parameter from caffe proto
  const std::string &value = layer_.custom().value();
  YAML::Node yaml_data = YAML::Load(value);
  float alpha = yaml_data["alpha"].as<float>();

  // set normal output shape
  TensorShape *output_shape = op->add_output_shape();
  output_shape->CopyFrom(input_shape);

  // set out_param
  TGCustomizedParameter* out_param = op->mutable_tg_customized_param();
  out_param->add_f32_param(alpha);
}

} // end namespace of bmnet.
