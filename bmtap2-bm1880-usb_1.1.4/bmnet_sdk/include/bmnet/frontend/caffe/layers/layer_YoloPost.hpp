/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_YOLOPOST_H_
#define _CAFFE_LAYER_YOLOPOST_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class YoloPostLayer : public CaffeLayer {
 public:
  explicit YoloPostLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~YoloPostLayer() override = default;

  std::string layer_name() override { return std::string("YoloPost"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif
