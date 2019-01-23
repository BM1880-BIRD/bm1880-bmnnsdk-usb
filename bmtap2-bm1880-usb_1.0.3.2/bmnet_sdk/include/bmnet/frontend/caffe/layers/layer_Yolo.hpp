/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_YOLO_H_
#define _CAFFE_LAYER_YOLO_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class YoloLayer : public CaffeLayer {
 public:
  explicit YoloLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~YoloLayer() override = default;

  std::string layer_name() override { return std::string("Yolo"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif
