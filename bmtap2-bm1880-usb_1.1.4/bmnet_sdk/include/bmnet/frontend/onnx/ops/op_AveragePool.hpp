/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_AVERAGEPOOL_H_
#define _ONNX_LAYER_AVERAGEPOOL_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class AveragePoolOp : public OnnxOperator {
 public:
  explicit AveragePoolOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  AveragePoolOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~AveragePoolOp() override = default;

  std::string layer_name() override { return std::string("AveragePool"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
  void quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_AVERAGEPOOL_H_ */
