/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_PREPROCESSING_H_
#define _CAFFE_LAYER_PREPROCESSING_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class PreprocessLayer : public CaffeLayer {
 public:
  explicit PreprocessLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~PreprocessLayer() override = default;

  std::string layer_name() override { return std::string("Preprocess"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet

#endif /* _CAFFE_LAYER_PREPROCESSING_H_ */
