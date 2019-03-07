/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_DIV_H_
#define _ONNX_LAYER_DIV_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>
#include <bmnet/frontend/onnx/ops/op_Arithmetic.hpp>

namespace bmnet {

class DivOp : public ArithmeticOp {
 public:
  explicit DivOp(FrontendContext *ctx) : ArithmeticOp(ctx) {}
  DivOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : ArithmeticOp(ctx, pOnnxNode) {}
  ~DivOp() override = default;

  std::string layer_name() override { return std::string("Div"); }

  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_DIV_H_ */
