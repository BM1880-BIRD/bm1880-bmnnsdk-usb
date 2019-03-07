/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_UNSQUEEZE_H_
#define _ONNX_LAYER_UNSQUEEZE_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class UnsqueezeOp : public OnnxOperator {
 public:
  explicit UnsqueezeOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  UnsqueezeOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~UnsqueezeOp() override = default;

  std::string layer_name() override { return std::string("Unsqueeze"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_UNSQUEEZE_H_ */
