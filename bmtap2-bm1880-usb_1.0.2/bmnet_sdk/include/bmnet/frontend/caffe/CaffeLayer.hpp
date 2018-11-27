/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_H_
#define _CAFFE_LAYER_H_

#include <bmnet/bmnet_caffe.pb.h>
#include <bmnet/frontend/Layer.hpp>

namespace bmnet {

class CaffeLayer : public Layer {
 public:
  CaffeLayer() : Layer(), layer_(void_layer_) {}
  explicit CaffeLayer(FrontendContext *ctx) : Layer(ctx), layer_(void_layer_) {}
  ~CaffeLayer() override = default;

  // NOLINTNEXTLINE
  void set_layer(caffe::LayerParameter &layer) { layer_ = layer; }
  void set_current_weight_size(uint32_t weight_size) { current_weight_size_ = weight_size; }
  uint32_t get_current_weight_size() { return current_weight_size_; }
  void reserve_weight(int size) { current_weight_size_ += size; }

 protected:
  caffe::LayerParameter &layer_;
  caffe::LayerParameter void_layer_;
  uint32_t current_weight_size_;
};

}  // end namespace bmnet

#endif /* _CAFFE_LAYER_H_ */
