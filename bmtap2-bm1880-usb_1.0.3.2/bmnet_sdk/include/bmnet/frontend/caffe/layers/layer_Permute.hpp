/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_PERMUTE_H_
#define _CAFFE_LAYER_PERMUTE_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class PermuteLayer : public CaffeLayer {
 public:
  explicit PermuteLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~PermuteLayer() override = default;

  std::string layer_name() override { return std::string("Permute"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 protected:
 private:
};

}  // namespace bmnet
#endif
