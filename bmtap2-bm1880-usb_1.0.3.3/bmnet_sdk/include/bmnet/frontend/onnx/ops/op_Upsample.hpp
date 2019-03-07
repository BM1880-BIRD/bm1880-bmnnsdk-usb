/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_UPSAMPLE_
#define _ONNX_LAYER_UPSAMPLE_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class UpsampleOp : public OnnxOperator {
 public:
  explicit UpsampleOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  UpsampleOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~UpsampleOp() override = default;

  std::string layer_name() override { return std::string("Upsample"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_UPSAMPLE_ */
