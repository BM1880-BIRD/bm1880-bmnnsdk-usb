/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_RELU_H_
#define _CAFFE_LAYER_RELU_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class ReluLayer : public CaffeLayer {
 public:
  explicit ReluLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~ReluLayer() override = default;

  std::string layer_name() override { return std::string("ReLU"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
