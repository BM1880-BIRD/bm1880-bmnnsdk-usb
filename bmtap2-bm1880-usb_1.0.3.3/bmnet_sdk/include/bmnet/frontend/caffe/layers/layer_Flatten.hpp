/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_FLATTEN_H_
#define _CAFFE_LAYER_FLATTEN_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class FlattenLayer : public CaffeLayer {
 public:
  explicit FlattenLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~FlattenLayer() override = default;

  std::string layer_name() override { return std::string("Flatten"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 protected:
 private:
};

}  // namespace bmnet
#endif
