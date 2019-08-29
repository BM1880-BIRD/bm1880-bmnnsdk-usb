/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_RESHAPE_H_
#define _CAFFE_LAYER_RESHAPE_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class ReshapeLayer : public CaffeLayer {
 public:
  explicit ReshapeLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~ReshapeLayer() override = default;

  std::string layer_name() override { return std::string("Reshape"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 protected:
  // These three param copy from caffe by JiangTao
  // vector of axes indices whose dimensions we'll copy from the bottom
  std::vector<int> copy_axes_;
  // the index of the axis whose dimension we infer, or -1 if none
  int inferred_axis_;
  // the product of the "constant" output dimensions
  int constant_count_;

 private:
};

}  // namespace bmnet
#endif
