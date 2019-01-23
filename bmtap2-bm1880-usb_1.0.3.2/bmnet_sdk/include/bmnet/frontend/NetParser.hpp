/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _NET_PARSER_H_
#define _NET_PARSER_H_

#include <bmnet/frontend/FrontendContext.hpp>
#include <bmnet/frontend/Layer.hpp>
#include <iostream>
#include <vector>

namespace bmnet {
class FrontendContext;
class Layer;

/// NetParser - Generic interface for parsing network and genrate IR
class NetParser {
 protected:
  explicit NetParser(FrontendContext* ctx) : ctx_(ctx) {}

 public:
  virtual ~NetParser();

  void parse_start() { ctx_->getGraph()->build_start(); }
  void parse_end() { ctx_->getGraph()->build_end(); }

  Node* create_node(const TensorOp& op) { return ctx_->getGraph()->add_node(op); }

  std::vector<Node*> get_output_nodes() { return ctx_->getGraph()->build_output_nodes(); }

  void set_current_shape(const TensorShape& shape) { current_shape_.CopyFrom(shape); }

  void registerLayer(Layer* layer) { LayerList_.push_back(layer); }
  Layer* lookupLayer(const std::string& layer_name);
  void destroyLayer(const std::string& layer_name);

 protected:
  FrontendContext* ctx_;
  TensorShape current_shape_;

 private:
  std::vector<Layer*> LayerList_;
};

}  // namespace bmnet

#endif /* _NET_PARSER_H_ */
