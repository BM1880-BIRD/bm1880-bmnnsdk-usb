/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_POWER_H_
#define _CAFFE_LAYER_POWER_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class PowerLayer : public CaffeLayer {
 public:
  explicit PowerLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~PowerLayer() override = default;

  std::string layer_name() override { return std::string("Power"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
