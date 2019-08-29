/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_CUSTOMIZED_H_
#define _CAFFE_LAYER_CUSTOMIZED_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class EluLayerPlugin : public CustomizedCaffeLayer {
public:
  EluLayerPlugin() : CustomizedCaffeLayer() {}
  ~EluLayerPlugin() {}

  std::string layer_name() {return std::string("ELU"); }
  void dump();
  void codegen(TensorOp *op);
};

} // end namespace of bmnet.
#endif
