/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_GLOBALMAXPOOL_H_
#define _ONNX_LAYER_GLOBALMAXPOOL_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class GlobalMaxPoolOp : public OnnxOperator {
 public:
  explicit GlobalMaxPoolOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  GlobalMaxPoolOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~GlobalMaxPoolOp() override = default;

  std::string layer_name() override { return std::string("GlobalMaxPool"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
  void quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_GLOBALMAXPOOL_H_ */
