/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_OPERATOR_H_
#define _ONNX_OPERATOR_H_

#include <bmnet/calibration.pb.h>
#include <onnx/common/ir.h>
#include <bmnet/frontend/Layer.hpp>
#include <bmnet/frontend/onnx/OnnxUtils.hpp>

namespace bmnet {

using MemTable = std::map<std::string, uint64_t>;
using qWeight_t = std::unordered_map<std::string, std::vector<int8_t>>;
using qBias_t = std::unordered_map<std::string, std::vector<int16_t>>;
using NetCTable_t = NetCalibrationParameter;
using LayerCTable_t = LayerCalibrationParameter;

enum class MemType { NEURON, WEIGHT };

struct MemOperand {
  std::string m_Name;
  uint64_t m_Addr;
  size_t m_Count;
  size_t m_Size;
  ONNX_NAMESPACE::TensorProto_DataType m_Type;
  MemType m_MemType;
  const ONNX_NAMESPACE::Value *m_Value;

  MemOperand(std::string pName, const ONNX_NAMESPACE::Value *pValue, MemType pMemType)
      : m_Name(pName),
        m_Addr(0x0),
        m_Size(0),
        m_Type(pValue->elemType()),
        m_MemType(pMemType),
        m_Value(pValue) {
    m_Count = 1;
    auto &dim = pValue->sizes();

    int elem_size = 0;
    if (pValue->elemType() == ONNX_NAMESPACE::TensorProto_DataType_FLOAT) {
      elem_size = sizeof(float);
    } else if (pValue->elemType() == ONNX_NAMESPACE::TensorProto_DataType_INT64) {
      elem_size = sizeof(int64_t);
    } else if (pValue->elemType() == ONNX_NAMESPACE::TensorProto_DataType_INT16) {
      elem_size = sizeof(int16_t);
    } else if (pValue->elemType() == ONNX_NAMESPACE::TensorProto_DataType_INT8) {
      elem_size = sizeof(int8_t);
    } else if (pValue->elemType() == ONNX_NAMESPACE::TensorProto_DataType_UNDEFINED) {
      // TODO Why undefined exits.
      LOG(WARNING) << "Undefined tensor data type!";
    } else {
      // Not supported.
      LOG(FATAL) << pValue->elemType();
    }
    for (size_t i = 0; i < dim.size(); i++) {
      m_Count *= dim[i].dim;
    }
    m_Count *= elem_size;
  }
};

std::ostream &operator<<(std::ostream &pOS, const MemOperand &pMem);  // NOLINT

class OnnxFrontendContext;

class OnnxOperator : public Layer {
 public:
  static MemType getMemType(const ONNX_NAMESPACE::Value *pValue);

  static void appendWeight(const MemOperand &mem_operand, std::string &output_weight);
  template <typename DataType>
  static void appendWeight(const std::vector<DataType> &weight_data, std::string &output_weight) {
    size_t size = weight_data.size() * sizeof(DataType);
    std::string raw(reinterpret_cast<const char *>(weight_data.data()), size);
    output_weight.append(raw);
  }

  explicit OnnxOperator(FrontendContext *ctx) : Layer(ctx) {}
  OnnxOperator(FrontendContext *ctx, const ONNX_NAMESPACE::Node *onnx_node)
      : Layer(ctx), onnx_node_(onnx_node) {
    onnx_graph_ = onnx_node->owningGraph();
  }

  void init();
  void debug();

  // setter function
  void setOnnxGraph(const ONNX_NAMESPACE::Graph *onnx_graph) { onnx_graph_ = onnx_graph; }
  void setOnnxNode(const ONNX_NAMESPACE::Node *onnx_node) { onnx_node_ = onnx_node; }
  MemOperand *addMemOperand(const ONNX_NAMESPACE::Value *pValue, std::string &pWeight);  // NOLINT

  // getter function
  const ONNX_NAMESPACE::Graph *getOnnxGraph() const { return onnx_graph_; }
  const ONNX_NAMESPACE::Node *getOnnxNode() const { return onnx_node_; }
  ONNX_NAMESPACE::Graph *getOnnxGraph() { return const_cast<ONNX_NAMESPACE::Graph *>(onnx_graph_); }
  ONNX_NAMESPACE::Node *getOnnxNode() { return const_cast<ONNX_NAMESPACE::Node *>(onnx_node_); }
  OnnxFrontendContext *getOnnxFrontendContext();
  TensorOp *getLayerParam() { return &layer_param_; }

  void setup(TensorOp *op) override = 0;
  virtual OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) = 0;
  virtual void appendWeight(std::string &pWeight);  // NOLINT
  // default buildMemOpernds is useful for n inputs and 1 output operator
  virtual void buildMemOperands();
  virtual void quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable) {}

 protected:
  const ONNX_NAMESPACE::Node *onnx_node_;
  const ONNX_NAMESPACE::Graph *onnx_graph_;
  TensorOp layer_param_;
};

}  // end namespace bmnet

#endif /* _ONNX_OPERATOR_H_ */
