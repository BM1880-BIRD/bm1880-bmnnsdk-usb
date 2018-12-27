/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_REVERSE_H_
#define _CAFFE_LAYER_REVERSE_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class ReverseLayer : public CaffeLayer {
 public:
  explicit ReverseLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~ReverseLayer() override = default;

  std::string layer_name() override { return std::string("Reverse"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
