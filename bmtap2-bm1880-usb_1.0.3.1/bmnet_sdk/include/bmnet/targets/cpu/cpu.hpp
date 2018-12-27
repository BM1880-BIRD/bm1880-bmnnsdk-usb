/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BMNET_CPU_OP_H_
#define _BMNET_CPU_OP_H_

#include <bmnet/proto/TensorOps.hpp>

namespace bmnet {

  void add_profile_op(const std::string& debug_ir_name,
                    const std::string& debug_ir_type);

  void add_cpu_op(const char* op_name, TensorOp& op);

  void add_cpu_op(void* ctx, const char* op_name, TensorOp& op);

}
#endif