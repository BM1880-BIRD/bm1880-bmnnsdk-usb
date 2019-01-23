/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _FRONTEND_CONTEXT_H_
#define _FRONTEND_CONTEXT_H_

#include <vector>

#include <bmnet/codegen/Graph.hpp>
#include <bmnet/frontend/FrontendContext.hpp>
#include <bmnet/frontend/Layer.hpp>

namespace bmnet {

// template <typename Dtype>
class FrontendContext {
 protected:  // Can only create subclasses.
  FrontendContext() { graph_ = new Graph(); }

 public:
  virtual ~FrontendContext() { delete graph_; }

  Graph *getGraph() { return graph_; }

  TensorShape &get_input_shape() { return input_shape_; }
  void set_input_shape(const TensorShape &shape) { input_shape_.CopyFrom(shape); }

  // record size of NEURON/WEIGHT
  void setEnableDequantized(bool enable) { dequantized_enable = enable; }
  bool getEnableDequantized() { return dequantized_enable; }

  void setDataTypeSize(size_t size) { data_type_size_ = size; }
  size_t getDataTypeSize() {
    assert(data_type_size_);
    return data_type_size_;
  }

  // FIXME we need put this target information to somewhere
  int get_npu_number() const {
    assert(data_type_size_);
    if (data_type_size_ == 1) {
      // assume this is bm1880 target
      return 32;
    } else if (data_type_size_ == 4) {
      //  assume this is bm1682 target
      return 64;
    }
    assert(0);
    return -1;
  }

  // convert input model to bmnet.proto (bmnet IR)
  virtual NetParameter *convert(void *orig, TensorShape *input_shape) = 0;

  virtual void registerCustomizedLayer(void *layer) = 0;

 protected:
  void output_graph(NetParameter *out_net) { graph_->output_to_net(out_net); }

  void output_graph(const std::string &net_name, NetParameter *out_net) {
    graph_->set_name(net_name);
    output_graph(out_net);
  }

 protected:
  Graph *graph_;

 private:
  size_t data_type_size_{0};
  TensorShape input_shape_;
  bool dequantized_enable;
};

}  // namespace bmnet

#endif /* _FRONTEND_CONTEXT_H_ */
