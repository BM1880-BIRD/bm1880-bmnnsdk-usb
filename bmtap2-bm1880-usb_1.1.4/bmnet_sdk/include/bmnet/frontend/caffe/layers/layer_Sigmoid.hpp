/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_SIGMOID_H_
#define _CAFFE_LAYER_SIGMOID_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class SigmoidLayer : public CaffeLayer {
 public:
  explicit SigmoidLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~SigmoidLayer() override = default;

  std::string layer_name() override { return std::string("Sigmoid"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  int quantize(const NetCalibrationParameter &qparam, TensorOp *op) override;
};

}  // namespace bmnet
#endif
