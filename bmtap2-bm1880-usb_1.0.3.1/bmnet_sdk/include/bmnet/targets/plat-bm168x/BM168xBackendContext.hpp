/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM168X_BACKEND_CONTEXT_H_
#define _BM168X_BACKEND_CONTEXT_H_

#include <ios>
#include <iostream>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include <bmnet/backend/BackendContext.hpp>
#include <bmnet/backend/TensorInst.hpp>

#include <bmkernel/bm168x/bmkernel_1682.h>

namespace bmnet {


/// Writes BM168x machine code to a stream.
class BM168xBackendContext : public BackendContext {
public:
  BM168xBackendContext(int chip_ver, int nodechip_num);
  BM168xBackendContext(int chip_ver, int nodechip_num, std::vector<float>& weight);
  ~BM168xBackendContext() override;

  void build(NetParameter &net, const char* term_layer=NULL) override;
  void enter()override;
  void exit()override;
  void submit()override;

  void registerCustomizedTensorInst(TensorInst* inst)override;
  void update_weight(std::vector<float>& weight) override;

  u64 get_global_neuron_base() {return global_neuron_base_; }
  u64 get_global_weight_base() {return global_weight_base_; }

  const TensorShape* getNetTensorShape(){return net_tensor_shape_;}
  void setNetTensorShape(const TensorShape &ts);
  void setNetTensorShape(NetParameter* net);
  NetParameter* getNetParameter() {return net_;}
  void setNetParameter(NetParameter* net) { net_ = net;}
  NetParameter* getBaseNetParameter(){return base_net_;}
  void setBaseNetParameter(NetParameter* base_net){base_net_ = base_net;}

  void *bmk() {
    return bmk_;
  }
  void *weight() {
    return weight_;
  }

  uint64_t weight_size() {return weight_size_;}
  float read_weight(uint64_t offset);

  void ImportInput(const std::string &input_file, const std::vector<int> &input_shape);
  float *ExportInputFp32();
private:

  bmk_info_t bmk_info_;
  void *bmk_;
  void *weight_;
  NetParameter *net_;
  NetParameter *base_net_;
  const TensorShape *net_tensor_shape_;
  void *emiter_;
  uint64_t weight_size_;

  bool input_init_;
  std::string input_file_;
  std::vector<int> input_shape_;
  std::unique_ptr<float[]> input_data_;
  /*
   * FIXME: use fixed neuron_base and weight_base for now
   */
  static const u64 global_neuron_base_ = 0x1;
  static const u64 global_weight_base_ = 0x2;
  static const u64 global_arm_base_ = 0x3;

};

} // end namespace of bmnet.

#endif /* _BM168X_BACKEND_CONTEXT_H_ */
