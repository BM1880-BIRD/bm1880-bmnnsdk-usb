/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_UTILS_HPP_
#define _ONNX_UTILS_HPP_

#include <bmnet/frontend/onnx/Module.h>
#include <onnx/common/ir.h>
#include <onnx/common/ir_pb_converter.h>
#include <onnx/common/tensor.h>
#include <string>

namespace bmnet {

bool is_tensor(ONNX_NAMESPACE::Value *value);

void extract_onnxmodel(const char *model_path, Module *module);

void extract_onnxmodel(const std::string &model_str, Module *module);

void exportModelProto(const Module &module, ONNX_NAMESPACE::ModelProto *proto);

void updateModule(const ONNX_NAMESPACE::ModelProto &proto, Module *module);

const ONNX_NAMESPACE::Tensor *getInitializerTensor(const std::string &name,
                                                   const ONNX_NAMESPACE::Graph &graph);

template <typename DataType>
std::vector<DataType> getTensorData(const std::string &pName, const ONNX_NAMESPACE::Graph *pGraph);

#define declare_get_tensor_data(ValueType)                                  \
  template <>                                                               \
  std::vector<ValueType> getTensorData<ValueType>(const std::string &pName, \
                                                  const ONNX_NAMESPACE::Graph *pGraph);
declare_get_tensor_data(float);
declare_get_tensor_data(double);
declare_get_tensor_data(int8_t);
declare_get_tensor_data(int16_t);
declare_get_tensor_data(int32_t);
declare_get_tensor_data(int64_t);
declare_get_tensor_data(uint64_t);
#undef decleare_get_tensor_data

void serializeToString(std::string &output, const Module &pModule);  // NOLINT

void replace_input(ONNX_NAMESPACE::Tensor &W, int idx, ONNX_NAMESPACE::Node *node,  // NOLINT
                   ONNX_NAMESPACE::Graph *graph);

void checkEqual(const ONNX_NAMESPACE::Tensor *pTensor, float compare_value);

void checkNAN(const ONNX_NAMESPACE::Tensor *pTensor);

size_t getTotalCount(const std::vector<int64_t> &dim);

size_t getTotalCount(const std::vector<ONNX_NAMESPACE::Dimension> &dim);

inline float *getTensorFloat(ONNX_NAMESPACE::Tensor &tensor) {  // NOLINT
  if (tensor.is_raw_data()) {
    // FIXME ugly casting, std::string::data return const char*
    return reinterpret_cast<float *>(const_cast<char *>((tensor.raw().data())));
  } else {
    return tensor.floats().data();
  }
}

}  // namespace bmnet

#endif  // _ONNX_UTILS_HPP_
