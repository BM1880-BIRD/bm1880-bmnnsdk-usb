/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_UPSAMPLE_H_
#define _CAFFE_LAYER_UPSAMPLE_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class UpsampleLayer : public CaffeLayer {
 public:
  explicit UpsampleLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~UpsampleLayer() override = default;

  std::string layer_name() override { return std::string("Upsample"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
