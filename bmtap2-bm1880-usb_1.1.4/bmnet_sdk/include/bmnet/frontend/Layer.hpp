/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _LAYER_H_
#define _LAYER_H_

#include <bmnet/bmnet.pb.h>
#include <bmnet/codegen/Graph.hpp>
#include <vector>

namespace bmnet {
class FrontendContext;

class Layer {
 public:
  Layer() = default;
  explicit Layer(FrontendContext *ctx) : ctx_(ctx) {}
  virtual ~Layer() = default;

  virtual std::string layer_name() = 0;
  bool IsPluginLayer() { return is_plugin_layer; }
  void SetPluginLayer() { is_plugin_layer = true; }

  const FrontendContext *get_frontend_context() { return ctx_; }
  void set_frontend_context(FrontendContext *ctx) { ctx_ = ctx; }
  virtual void dump() = 0;
  virtual void setup(TensorOp *op) = 0;
  virtual void codegen(TensorOp *op) = 0;

 protected:
  bool is_plugin_layer = false;
  void add_output_offset(int offset) {}
  FrontendContext *ctx_ = nullptr;
};

}  // end namespace bmnet

#endif /* _LAYER_H_ */
