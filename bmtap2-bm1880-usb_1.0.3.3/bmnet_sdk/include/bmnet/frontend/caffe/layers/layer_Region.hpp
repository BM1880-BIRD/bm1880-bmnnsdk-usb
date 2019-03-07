/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_REGION_H_
#define _CAFFE_LAYER_REGION_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class RegionLayer : public CaffeLayer {
 public:
  explicit RegionLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~RegionLayer() override = default;

  std::string layer_name() override { return std::string("Region"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif
