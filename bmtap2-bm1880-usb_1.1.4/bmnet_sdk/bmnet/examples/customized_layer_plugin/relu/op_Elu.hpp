/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_ELU_H_
#define _ONNX_LAYER_ELU_H_

#include "bmnet/frontend/onnx/OnnxFrontendContext.hpp"
#include "bmnet/frontend/onnx/OnnxOperator.hpp"
#include "bmnet/frontend/onnx/ops/op_Customized.hpp"

namespace bmnet {

class EluOpPlugin : public CustomizedOp {
 public:
  explicit EluOpPlugin(FrontendContext *ctx) : CustomizedOp(ctx) {}
  EluOpPlugin(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode) : CustomizedOp(ctx, pOnnxNode) {}
  ~EluOpPlugin() override = default;

  std::string layer_name() override { return std::string("Elu"); }

  void dump() override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;

 private:
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_SOFTMAX_H_ */
