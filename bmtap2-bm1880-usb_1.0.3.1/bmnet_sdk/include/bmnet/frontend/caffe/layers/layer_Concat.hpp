/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_CONCAT_H_
#define _CAFFE_LAYER_CONCAT_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class ConcatLayer : public CaffeLayer {
 public:
  explicit ConcatLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~ConcatLayer() override = default;

  std::string layer_name() override { return std::string("Concat"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
