/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_DETECTOUTPUT_H_
#define _CAFFE_LAYER_DETECTOUTPUT_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class DetectOutput : public CaffeLayer {
 public:
  explicit DetectOutput(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~DetectOutput() override = default;

  std::string layer_name() override { return std::string("DetectionOutput"); }

  void dump() override;
  void codegen(TensorOp *op) override;
  void setup(TensorOp *op) override;
};

}  // namespace bmnet.
#endif
