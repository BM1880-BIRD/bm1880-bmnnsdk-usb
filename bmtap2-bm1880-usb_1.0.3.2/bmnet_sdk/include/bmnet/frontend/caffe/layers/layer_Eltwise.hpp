/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_ELTWISE_H_
#define _CAFFE_LAYER_ELTWISE_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class EltwiseLayer : public CaffeLayer {
 public:
  explicit EltwiseLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~EltwiseLayer() override = default;

  std::string layer_name() override { return std::string("Eltwise"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet

#endif /* _CAFFE_LAYER_ELTWISE_H_ */
