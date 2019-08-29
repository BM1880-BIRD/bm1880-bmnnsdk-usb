/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_REDUCTION_H_
#define _CAFFE_LAYER_REDUCTION_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class ReductionLayer : public CaffeLayer {
 public:
  explicit ReductionLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~ReductionLayer() override = default;

  std::string layer_name() override { return std::string("Reduction"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

  int quantize(const NetCalibrationParameter &qparam, TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
