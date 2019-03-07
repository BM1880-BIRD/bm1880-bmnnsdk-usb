/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_DUMMY_H_
#define _CAFFE_LAYER_DUMMY_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class DummyLayer : public CaffeLayer {
 public:
  explicit DummyLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~DummyLayer() override = default;

  std::string layer_name() override { return std::string("Dummy"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
