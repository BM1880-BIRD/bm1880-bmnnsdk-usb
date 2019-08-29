/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_INTERP_H_
#define _CAFFE_LAYER_INTERP_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class InterpLayer : public CaffeLayer {
 public:
  explicit InterpLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~InterpLayer() override = default;

  std::string layer_name() override { return std::string("Interp"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet

#endif /* _CAFFE_LAYER_INTERP_H_ */
