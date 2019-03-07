/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_IDENTITY_H_
#define _ONNX_LAYER_IDENTITY_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class IdentityOp : public OnnxOperator {
 public:
  explicit IdentityOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  IdentityOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~IdentityOp() override = default;

  std::string layer_name() override { return std::string("Identity"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_IDENTITY_H_ */
