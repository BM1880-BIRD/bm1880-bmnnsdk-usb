/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_SPLIT_H_
#define _CAFFE_LAYER_SPLIT_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class SplitLayer : public CaffeLayer {
 public:
  explicit SplitLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~SplitLayer() override = default;

  std::string layer_name() override { return std::string("Split"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
