/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_LEAKYRELU_H_
#define _ONNX_LAYER_LEAKYRELU_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class LeakyReluOp : public OnnxOperator {
 public:
  explicit LeakyReluOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  LeakyReluOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~LeakyReluOp() override = default;

  std::string layer_name() override { return std::string("LeakyRelu"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_LEAKYRELU_H_ */
