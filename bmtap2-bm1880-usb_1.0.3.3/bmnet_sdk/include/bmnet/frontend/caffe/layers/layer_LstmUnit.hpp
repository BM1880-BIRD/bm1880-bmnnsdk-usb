/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_LSTMUNIT_H_
#define _CAFFE_LAYER_LSTMUNIT_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class LstmUnitLayer : public CaffeLayer {
 public:
  explicit LstmUnitLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~LstmUnitLayer() override = default;

  std::string layer_name() override { return std::string("LstmUnit"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
