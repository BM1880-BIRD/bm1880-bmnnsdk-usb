/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_NET_PARSER_H_
#define _CAFFE_NET_PARSER_H_

#include <bmnet/bmnet_caffe.pb.h>
#include <bmnet/codegen/Graph.hpp>
#include <bmnet/frontend/NetParser.hpp>
#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <map>
#include <utility>
#include <vector>

namespace bmnet {

class CaffeLayer;

/// Parse network and generate TensorOps
class CaffeNetParser : public NetParser {
 public:
  explicit CaffeNetParser(FrontendContext* ctx);
  ~CaffeNetParser() override = default;

  void parse_net(caffe::NetParameter* in_net);
  void layer_codegen(caffe::LayerParameter& layer_param);  // NOLINT
  uint32_t get_weight_size() { return current_weight_offset_; }
  CaffeLayer* findLayer(const std::string& layer_name);

 private:
  uint64_t current_output_offset_;
  uint32_t current_weight_offset_;
  void add_start_node(const TensorShape& shape);
  void add_end_node(Node* output_node);
  Node* add_concat_node(std::vector<Node*>* output_nodes);
  void add_dequantized_node(std::vector<Node*>& output_nodes);
  void setup_bottom_top(TensorOp* op, const caffe::LayerParameter& param);

  void setup_layer_input(Node* node, const caffe::LayerParameter& param, CaffeLayer* layer);
  void setup_layer_output(Node* node, const caffe::LayerParameter& param, CaffeLayer* layer);
};

}  // namespace bmnet
#endif /* _CAFFE_NET_PARSER_H_ */
