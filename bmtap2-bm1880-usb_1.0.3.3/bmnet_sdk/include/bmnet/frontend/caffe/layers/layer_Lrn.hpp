/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_LRN_H_
#define _CAFFE_LAYER_LRN_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class LrnLayer : public CaffeLayer {
 public:
  explicit LrnLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~LrnLayer() override = default;

  std::string layer_name() override { return std::string("LRN"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
