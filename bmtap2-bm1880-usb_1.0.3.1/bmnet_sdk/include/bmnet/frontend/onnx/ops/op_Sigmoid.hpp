/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_SIGMOID_H_
#define _ONNX_LAYER_SIGMOID_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class SigmoidOp : public OnnxOperator {
 public:
  explicit SigmoidOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  SigmoidOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~SigmoidOp() override = default;

  std::string layer_name() override { return std::string("Sigmoid"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
  void quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_SIGMOID_H_ */
