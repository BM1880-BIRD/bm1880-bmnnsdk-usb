/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_STACK_H_
#define _ONNX_LAYER_STACK_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class StackOp : public OnnxOperator {
 public:
  explicit StackOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  StackOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~StackOp() override = default;

  std::string layer_name() override { return std::string("Stack"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_STACK_H_ */
