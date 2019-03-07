/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_POOLING_H_
#define _CAFFE_LAYER_POOLING_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class PoolingLayer : public CaffeLayer {
 public:
  explicit PoolingLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~PoolingLayer() override = default;

  std::string layer_name() override { return std::string("Pooling"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet

#endif /* _CAFFE_LAYER_POOLING_H_ */
