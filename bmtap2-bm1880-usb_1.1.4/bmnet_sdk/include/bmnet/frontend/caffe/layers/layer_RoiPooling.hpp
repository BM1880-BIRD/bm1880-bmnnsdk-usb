/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_ROIPOOLING_H_
#define _CAFFE_LAYER_ROIPOOLING_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class RoiPoolingLayer : public CaffeLayer {
 public:
  explicit RoiPoolingLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~RoiPoolingLayer() override = default;

  std::string layer_name() override { return std::string("ROIPooling"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif
