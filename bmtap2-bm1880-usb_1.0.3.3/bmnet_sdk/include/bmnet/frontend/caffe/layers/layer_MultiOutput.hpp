/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_MULTI_OUTPUT_H_
#define _CAFFE_LAYER_MULTI_OUTPUT_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class MultiOutputLayer : public CaffeLayer {
 public:
  explicit MultiOutputLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~MultiOutputLayer() override = default;

  std::string layer_name() override { return std::string("MultiOutput"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
