/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_SQUEEZE_H_
#define _ONNX_LAYER_SQUEEZE_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class SqueezeOp : public OnnxOperator {
 public:
  explicit SqueezeOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  SqueezeOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~SqueezeOp() override = default;

  std::string layer_name() override { return std::string("Squeeze"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_SQUEEZE_H_ */
