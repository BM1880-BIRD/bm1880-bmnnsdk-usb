/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_BIAS_H_
#define _CAFFE_LAYER_BIAS_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class BiasLayer : public CaffeLayer {
 public:
  explicit BiasLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~BiasLayer() override = default;

  std::string layer_name() override { return std::string("Bias"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif