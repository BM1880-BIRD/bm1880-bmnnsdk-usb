/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_LEAKYRELU_CUSTOMIZED_H_
#define _CAFFE_LAYER_LEAKYRELU_CUSTOMIZED_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class LeakyReluLayerPlugin : public CustomizedCaffeLayer {
public:
  LeakyReluLayerPlugin() : CustomizedCaffeLayer() {}
  ~LeakyReluLayerPlugin() {}

  std::string layer_name() {return std::string("ReLU"); }
  void dump();
  void setup(TensorOp* op) override;
  void codegen(TensorOp *op);
};

} // end namespace of bmnet.
#endif
