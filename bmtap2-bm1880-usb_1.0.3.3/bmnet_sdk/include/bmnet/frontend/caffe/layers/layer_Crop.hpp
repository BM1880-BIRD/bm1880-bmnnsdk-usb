/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_CROP_H_
#define _CAFFE_LAYER_CROP_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class CropLayer : public CaffeLayer {
 public:
  explicit CropLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~CropLayer() override = default;

  std::string layer_name() override { return std::string("Crop"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
