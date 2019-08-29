/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_AXPY_H_
#define _CAFFE_LAYER_AXPY_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class AxpyLayer : public CaffeLayer {
 public:
  explicit AxpyLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~AxpyLayer() override = default;

  std::string layer_name() override { return std::string("Axpy"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif
