/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#pragma once
#include <bmnet/frontend/Layer.hpp>
#include <bmnet/backend/Instruction.hpp>

#define LAYERAPI_VERSION "1.0.0"

namespace bmnet {
class LayerAPI {
public:
  LayerAPI() {}

  virtual ~LayerAPI() {
    if (onnx_layer) delete onnx_layer;
    if (caffe_layer) delete caffe_layer;
    if (int8_layer_inst) delete int8_layer_inst;
    if (float_layer_inst) delete float_layer_inst;
  }
  virtual void init(FrontendContext *ctx) = 0;
  const std::string getAPIVersion() { return LAYERAPI_VERSION; }
  virtual const std::string layerName() = 0;
  virtual Layer* getCaffeLayer() { return caffe_layer; }
  virtual Layer* getOnnxLayer() { return onnx_layer; }
  virtual Instruction* getInt8Instruction() { return int8_layer_inst; }
  virtual Instruction* getFloatInstruction() { return float_layer_inst; }

  typedef LayerAPI *create_t();
  typedef void destroy_t(LayerAPI *);
protected:
  bmnet::Layer *onnx_layer = nullptr;
  bmnet::Layer *caffe_layer = nullptr;
  bmnet::Instruction *int8_layer_inst = nullptr;
  bmnet::Instruction *float_layer_inst = nullptr;
};
}
