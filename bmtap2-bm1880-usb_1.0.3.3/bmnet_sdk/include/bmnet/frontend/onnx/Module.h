//===- Module.h -----------------------------------------------------------===//
//
//                             The ONNC Project
//
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#ifndef ONNC_IR_MODULE_H
#define ONNC_IR_MODULE_H
#include <onnx/common/ir.h>
#include <bmnet/utils/common.hpp>
#include <map>
#include <memory>
#include <ostream>
#include <vector>

namespace bmnet {

/** \class Module
 *  \brief Rrepresentation of ONNX model
 */
class Module {
 public:
  using OpsetImport = std::map<std::string, int64_t>;
  using MetaDataMap = std::map<std::string, std::string>;

  class OnnxInfo {
   public:
    OnnxInfo();

    ~OnnxInfo() = default;

    void setIRVersion(int64_t pVersion) { m_IRVersion = pVersion; }

    int64_t getIRVersion() const { return m_IRVersion; }

    void setProducer(const std::string& pName, const std::string& pVersion);

    const std::string& getProducerName() const { return m_ProducerName; }

    void setProducerName(const std::string& pName) { m_ProducerName = pName; }

    const std::string& getProducerVersion() const { return m_ProducerVersion; }

    void setProducerVersion(const std::string& pVersion) { m_ProducerVersion = pVersion; }

    const std::string& getDomain() const { return m_Domain; }

    void setDomain(const std::string& pDomain) { m_Domain = pDomain; }

    int64_t getModelVersion() const { return m_ModelVersion; }

    void setModelVersion(int64_t pModelVersion) { m_ModelVersion = pModelVersion; }

    const std::string& getDocString() const { return m_DocString; }

    void setDocString(const std::string& pDocString) { m_DocString = pDocString; }

    /// print the information in @ref pOS
    void print(std::ostream& pOS) const;

    /// print the information to stderrs.
    void dump() const;

   private:
    int64_t m_IRVersion;
    std::string m_ProducerName;
    std::string m_ProducerVersion;
    std::string m_Domain;
    int64_t m_ModelVersion;
    std::string m_DocString;
  };

  using GraphIR = ONNX_NAMESPACE::Graph;

 public:
  /// default constructor. No graph IR is set.
  Module();

  /// delegation constructor.
  explicit Module(std::unique_ptr<ONNX_NAMESPACE::Graph> pGraph);

  /// Destructor. Check and delete IRs.
  /// Module responses for the life cycle of the delegated ONNX_NAMESPACE::Graph.
  ~Module();

  // move @ref pGraph from outside.
  Module& delegate(std::unique_ptr<ONNX_NAMESPACE::Graph> pGraph);

  // move @ref pGraph from outside.
  Module& delegate(ONNX_NAMESPACE::Graph* pGraph);

  std::shared_ptr<ONNX_NAMESPACE::Graph> getGraphIR() { return m_pOnnxGraph; }

  std::shared_ptr<const ONNX_NAMESPACE::Graph> getGraphIR() const { return m_pOnnxGraph; }

  bool hasGraphIR() const { return (0 != m_pOnnxGraph.use_count()); }

  std::vector<size_t> getModelInputDim() const;

  MetaDataMap& getMetaData() { return m_OnnxMetaData; }

  const MetaDataMap& getMetaData() const { return m_OnnxMetaData; }

  OpsetImport& getSetId() { return m_OnnxSetId; }

  const OpsetImport& getSetId() const { return m_OnnxSetId; }

  OnnxInfo& getOnnxInfo() { return m_OnnxInfo; }

  const OnnxInfo& getOnnxInfo() const { return m_OnnxInfo; }

  std::string& getOnnxWeightData() { return m_OnnxWeightData; }

  const std::string& getOnnxWeightData() const { return m_OnnxWeightData; }

  // print the whole module to @ref pOS.
  // NOLINTNEXTLINE
  void print(std::ostream& pOS) const;

  // NOLINTNEXTLINE
  template <typename PART>
  void print(std::ostream& pOS) const {
    assert(false && "no part to print!");
  }

  // NOLINTNEXTLINE
  template <typename PART>
  void print(std::ostream& pOS, const PART& pPart) const {
    assert(false && "no part to print!");
  }

  /// print the information to stderrs.
  void dump() const;

 private:
  // Graph IR field
  std::shared_ptr<ONNX_NAMESPACE::Graph> m_pOnnxGraph;
  OnnxInfo m_OnnxInfo;
  OpsetImport m_OnnxSetId;
  MetaDataMap m_OnnxMetaData;
  std::string m_OnnxWeightData;
};

// NOLINTNEXTLINE
template <>
void Module::print<Module::OpsetImport>(std::ostream& pOS) const;

// NOLINTNEXTLINE
template <>
void Module::print<Module::MetaDataMap>(std::ostream& pOS) const;

// NOLINTNEXTLINE
template <>
void Module::print(std::ostream& pOS, const ONNX_NAMESPACE::Value& pValue) const;

// NOLINTNEXTLINE
template <>
void Module::print(std::ostream& pOS, const ONNX_NAMESPACE::Node& pNode) const;

}  // namespace bmnet

#endif
