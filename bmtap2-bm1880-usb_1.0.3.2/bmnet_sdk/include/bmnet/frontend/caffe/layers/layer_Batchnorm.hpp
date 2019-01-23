/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_BATCHNORM_H_
#define _CAFFE_LAYER_BATCHNORM_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class BatchnormLayer : public CaffeLayer {
 public:
  explicit BatchnormLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~BatchnormLayer() override = default;

  std::string layer_name() override { return std::string("BatchNorm"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
