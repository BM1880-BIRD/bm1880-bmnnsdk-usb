/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <bmnet/proto/TensorOps.hpp>
#include <bmnet/backend/BackendContext.hpp>

namespace bmnet {
//class BackendContext;

/// \brief Instances of this class represent a single tensor instrunction,
/// could be a TL instruction or a TG instruction.
class Instruction {
public:
  Instruction() : op_(void_op_) {}
  Instruction(TensorOp& op) : op_(op) {}
  virtual ~Instruction(void) {}

  void set_op(TensorOp& op) {
    op_ = op;
  }

  const std::string& type() const {
    return op_.type();
  }

  const std::string& name() const {
    return op_.name();
  }

  bool IsPluginInstruction() { return is_plugin_instruction; }
  void SetPluginInstruction() { is_plugin_instruction = true; }

  // setup backend context after instance is constucted.
  virtual void set_backend_context(BackendContext* ctx) = 0;

  // inst_name(): setup IR's type name.
  virtual std::string inst_name() = 0;

  virtual std::string alias() { return inst_name(); }

  // dump(): print details of IR
  virtual void dump() = 0;

  // encode(): translate IR to instructions of target board.
  virtual void encode() = 0;

  void restore_op(TensorOp& op) {
    op.CopyFrom(op_);
  }

protected:
  bool is_plugin_instruction = false;
  TensorOp &op_;
  TensorOp void_op_;
};

} // end namespace bmnet

#endif /* _INSTRUCTION_H_ */
