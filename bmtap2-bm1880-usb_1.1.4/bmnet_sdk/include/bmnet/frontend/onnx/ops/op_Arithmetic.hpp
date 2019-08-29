/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_ARITHMETIC_H_
#define _ONNX_LAYER_ARITHMETIC_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class ArithmeticOp : public OnnxOperator {
 public:
  explicit ArithmeticOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  ArithmeticOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~ArithmeticOp() override = default;

  std::string layer_name() override { return std::string("Arithmetic"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_ARITHMETIC_H_ */
