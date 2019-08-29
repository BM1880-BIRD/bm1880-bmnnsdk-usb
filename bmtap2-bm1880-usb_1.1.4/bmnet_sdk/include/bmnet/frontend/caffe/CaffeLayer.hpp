/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_H_
#define _CAFFE_LAYER_H_

#include <bmnet/calibration.pb.h>
#include <caffe.pb.h>
#include <bmnet/frontend/Layer.hpp>

namespace bmnet {

enum LAYERMODE { BOTTOM = 1, SELF = 2, TOP = 3 };

class CaffeLayer : public Layer {
 public:
  CaffeLayer() : Layer(), layer_(void_layer_) {}
  explicit CaffeLayer(FrontendContext *ctx) : Layer(ctx), layer_(void_layer_) {}
  ~CaffeLayer() override = default;

  // NOLINTNEXTLINE
  void set_layer(caffe::LayerParameter &layer) { layer_ = layer; }
  void set_player(caffe::LayerParameter *layer) { player_ = layer; }
  void set_net_parameter(::caffe::NetParameter *net) { net_ = net; }
  ::caffe::NetParameter *get_net_parameter() { return net_; }
  void set_current_weight_size(uint32_t weight_size) { current_weight_size_ = weight_size; }
  uint32_t get_current_weight_size() { return current_weight_size_; }
  void reserve_weight(int size) { current_weight_size_ += size; }
  float GetLayerThreshold(const NetCalibrationParameter &param, const std::string layerNameconst,
                          const std::string &blobName, LAYERMODE mode);

  virtual int quantize(const NetCalibrationParameter &qparam, TensorOp *op) { return 0; }

 protected:
  ::caffe::NetParameter *net_;
  caffe::LayerParameter *player_;
  caffe::LayerParameter &layer_;
  caffe::LayerParameter void_layer_;
  uint32_t current_weight_size_;
};

}  // end namespace bmnet

#endif /* _CAFFE_LAYER_H_ */
