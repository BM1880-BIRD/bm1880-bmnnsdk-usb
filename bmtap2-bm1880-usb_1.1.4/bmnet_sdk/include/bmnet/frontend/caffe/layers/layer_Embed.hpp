/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_EMBED_H_
#define _CAFFE_LAYER_EMBED_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class EmbedLayer : public CaffeLayer {
 public:
  explicit EmbedLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~EmbedLayer() override = default;

  std::string layer_name() override { return std::string("Embed"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif
