/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef BMNET_CPU_CMD_H
#define BMNET_CPU_CMD_H

#include <string>
#include <vector>

// if CpuLayer changed, you need to increase CPU_LAYER_VERSION
#define CPU_LAYER_VERSION 1

class CpuLayer {

public:
  CpuLayer() {}
  virtual ~CpuLayer() {}

  virtual bool parse_cmd(char *payload, int payload_size) = 0;

  virtual const std::string& get_type() = 0;

  virtual void get_op_inputs(std::vector<std::pair<gaddr_t, uint64_t> >& info) = 0;

  virtual void get_op_outputs(std::vector<std::pair<gaddr_t, uint64_t> >& info) = 0;

  virtual void relocate_op_inputs(std::vector<gaddr_t>& addrs) = 0;

  virtual void relocate_op_outputs(std::vector<gaddr_t>& addrs) = 0;

  virtual void run() = 0;

  virtual void init_runtime_info(void *ctx, gaddr_t neuron_addr) = 0;
};

typedef CpuLayer* (*create_op)(void);
typedef void (*destroy_op)(CpuLayer*);
typedef uint32_t (*get_version_op)();

#endif
