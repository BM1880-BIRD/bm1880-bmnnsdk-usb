/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _TENSORINST_H_
#define _TENSORINST_H_

#include <bmnet/proto/TensorOps.hpp>
#include <bmnet/backend/BackendContext.hpp>
#include <bmnet/targets/cpu/cpu.hpp>

namespace bmnet {
class BackendContext;

/// \brief Instances of this class represent a single tensor instrunction,
/// could be a TL instruction or a TG instruction.
class TensorInst {
public:
  TensorInst() : op_(void_op_) {}
  TensorInst(TensorOp& op) : op_(op) {}
  TensorInst(BackendContext* ctx)
      : ctx_(ctx), op_(void_op_) {}
  TensorInst(BackendContext* ctx, TensorOp& op)
      : ctx_(ctx), op_(op) {}
  virtual ~TensorInst(void) {}

  void set_op(TensorOp& op) {op_ = op; }
  std::string get_op_type() { return op_.type(); }
  std::string get_op_name() {return op_.name();}
  BackendContext* get_backend_context() {return ctx_; }
  virtual void set_backend_context(BackendContext* ctx) {ctx_ = ctx; }

  // inst_name(): setup IR's type name.
  virtual std::string inst_name() = 0;

  // dump(): print details of IR
  virtual void dump() = 0;

  // compute(): translate IR to instructions of target board.
  // you could add pre-processing or post-processing code in it
  // before or after compute() is called.
  virtual void encode() {
    //pre-processing code
    //
    compute();
    //post-processing code
    if (ctx_->profile_enabled()) {
      add_profile_op(op_.name(), op_.type());
    }
  }

  // compute(): implement IR either by NPU or CPU.
  virtual void compute() = 0;

  void restore_op(TensorOp& op) {
    op.CopyFrom(op_);
  }

protected:
  BackendContext* ctx_ = NULL;
  TensorOp &op_;
  TensorOp void_op_;
};

} // end namespace bmnet

#endif /* _TENSORINST_H_ */
