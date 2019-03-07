/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_SLICE_H_
#define _CAFFE_LAYER_SLICE_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class SliceLayer : public CaffeLayer {
 public:
  explicit SliceLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~SliceLayer() override = default;

  std::string layer_name() override { return std::string("Slice"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
