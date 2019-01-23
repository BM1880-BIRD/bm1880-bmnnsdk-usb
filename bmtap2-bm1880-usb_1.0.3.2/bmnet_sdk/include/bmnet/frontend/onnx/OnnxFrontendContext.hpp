/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_FRONTEND_CONTEXT_H_
#define _ONNX_FRONTEND_CONTEXT_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <bmnet/frontend/onnx/Module.h>
#include <bmnet/frontend/FrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {
class OnnxNetParser;
/// Compile Onnx model into a bmnet prototxt file.
class OnnxFrontendContext : public FrontendContext {
 public:
  explicit OnnxFrontendContext(const char *model_path);

  explicit OnnxFrontendContext(const std::string &model_str);

  // used by unittest, or user build onnx graph in runtime
  explicit OnnxFrontendContext(int input_n, int input_c, int input_h, int input_w);

  OnnxFrontendContext() = delete;

  ~OnnxFrontendContext() override;

  void setDimensions(Module *module);

  OnnxNetParser *getOnnxNetParser() { return parser_; }

  void extractFromFile(Module *module);

  void extractFromString(Module *module);

  const std::vector<MemOperand *> &mem_operands() const { return mem_operands_; }

  MemOperand *getMemOperand(const ONNX_NAMESPACE::Value *value);
  // create a new MemOperand by ONNX_NAMESPACE::Value.
  // return nullptr if it has been created.
  MemOperand *createMemOperand(const ONNX_NAMESPACE::Value *value);

  void appendWeight(const ONNX_NAMESPACE::Value *value, std::string &weight);  // NOLINT
  template <typename DataType>
  void appendWeight(const ONNX_NAMESPACE::Value *value, const std::vector<DataType> &value_data,
                    std::string &weight) {
    if (!shouldAppendWeight(value)) {
      return;
    }
    OnnxOperator::appendWeight(value_data, weight);
  }

  const std::vector<OnnxOperator *> &onnx_operators() const { return onnx_operators_; }

  void addOnnxOperator(OnnxOperator *onnx_operator) { onnx_operators_.push_back(onnx_operator); }

  void getInputDimension(int *n, int *c, int *h, int *w) const;

  size_t sizeOfTensorType(const ONNX_NAMESPACE::TensorProto_DataType &type);

  NetParameter *convert(void *orig_net, TensorShape *input_shape) override;

  void registerCustomizedLayer(void *layer) override;

 private:
  bool shouldAppendWeight(const ONNX_NAMESPACE::Value *value);

  OnnxNetParser *parser_;
  const char *model_path_;
  const std::string *model_str_;
  std::vector<MemOperand *> mem_operands_;
  std::vector<OnnxOperator *> onnx_operators_;
  std::unordered_set<const ONNX_NAMESPACE::Value *> processed_weight_;
  int input_n_{0}, input_c_{0}, input_h_{0}, input_w_{0};
};

}  // namespace bmnet

#endif /* _ONNX_FRONTEND_CONTEXT_H_ */
