/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _TENSORFIXEDINST_H_
#define _TENSORFIXEDINST_H_

#include <bmnet/backend/Instruction.hpp>
#include <bmnet/calibration.pb.h>
#include <bmnet/targets/plat-bm188x/BM188xBackendContext.hpp>
#include <bmnet/targets/cpu/cpu.hpp>

namespace bmnet {
class BackendContext;

class TensorFixedInst : public Instruction {
public:
  TensorFixedInst() : Instruction() {}
  TensorFixedInst(TensorOp &op) : Instruction(op) {}
  TensorFixedInst(BackendContext *ctx) : Instruction() {
    ctx_ = dynamic_cast<BM188xBackendContext*>(ctx);
  }
  TensorFixedInst(BackendContext *ctx, TensorOp &op) : Instruction(op){
    ctx_ = dynamic_cast<BM188xBackendContext*>(ctx);
  };

  void SetCalibrationParameter(
      const LayerCalibrationParameter &calibration_parameter) {
    m_calibrationParameter = calibration_parameter;
  }

  void AddInputCalibrationParameter(
      const LayerCalibrationParameter &calibration_parameter) {
    m_inputCalibrationParameter.push_back(calibration_parameter);
  }

  void ClearInputCalibrationParameter() {
    std::vector<LayerCalibrationParameter>().swap(m_inputCalibrationParameter);
  }

  void encode() override {
    ctx_->set_layer_id(op_.id());

    compute();

    //post-processing code
    if (ctx_->profile_enabled()) {
      add_profile_op(ctx_, op_);
    }
  }

  void set_backend_context(BackendContext* ctx) override {
    ctx_ = dynamic_cast<BM188xBackendContext*>(ctx);
  }

  virtual void compute() = 0;

protected:
  LayerCalibrationParameter m_calibrationParameter;
  std::vector<LayerCalibrationParameter> m_inputCalibrationParameter;
  BM188xBackendContext* ctx_;

  u64 get_global_neuron_base() {
    return ctx_->get_global_neuron_base();
  }

  u64 get_global_weight_base() {
    return ctx_->get_global_weight_base();
  }
};

} // end namespace bmnet

#endif /* _TENSORFIXEDINST_H_ */
