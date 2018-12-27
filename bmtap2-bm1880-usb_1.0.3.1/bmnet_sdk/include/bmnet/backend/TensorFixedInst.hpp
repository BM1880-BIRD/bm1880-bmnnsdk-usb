/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _TENSORFIXEDINST_H_
#define _TENSORFIXEDINST_H_

#include <bmnet/backend/TensorInst.hpp>
#include <bmnet/calibration.pb.h>

namespace bmnet {
class BackendContext;

class TensorFixedInst : public TensorInst {
public:
  TensorFixedInst() : TensorInst() {}
  TensorFixedInst(TensorOp &op) : TensorInst(op) {}
  TensorFixedInst(BackendContext *ctx) : TensorInst(ctx) {}
  TensorFixedInst(BackendContext *ctx, TensorOp &op) : TensorInst(ctx, op){};

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

  void encode() {
    std::string debug_string = "START|" + op_.name() +"|" + op_.type();
    arm_sync(debug_string.c_str());

    compute();
  }

protected:
  LayerCalibrationParameter m_calibrationParameter;
  std::vector<LayerCalibrationParameter> m_inputCalibrationParameter;
};

} // end namespace bmnet

#endif /* _TENSORFIXEDINST_H_ */
