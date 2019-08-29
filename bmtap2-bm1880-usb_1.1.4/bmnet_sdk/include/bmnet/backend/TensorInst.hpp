/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _TENSORINST_H_
#define _TENSORINST_H_

#include <bmnet/proto/TensorOps.hpp>
#include <bmnet/backend/Instruction.hpp>
#include <bmnet/backend/BackendContext.hpp>
#include <bmnet/targets/plat-bm168x/BM168xBackendContext.hpp>
#include <bmnet/targets/cpu/cpu.hpp>

namespace bmnet {
//class BackendContext;

/// \brief Instances of this class represent a single tensor instrunction,
/// could be a TL instruction or a TG instruction.
class TensorInst : public Instruction {
public:
  TensorInst() {}

  TensorInst(TensorOp& op) : Instruction(op) {}

  TensorInst(BackendContext* ctx) : Instruction() {
    ctx_ = dynamic_cast<BM168xBackendContext*>(ctx);
  }

  TensorInst(BackendContext* ctx, TensorOp& op) : Instruction(op) {
    ctx_ = dynamic_cast<BM168xBackendContext*>(ctx);
  }

  ~TensorInst(void) override {}

  void set_backend_context(BackendContext* ctx) override {
    ctx_ = dynamic_cast<BM168xBackendContext*>(ctx);
  }

  // compute(): translate IR to instructions of target board.
  // you could add pre-processing or post-processing code in it
  // before or after compute() is called.
  void encode() override {
    //pre-processing code
    //
    ctx_->setCurrentInst(this);

    compute();
    //post-processing code
    if (ctx_->profile_enabled()) {
      add_profile_op(op_.name(), op_.type());
    }
  }

  // compute(): translate IR to instructions of target board.
  virtual void compute() = 0;

protected:
  BM168xBackendContext* ctx_;

  u64 get_global_neuron_base() {
    return ctx_->get_global_neuron_base();
  }

  u64 get_global_weight_base() {
    return ctx_->get_global_weight_base();
  }
};

} // end namespace bmnet

#endif /* _TENSORINST_H_ */
