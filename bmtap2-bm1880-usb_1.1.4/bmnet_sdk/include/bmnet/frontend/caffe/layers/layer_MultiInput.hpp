/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_MULTI_INPUT_H_
#define _CAFFE_LAYER_MULTI_INPUT_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class MultiInputLayer : public CaffeLayer {
 public:
  explicit MultiInputLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~MultiInputLayer() override = default;

  std::string layer_name() override { return std::string("MultiInput"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
