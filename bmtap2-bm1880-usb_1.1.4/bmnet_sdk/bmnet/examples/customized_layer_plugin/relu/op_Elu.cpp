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

void EluOpPlugin::dump() {
  ONNX_NAMESPACE::Node *pNode = getOnnxNode();
  LOG(INFO) << pNode->name() << " param:";
}

void EluOpPlugin::codegen(TensorOp *op) {
  // Setup your op type
  op->set_type("tg_elu");
  ONNX_NAMESPACE::Node *pNode = getOnnxNode();
  LOG(INFO) << pNode->name() << " codegen";

  const TensorShape &input_shape = op->input_shape(0);

  float alpha = 1.0;

  if (pNode->hasAttribute(ONNX_NAMESPACE::Symbol("alpha"))) {
   alpha = pNode->f(ONNX_NAMESPACE::Symbol("alpha"));
  }

  TensorShape *output_shape = op->add_output_shape();
  output_shape->CopyFrom(input_shape);

   // set out_param
  TGCustomizedParameter* out_param = op->mutable_tg_customized_param();
  out_param->add_f32_param(alpha);
}

OnnxOperator *EluOpPlugin::makeOp(const ONNX_NAMESPACE::Node *node) {
  return new EluOpPlugin(ctx_, node);
}

}  // namespace bmnet
