/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM168X_BACKEND_CONTEXT_H_
#define _BM168X_BACKEND_CONTEXT_H_

#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <bmnet/backend/BackendContext.hpp>
#include <bmnet/backend/Instruction.hpp>

namespace bmnet {
class TensorInst;

/// Writes BM168x machine code to a stream.
class BM168xBackendContext : public BackendContext {
 public:
  BM168xBackendContext(int chip_ver, int nodechip_num);
  BM168xBackendContext(int chip_ver, int nodechip_num, std::vector<float>& weight);
  ~BM168xBackendContext() override;

  void build(NetParameter& net, const char* term_layer = nullptr) override;
  void enter() override;
  void exit() override;
  void submit() override;

  void registerInstruction(Instruction* inst) override;

  u64 get_global_neuron_base() { return global_neuron_base_; }
  u64 get_global_weight_base() { return global_weight_base_; }

  void* bmk() { return bmk_; }
  void* weight() { return weight_; }
  void update_weight(std::vector<float>& weight);
  uint64_t weight_size() { return weight_size_; }
  float read_weight(uint64_t offset);
  void setCurrentInst(void * curInst) { curInst_ = curInst; }
  void *getCurrentInst() { return curInst_; }

 private:
  bmk_info_t bmk_info_;
  void* bmk_;
  void* weight_;
  void* emiter_;
  uint64_t weight_size_;
  std::vector<int> input_shape_;

  void *builder_;
  void *curInst_;

  static const u64 global_neuron_base_ = 0x4000000000;
  static const u64 global_weight_base_ = 0x8000000000;
};

}  // namespace bmnet

#endif /* _BM168X_BACKEND_CONTEXT_H_ */
