/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef BMNET_CPU_OP_HPP
#define BMNET_CPU_OP_HPP

#include <vector>
#include <bmnet/proto/TensorOps.hpp>
#include <bmnet/targets/cpu/cpu_layer.hpp>
#include <bmnet/bmnet.pb.h>

namespace bmnet {

class CpuOp: public CpuLayer {

public:

  CpuOp(): CpuLayer(), op_() {}

  virtual ~CpuOp() {}

  bool parse_cmd(char *payload, int payload_size);

  const std::string& get_type();

  void get_op_inputs(std::vector<std::pair<gaddr_t, uint64_t> >& info);

  void get_op_outputs(std::vector<std::pair<gaddr_t, uint64_t> >& info);

  void relocate_op_inputs(std::vector<gaddr_t>& addrs);

  void relocate_op_outputs(std::vector<gaddr_t>& addrs);

  void init_runtime_info(void *ctx, gaddr_t neuron_addr) {}

protected:
  TensorOp op_;

};

}

#define REGISTER_CPU_OP(x)                     \
using namespace bmnet;                         \
extern "C" CpuLayer* create_cpu_op() {         \
  return new x();                              \
}                                              \
                                               \
extern "C" void destroy_cpu_op(CpuLayer* p) {  \
  delete p;                                    \
}                                              \
                                               \
extern "C" uint32_t get_version_cpu_op() {         \
  return CPU_LAYER_VERSION;                    \
}

#endif
