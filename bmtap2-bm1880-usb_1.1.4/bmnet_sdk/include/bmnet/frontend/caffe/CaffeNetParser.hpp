/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_NET_PARSER_H_
#define _CAFFE_NET_PARSER_H_

#include <caffe.pb.h>
#include <bmnet/codegen/Graph.hpp>
#include <bmnet/frontend/NetParser.hpp>
#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>

namespace bmnet {

class CaffeLayer;

/// Parse network and generate TensorOps
class CaffeNetParser : public NetParser {
 public:
  explicit CaffeNetParser(FrontendContext* ctx);
  ~CaffeNetParser() override = default;

  TensorShape parse_net(const int chip_ver, const NetCalibrationParameter& param,
                        ::caffe::NetParameter* in_net);
  void layer_codegen(const int chip_ver, const NetCalibrationParameter& param,
                     caffe::LayerParameter& layer_param);  // NOLINT
  uint32_t get_weight_size() { return current_weight_offset_; }
  CaffeLayer* findLayer(const std::string& layer_name);
  void set_net_parameter(::caffe::NetParameter* in_net);

 private:
  uint32_t current_weight_offset_;
  void get_input_info(const ::caffe::NetParameter* in_net, const std::vector<TensorShape>& shapes,
                      std::vector<InputInfoPair>& input_info);
  void setup_bottom_top(TensorOp* op, const caffe::LayerParameter& param);

  void setup_layer_input(Node* node, const caffe::LayerParameter& param, CaffeLayer* layer);
  void setup_layer_output(Node* node, const caffe::LayerParameter& param, CaffeLayer* layer);
};

}  // namespace bmnet
#endif /* _CAFFE_NET_PARSER_H_ */
