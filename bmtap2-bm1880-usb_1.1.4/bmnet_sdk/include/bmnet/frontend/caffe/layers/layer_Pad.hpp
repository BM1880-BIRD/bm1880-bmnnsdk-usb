/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_PAD_H_
#define _CAFFE_LAYER_PAD_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class PadLayer : public CaffeLayer {
 public:
  explicit PadLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~PadLayer() override = default;

  std::string layer_name() override { return std::string("Pad"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif