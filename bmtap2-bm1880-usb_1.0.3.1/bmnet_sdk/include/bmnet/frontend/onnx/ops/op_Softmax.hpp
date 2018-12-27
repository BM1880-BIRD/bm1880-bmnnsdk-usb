/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_SOFTMAX_H_
#define _ONNX_LAYER_SOFTMAX_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class SoftmaxOp : public OnnxOperator {
 public:
  explicit SoftmaxOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  SoftmaxOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~SoftmaxOp() override = default;

  std::string layer_name() override { return std::string("Softmax"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_SOFTMAX_H_ */
