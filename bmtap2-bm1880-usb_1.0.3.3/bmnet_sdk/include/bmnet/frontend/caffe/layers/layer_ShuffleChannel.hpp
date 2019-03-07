/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_SHUFFLE_CHANNEL_H_
#define _CAFFE_LAYER_SHUFFLE_CHANNEL_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class ShuffleChannelLayer : public CaffeLayer {
 public:
  explicit ShuffleChannelLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~ShuffleChannelLayer() override = default;

  std::string layer_name() override { return std::string("ShuffleChannel"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
