/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_PSROIPOOLING_H_
#define _CAFFE_LAYER_PSROIPOOLING_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class PSRoiPoolingLayer : public CaffeLayer {
 public:
  explicit PSRoiPoolingLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~PSRoiPoolingLayer() override = default;

  std::string layer_name() override { return std::string("PSROIPooling"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif
