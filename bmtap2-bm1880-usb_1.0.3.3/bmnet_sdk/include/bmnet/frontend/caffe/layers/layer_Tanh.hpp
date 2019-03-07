/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_TANH_H_
#define _CAFFE_LAYER_TANH_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class TanhLayer : public CaffeLayer {
 public:
  explicit TanhLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~TanhLayer() override = default;

  std::string layer_name() override { return std::string("TanH"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
