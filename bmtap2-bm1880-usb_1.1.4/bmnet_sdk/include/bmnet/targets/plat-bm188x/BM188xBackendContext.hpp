/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM188X_BACKEND_CONTEXT_H_
#define _BM188X_BACKEND_CONTEXT_H_

#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <bmkernel/bm1880/bmkernel_1880.h>
#include <bmnet/calibration.pb.h>
#include <bmnet/backend/BackendContext.hpp>
#include <bmnet/backend/Instruction.hpp>

#include <bmkernel/bm1880/bmkernel_1880.h>

namespace bmnet {

struct CalibrationConfig {
  float threshold;
  int rshift;
};

/// Writes BM188x machine code to a stream.
class BM188xBackendContext : public BackendContext {
 public:
  BM188xBackendContext(int chip_ver, int nodechip_num);
  BM188xBackendContext(int chip_ver, int nodechip_num, std::vector<int8_t> &weight);
  ~BM188xBackendContext() override;

  virtual void parallel_enable() const = 0;
  virtual void parallel_disable() const = 0;
  virtual void set_layer_id(u16 layer_id) const = 0;
  virtual int layer_id() const = 0;

  void build(NetParameter &net, const char *term_layer = nullptr) override;
  void enter() override;
  void exit() override;

  void registerInstruction(Instruction *inst) override;
  void update_weight(std::vector<int8_t> &weight);
  void ImportCalibrationTable(const char *ctableName);
  void ImportCalibrationTableFromFrontend(const char *ctableName,
                                          const NetCalibrationParameter &param);

  u64 get_global_neuron_base() { return global_neuron_base_; }
  u64 get_global_weight_base() { return global_weight_base_; }

  void *weight() { return weight_; }
  uint64_t weight_size() { return weight_size_; }
  int8_t read_weight(uint64_t offset);

  const LayerCalibrationParameter *GetLayerCalibrationParameter(const std::string &name) {
    for (int i = 0; i < m_netCalibrationParameter.layer_size(); i++) {
      const LayerCalibrationParameter &layer = m_netCalibrationParameter.layer(i);
      if (layer.name() == name) {
        return &layer;
      }
      for (int j = 0; j < layer.blob_param_size(); j++) {
        if (layer.blob_param(j).name() == name) {
          return &layer;
        }
      }
    }
    return nullptr;
  }
  float GetBlobCalibrationThreshold(const std::string &layerName,
                                    const std::string &blobName) override {
    std::cout << "\tFinding blob " << blobName << " inside " << layerName << "." << std::endl;
    float threshold = 0;
    int count = 0;
    for (int i = 0; i < m_netCalibrationParameter.layer_size(); i++) {
      const LayerCalibrationParameter &layer = m_netCalibrationParameter.layer(i);
      if (layerName == "" || layer.name() == layerName) {
        for (int j = 0; j < layer.blob_param_size(); j++) {
          const BlobParameter &blob = layer.blob_param(j);
          if (blob.name() == blobName) {
            threshold = blob.threshold_y();
            count++;
          }
        }
      }
    }

    if (count == 0) {
      for (int i = 0; i < m_netCalibrationParameter.layer_size(); i++) {
        const LayerCalibrationParameter &layer = m_netCalibrationParameter.layer(i);
        for (int j = 0; j < layer.blob_param_size(); j++) {
          const BlobParameter &blob = layer.blob_param(j);
          if (blob.name() == blobName) {
            threshold = blob.threshold_y();
            count++;
          }
        }
      }
    }

    if (count == 1) {
      return threshold;
    }

    LOG(FATAL) << "(layer, blob) = ( " << layerName << ", " << blobName
               << ") not found. Please check blob&layer name.";
  }

  void ImportInput(const std::string &input_file, const std::vector<int> &input_shape);
  float *ExportInputFp32();
  int8_t *ExportInputI8();
#ifdef ENABLE_CAFFE_GOLDEN
  void TurnOffCaffeGolden() { caffe_golden_is_on = false; }
  bool IsCaffeGoldenOn() { return caffe_golden_is_on; }
  void CaffeCmpOpt(bool val);
  void ImportCaffeTest(const std::string &caffe_proto, const std::string &caffe_weight);
  void set_input_from_caffe(bool);
  bool input_from_caffe();
  void caffe_prepare();
  const int8_t *caffe_topBlob(const std::string &layername, int layer_output_id);
  const int8_t *caffe_bottomBlob(const std::string &layername, int layer_input_id);
  int caffe_topBlob_neuron_num(const std::string &layername, int layer_output_id);
  int caffe_bottomBlob_neuron_num(const std::string &layername, int layer_input_id);
#endif

 protected:
  bmk_info_t bmk_info_;
  void *weight_;
  uint64_t weight_size_;
  void *emiter_;
  NetCalibrationParameter m_netCalibrationParameter;
  bool input_init_;
  std::string input_file_;
  std::vector<int> input_shape_;
  std::unique_ptr<int8_t[]> input_data_i8_;
  std::unique_ptr<float[]> input_data_;
  std::string ctableName_;
#ifdef ENABLE_CAFFE_GOLDEN
  bool caffe_golden_is_on = true;
  bool caffe_init_;
  bool input_from_caffe_;
  bool caffe_cmp_opt_;
  std::string caffe_proto_;
  std::string caffe_weight_;
  std::vector<std::vector<std::shared_ptr<int8_t>>> caffe_all_layer_tops;
  std::vector<std::vector<std::shared_ptr<int8_t>>> caffe_all_layer_bottoms;
  using deleter_t = std::function<void(void *)>;
  std::unique_ptr<void, deleter_t> caffe_net_;
#endif

  /*
   * Note:
   * BM188x uses CTRL_NEURON and CTRL_WEIGHT in bmk1880_gdma_load
   * and bmk1880_gdma_store, which is different from BM168x.
   * The params as follows are useless.
   */
  static const u64 global_neuron_base_ = 0x0;
  static const u64 global_weight_base_ = 0x0;
};

}  // namespace bmnet

#endif /* _BM188X_BACKEND_CONTEXT_H_ */
