/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_LSTMUNIT_H_
#define _ONNX_LAYER_LSTMUNIT_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class LSTMUnitOp : public OnnxOperator {
 public:
  explicit LSTMUnitOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  LSTMUnitOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~LSTMUnitOp() override = default;

  std::string layer_name() override { return std::string("LSTMUnit"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;

  void appendWeight(std::string &pWeight) override;
  void buildMemOperands() override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_LSTMUNIT_H_ */
