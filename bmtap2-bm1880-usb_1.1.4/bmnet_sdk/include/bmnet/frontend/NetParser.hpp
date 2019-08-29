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
typedef std::pair<std::string, TensorShape> InputInfoPair;
class FrontendContext;
class Layer;

/// NetParser - Generic interface for parsing network and genrate IR
class NetParser {
 protected:
  explicit NetParser(FrontendContext* ctx) : ctx_(ctx), current_output_offset_(0) {}
  std::vector<TensorShape> expand_input_size(const size_t& expand_size,
                                             const std::vector<TensorShape>& shapes);
  void update_input_info(const std::vector<TensorShape>& shapes,
                         std::vector<InputInfoPair>& input_info);
  void add_start_node(const TensorShape& shape);
  TensorShape add_start_node(const std::vector<InputInfoPair>& input_info);
  void add_end_node(Node* output_node);
  Node* add_concat_node(const std::vector<Node*>& output_nodes);
  void add_dequantized_node(std::vector<Node*>& output_nodes);

  Node* create_node(TensorOp& op);

 public:
  virtual ~NetParser();

  void parse_start() {
    OpCounter::get()->reset();
    ctx_->getGraph()->build_start();
  }
  void parse_end() { ctx_->getGraph()->build_end(); }

  void get_output_nodes(std::vector<Node*>& outputs) {
    return ctx_->getGraph()->build_output_nodes(outputs);
  }

  void set_current_shape(const TensorShape& shape) { current_shape_.CopyFrom(shape); }

  void registerLayer(Layer* layer);
  Layer* lookupLayer(const std::string& layer_name);
  void destroyLayer(const std::string& layer_name);

 protected:
  FrontendContext* ctx_;
  TensorShape current_shape_;
  uint64_t current_output_offset_;

 private:
  std::vector<Layer*> LayerList_;
};

}  // namespace bmnet

#endif /* _NET_PARSER_H_ */
