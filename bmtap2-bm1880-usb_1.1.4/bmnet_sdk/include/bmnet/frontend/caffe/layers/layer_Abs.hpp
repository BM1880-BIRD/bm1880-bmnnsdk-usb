/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_ABS_H_
#define _CAFFE_LAYER_ABS_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class AbsLayer : public CaffeLayer {
 public:
  explicit AbsLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~AbsLayer() override = default;

  std::string layer_name() override { return std::string("AbsVal"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
