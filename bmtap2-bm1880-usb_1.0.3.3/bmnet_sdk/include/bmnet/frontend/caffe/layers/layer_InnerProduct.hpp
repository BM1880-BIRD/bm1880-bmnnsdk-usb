/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_INNERPRODUCT_H_
#define _CAFFE_LAYER_INNERPRODUCT_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class InnerProductLayer : public CaffeLayer {
 public:
  explicit InnerProductLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~InnerProductLayer() override = default;

  std::string layer_name() override { return std::string("InnerProduct"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet

#endif /* _CAFFE_LAYER_INNERPRODUCT_H_ */
