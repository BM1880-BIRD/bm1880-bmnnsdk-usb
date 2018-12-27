/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_DECONVOLUTION_H_
#define _CAFFE_LAYER_DECONVOLUTION_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class DeconvolutionLayer : public CaffeLayer {
 public:
  explicit DeconvolutionLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~DeconvolutionLayer() override = default;

  std::string layer_name() override { return std::string("Deconvolution"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet

#endif /* _CAFFE_LAYER_DECONVOLUTION_H_ */
