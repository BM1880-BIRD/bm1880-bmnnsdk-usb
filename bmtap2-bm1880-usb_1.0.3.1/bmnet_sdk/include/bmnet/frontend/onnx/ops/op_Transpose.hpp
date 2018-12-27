/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_TRANSPOSE_H_
#define _ONNX_LAYER_TRANSPOSE_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class TransposeOp : public OnnxOperator {
 public:
  explicit TransposeOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  TransposeOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~TransposeOp() override = default;

  std::string layer_name() override { return std::string("Transpose"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_TRANSPOSE_H_ */
