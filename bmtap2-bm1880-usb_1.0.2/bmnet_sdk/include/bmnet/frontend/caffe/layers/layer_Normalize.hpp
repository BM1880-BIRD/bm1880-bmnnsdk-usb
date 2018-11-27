/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_NORMALIZE_H_
#define _CAFFE_LAYER_NORMALIZE_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class NormalizeLayer : public CaffeLayer {
 public:
  explicit NormalizeLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~NormalizeLayer() override = default;

  std::string layer_name() override { return std::string("Normalize"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
