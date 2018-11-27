/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_PRIORBOX_H_
#define _CAFFE_LAYER_PRIORBOX_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class PriorboxLayer : public CaffeLayer {
 public:
  explicit PriorboxLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~PriorboxLayer() override = default;

  std::string layer_name() override { return std::string("PriorBox"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 protected:
 private:
};

}  // namespace bmnet
#endif
