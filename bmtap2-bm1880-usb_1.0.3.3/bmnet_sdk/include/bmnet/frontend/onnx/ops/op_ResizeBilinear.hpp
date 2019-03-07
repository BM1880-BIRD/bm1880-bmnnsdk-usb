/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_RESIZE_BILINEAR_H_
#define _ONNX_LAYER_RESIZE_BILINEAR_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class ResizeBilinearOp : public OnnxOperator {
 public:
  explicit ResizeBilinearOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  ResizeBilinearOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~ResizeBilinearOp() override = default;

  std::string layer_name() override { return std::string("ResizeBilinear"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;

  void buildMemOperands() override;
  void appendWeight(std::string &pWeight) override;

 private:
  ONNX_NAMESPACE::Value *addExtraWeight();
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_RESIZE_BILINEAR_H_ */
