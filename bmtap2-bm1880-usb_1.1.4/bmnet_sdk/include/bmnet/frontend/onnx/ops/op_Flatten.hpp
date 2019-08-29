/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_FLATTEN_H_
#define _ONNX_LAYER_FLATTEN_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class FlattenOp : public OnnxOperator {
 public:
  explicit FlattenOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  FlattenOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~FlattenOp() override = default;

  std::string layer_name() override { return std::string("Flatten"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;

  void appendWeight(std::string &pWeight) override{};
  void buildMemOperands() override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_FLATTEN_H_ */
