/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_ABANDON_H_
#define _CAFFE_LAYER_ABANDON_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class AbandonLayer : public CaffeLayer {
 public:
  explicit AbandonLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~AbandonLayer() override = default;

  std::string layer_name() override { return std::string("Abandon"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
