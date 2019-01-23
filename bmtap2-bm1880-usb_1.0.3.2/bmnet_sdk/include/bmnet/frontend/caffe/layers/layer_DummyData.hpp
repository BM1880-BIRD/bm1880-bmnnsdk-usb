/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_DUMMY_DATA_H_
#define _CAFFE_LAYER_DUMMY_DATA_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class DummyDataLayer : public CaffeLayer {
 public:
  explicit DummyDataLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~DummyDataLayer() override = default;

  std::string layer_name() override { return std::string("DummyData"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 protected:
 private:
};

}  // namespace bmnet
#endif
