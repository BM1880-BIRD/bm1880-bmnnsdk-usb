/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
/*
 * bmnet/src/bmnet/frontend/onnx/ops/op_Softmax.cpp
 *
 * Copyright Bitmain Technologies Inc.
 * Written by:
 *   Wanwei CAI <wanwei.cai@bitmain.com>
 * Created Time: 2018-07-06 18:17
 */

#include "op_Elu.hpp"

namespace bmnet {

void EluOp::dump() {
  ONNX_NAMESPACE::Node *pNode = getOnnxNode();
  LOG(INFO) << pNode->name() << " param:";
}

void EluOp::codegen(TensorOp *op) {
  ONNX_NAMESPACE::Node *pNode = getOnnxNode();
  LOG(INFO) << pNode->name() << " codegen";

  const TensorShape &input_shape = op->input_shape(0);

  float alpha = 1.0;

  if (pNode->hasAttribute(ONNX_NAMESPACE::Symbol("alpha"))) {
   alpha = pNode->f(ONNX_NAMESPACE::Symbol("alpha"));
  }

  TensorShape *output_shape = op->add_output_shape();
  output_shape->CopyFrom(input_shape);
  output_shape->set_data_type_size(sizeof(int8_t));
   // set out_param
  TGCustomizedParameter* out_param = op->mutable_tg_customized_param();
  out_param->add_f32_param(alpha);
}

OnnxOperator *EluOp::makeOp(const ONNX_NAMESPACE::Node *node) {
  return new EluOp(ctx_, node);
}

}  // namespace bmnet
