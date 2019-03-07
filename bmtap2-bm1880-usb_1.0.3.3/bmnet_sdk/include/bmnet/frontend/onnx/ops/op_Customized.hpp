/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_CUSTOMIZED_H_
#define _ONNX_LAYER_CUSTOMIZED_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class CustomizedOp : public OnnxOperator {
 public:
  explicit CustomizedOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  CustomizedOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~CustomizedOp() override = default;

  void setup(TensorOp *op) {
    ONNX_NAMESPACE::Node *pNode = getOnnxNode();
    LOG(INFO) << pNode->name() << " setup";

    if (pNode->name().empty()) {
      op->set_name(pNode->outputs()[0]->uniqueName());
    } else {
      op->set_name(pNode->name());
    }

    op->set_type("tg_customized");
    TGCustomizedParameter *param = op->mutable_tg_customized_param();
    param->set_sub_type(layer_name());

    // set bottom and top
    for (int i = 0; i < pNode->inputs().size(); i++) {
      auto input_name = pNode->inputs()[i]->uniqueName();
      op->add_bottom(input_name);
      TensorShape *input_shape = op->add_input_shape();
      const std::vector<ONNX_NAMESPACE::Dimension> in_dim = pNode->inputs()[i]->sizes();
      for (int i = 0; i < in_dim.size(); i++) {
        input_shape->add_dim(in_dim[i].dim);
      }
    }
    for (int i = 0; i < pNode->outputs().size(); i++) {
      auto output_name = pNode->outputs()[i]->uniqueName();
      op->add_top(output_name);
    }
  }

 private:
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_SOFTMAX_H_ */
