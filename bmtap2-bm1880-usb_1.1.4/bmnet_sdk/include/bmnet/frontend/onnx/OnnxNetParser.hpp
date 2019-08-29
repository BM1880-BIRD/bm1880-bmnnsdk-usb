/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_NET_PARSER_H_
#define _ONNX_NET_PARSER_H_

#include <bmnet/codegen/Graph.hpp>
#include <bmnet/frontend/NetParser.hpp>
#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <map>
#include <utility>
#include <vector>

namespace bmnet {

class OnnxOperator;

/// Parse network and generate TensorOps
class OnnxNetParser : public NetParser {
 public:
  OnnxNetParser();
  explicit OnnxNetParser(OnnxFrontendContext *ctx);
  ~OnnxNetParser() override = default;

  void parse_net(Module *module);

  // target-indep optimizations
  void optimizationPasses(Module *module);

  // onnx opt Pass
  void removeUnusedNodesPass(Module *module);
  void optimizeOnnxPass(Module *module);
  void optimizeBnConvPass(Module *module);
  void unrollLSTMPass(Module *module);
  void removeTransposePass(Module *module);
  void fuseSqueezePass(Module *module);
  void fuseUnsqueezePass(Module *module);
  void convert2eltwisePass(Module *module);
  void fusePadPass(Module *module);
  void fuseChArithPass(Module *module);
  void convertToNCHWPass(Module *module);
  void removeRedudantOpPass(Module *module);
  void updateGraphOutputSizePass(Module *module);
  void fixModelAfterShapeInferPass(Module *module);
  void convertDoubleWeightPass(Module *module);
  void genONNCNodeNamePass(Module *module);
  void fuseMulAdd2BNPass(Module *module);
  bool convertAutoPadPass(Module *module);
  void shuffleChannelPass(Module *module);
  void convertDownsampleMaxPoolToDepthwiseConvPass(Module *module);
  void convertReduceMean2GlobalAveragePoolPass(Module *module);
  void convertReduceMax2GlobalMaxPoolPass(Module *module);
  void convertConvTransposeOutputShapeAttrib(Module *module);

  // all onnx opt passes
  void optPasses(Module *module);

  // bmnet-dep pass
  void insertSplitPass(Module *module);
  void insertMultiInputPass(Module *module);
  void opGenPass(Module *module);
  void irGenPass(Module *module);
  void memOpBuildPass(Module *module);
  void globalMemAllocPass(Module *module);
  void weightGenPass(Module *module);
  void quantizePass(Module *module);
  void fuseBatchnormPass(Module *module);
  void add_support_ops(const std::string &layer_name) {
    supported_ops.emplace(ONNX_NAMESPACE::Symbol(layer_name));
  }

 private:
  void writeOutOnnxProto(Module *module, const char *name);

  // Remove all custom weight/attribute in op. This is usually used before exporting onnx model.
  void standardizeOpPass(Module *module);

  void setup_layer_input(Node *node);
  void setup_layer_output(Node *node, OnnxOperator *onnx_operator, int data_type_size);
  std::vector<InputInfoPair> getInputInfo(Module *module, const std::vector<TensorShape> &shapes);
  OnnxOperator *makeOnnxOperator(const ONNX_NAMESPACE::Node *node);

 private:
  std::vector<std::unique_ptr<OnnxOperator>> opList;
  std::unordered_set<ONNX_NAMESPACE::Symbol> supported_ops;
};

}  // namespace bmnet
#endif /* _ONNX_NET_PARSER_H_ */
