/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_BATCHNORMALIZATION_H_
#define _ONNX_LAYER_BATCHNORMALIZATION_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class BatchNormalizationOp : public OnnxOperator {
 public:
  explicit BatchNormalizationOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  BatchNormalizationOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~BatchNormalizationOp() override = default;

  std::string layer_name() override { return std::string("BatchNormalization"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
  void quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable) override;

  void appendWeight(std::string &pWeight) override;
  void buildMemOperands() override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_BATCHNORMALIZATION_H_ */
