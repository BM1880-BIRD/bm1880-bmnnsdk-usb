/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BMNET_CPU_OP_H_
#define _BMNET_CPU_OP_H_

#include <bmnet/proto/TensorOps.hpp>
#include <bmnet/targets/plat-bm188x/BM188xBackendContext.hpp>

namespace bmnet {

  void add_profile_op(const std::string& debug_ir_name,
                      const std::string& debug_ir_type);

  void add_profile_op(const std::string& debug_ir_name,
                      const std::string& debug_ir_type,
                      const std::string& bottom,
                      const std::string& top);

  void add_profile_op(BM188xBackendContext* ctx,
                      const std::string& debug_ir_name,
                      const std::string& debug_ir_type);

  void add_profile_op(BM188xBackendContext* ctx, const TensorOp& op);

  void add_cpu_op(const char* op_name, TensorOp& op);

  void add_cpu_op(BM188xBackendContext* ctx, const char* op_name, TensorOp& op);

}
#endif