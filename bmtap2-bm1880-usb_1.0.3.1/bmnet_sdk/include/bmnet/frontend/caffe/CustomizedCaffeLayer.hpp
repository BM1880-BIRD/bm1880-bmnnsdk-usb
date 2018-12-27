/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_CUSTOMIZED_LAYER_H_
#define _CAFFE_CUSTOMIZED_LAYER_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class CustomizedCaffeLayer : public CaffeLayer {
 public:
  CustomizedCaffeLayer() : CaffeLayer() {}
  ~CustomizedCaffeLayer() override = default;

  void setup(TensorOp* op) override {
    op->set_name(layer_.name());
    op->set_type("tg_customized");
    TGCustomizedParameter* param = op->mutable_tg_customized_param();
    param->set_sub_type(layer_name());
  }
};

}  // namespace bmnet
#endif
