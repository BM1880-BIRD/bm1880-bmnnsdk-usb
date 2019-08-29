/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_LEAKYRELU_CUSTOMIZED_H_
#define _ONNX_LAYER_LEAKYRELU_CUSTOMIZED_H_

#include "bmnet/frontend/onnx/OnnxFrontendContext.hpp"
#include "bmnet/frontend/onnx/OnnxOperator.hpp"
#include "bmnet/frontend/onnx/ops/op_Customized.hpp"

namespace bmnet {

class LeakyReluOpPlugin : public CustomizedOp {
 public:
  explicit LeakyReluOpPlugin(FrontendContext *ctx) : CustomizedOp(ctx) {}
  LeakyReluOpPlugin(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode) : CustomizedOp(ctx, pOnnxNode) {}
  ~LeakyReluOpPlugin() override = default;

  std::string layer_name() override { return std::string("LeakyRelu"); }

  void dump() override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
  void quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable) override;

 private:
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_SOFTMAX_H_ */
