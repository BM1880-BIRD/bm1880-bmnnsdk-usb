/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_BN_H_
#define _CAFFE_LAYER_BN_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class BnLayer : public CaffeLayer {
 public:
  explicit BnLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~BnLayer() override = default;

  std::string layer_name() override { return std::string("BN"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet

#endif /* _CAFFE_LAYER_BN_H_ */
