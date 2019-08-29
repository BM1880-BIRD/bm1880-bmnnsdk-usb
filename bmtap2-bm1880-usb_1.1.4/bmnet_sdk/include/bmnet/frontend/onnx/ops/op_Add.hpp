/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_ADD_H_
#define _ONNX_LAYER_ADD_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>
#include <bmnet/frontend/onnx/ops/op_Arithmetic.hpp>

namespace bmnet {

class AddOp : public ArithmeticOp {
 public:
  explicit AddOp(FrontendContext *ctx) : ArithmeticOp(ctx) {}
  AddOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : ArithmeticOp(ctx, pOnnxNode) {}
  ~AddOp() override = default;

  std::string layer_name() override { return std::string("Add"); }

  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
  void quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_ADD_H_ */
