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

#include "op_LeakyRelu.hpp"
#include "bmnet/frontend/onnx/QuantizeHelper.hpp"

namespace bmnet {
static LayerCTable_t *getMutableLayerCtable(const std::string &name, NetCTable_t *net_ctable) {
  for (int i = 0; i < net_ctable->layer_size(); i++) {
    LayerCTable_t *layer = net_ctable->mutable_layer(i);
    if (layer->name() == name) {
      return layer;
    }
  }
  return nullptr;
}

static const LayerCTable_t *getLayerCtable(const std::string &name, const NetCTable_t *net_ctable) {
  for (int i = 0; i < net_ctable->layer_size(); i++) {
    const LayerCTable_t &layer = net_ctable->layer(i);
    for (int j = 0; j < layer.blob_param_size(); j++) {
      if (layer.blob_param(j).name() == name) {
        return &layer;
      }
    }
  }
  return nullptr;
}

static bool getTensorThreshold(const LayerCTable_t *layer_ctable, const std::string &name,
                               float *pThres) {
  bool is_find_thres = false;
  for (int i = 0; i < layer_ctable->blob_param_size(); i++) {
    LOG(INFO) << "name = " << name << ", blob_name = " << layer_ctable->blob_param(i).name();
    if (name == layer_ctable->blob_param(i).name()) {
      *pThres = layer_ctable->blob_param(i).threshold_y();
      is_find_thres = true;
      break;
    }
  }
  return is_find_thres;
}

static int getRightShift(const std::vector<float> &tensor, float scale) {
  int m = 0;
  // Find max abs in the tensor.
  auto cmp = [](float pA, float pB) { return (std::abs(pA) < std::abs(pB)); };
  float abs_max = std::abs(*std::max_element(tensor.begin(), tensor.end(), cmp));
  float data_max = abs_max * scale;

  assert(data_max > 0);

  while (data_max < 64) {
    m += 1;
    data_max *= 2;
  }
  while (data_max >= 128) {
    LOG(FATAL) << "data_max = " << data_max
               << "Error in quantize_right_shift: rshift will be negative...";
  }
  return m;
}

void LeakyReluOpPlugin::dump() {
  ONNX_NAMESPACE::Node *pNode = getOnnxNode();
  LOG(INFO) << pNode->name() << " param:";
}

void LeakyReluOpPlugin::codegen(TensorOp *op) {
  ONNX_NAMESPACE::Node *pNode = getOnnxNode();
  LOG(INFO) << pNode->name() << " codegen";
  op->set_type("tg_leakyrelu");
  const TensorShape &input_shape = op->input_shape(0);

  float alpha = 0.0;
  if (pNode->hasAttribute(ONNX_NAMESPACE::Symbol("alpha"))) {
    auto &f = pNode->f(ONNX_NAMESPACE::Symbol("alpha"));
    alpha = f;
  }

  TensorShape *output_shape = op->add_output_shape();
  output_shape->CopyFrom(input_shape);

   // set out_param
  TGCustomizedParameter* out_param = op->mutable_tg_customized_param();
  out_param->add_f32_param(alpha);
}

void LeakyReluOpPlugin::quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable) {
  ONNX_NAMESPACE::Node *node = getOnnxNode();
  std::string inputName = node->inputs()[0]->uniqueName();
  std::string outputName = node->output()->uniqueName();
  const auto *inputCtable = getLayerCtable(inputName, NetCTable);
  auto *outputCtable = getMutableLayerCtable(outputName, NetCTable);
  float alpha = 0.0;
  if (node->hasAttribute(ONNX_NAMESPACE::Symbol("alpha"))) {
    auto &f = node->f(ONNX_NAMESPACE::Symbol("alpha"));
    alpha = f;
  }

  // Get input threshold
  float thresX;
  if (!getTensorThreshold(inputCtable, inputName, &thresX)) {
    LOG(FATAL) << "count not find threshold in: " << inputName;
  }
  // Get output threshold
  float thresY;
  if (!getTensorThreshold(outputCtable, outputName, &thresY)) {
    LOG(FATAL) << "count not find threshold in: " << outputName;
  }
  std::vector<float> const_tensor(1, 1.0);
  int gt_rightShift = getRightShift(const_tensor, thresX / thresY);
  int gt_multiplier =
      static_cast<int>(std::floor(((thresX / thresY) * (1 << gt_rightShift)) + 0.5));

  outputCtable->mutable_relu_param()->set_gt_right_shift_width(gt_rightShift);
  outputCtable->mutable_relu_param()->set_gt_scale(gt_multiplier);

  int le_rightShift = getRightShift(const_tensor, alpha * thresX / thresY);
  int le_multiplier =
      static_cast<int>(std::floor(((alpha * thresX / thresY) * (1 << le_rightShift)) + 0.5));

  outputCtable->mutable_relu_param()->set_le_right_shift_width(le_rightShift);
  outputCtable->mutable_relu_param()->set_le_scale(le_multiplier);
}

OnnxOperator *LeakyReluOpPlugin::makeOp(const ONNX_NAMESPACE::Node *node) {
  return new LeakyReluOpPlugin(ctx_, node);
}

}  // namespace bmnet
