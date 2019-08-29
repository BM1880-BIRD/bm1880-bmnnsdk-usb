/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
// This file shouldn't change any more.
// if must change, need reviewed by jiang.jiang
#ifndef BMNET_CPU_CMD_H
#define BMNET_CPU_CMD_H

#include <string>
#include <vector>

// if CpuLayer changed, you need to increase CPU_LAYER_VERSION
#define CPU_LAYER_VERSION 3
#define CPU_LAYER_NEURON_ADDR (1)
#define CPU_LAYER_WEIGHT_ADDR (2)
#define CPU_LAYER_CTX (3)

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

  virtual void get_op_coeffs(std::vector<std::pair<gaddr_t, uint64_t> >& info) = 0;

  virtual void relocate_op_coeffs(std::vector<gaddr_t>& addrs) = 0;

	//<! id means CPU_LAYER_XXX
  virtual void func(int id, void* p) = 0;
};

typedef CpuLayer* (*create_op)(void);
typedef void (*destroy_op)(CpuLayer*);
typedef uint32_t (*get_version_op)();

#endif
