/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

#include <bmnet/frontend/Layer.hpp>
#include <bmkernel/bm168x/bmkernel_1682.h>
#include <bmnet/backend/BackendContext.hpp>
#define BM_CHIP_BM1680 0
#define BM_CHIP_BM1682 1

#define BM_OPT_NONE 0
#define BM_OPT_LAYER_GROUP 1
#define BM_OPT_LAYER_GROUP_WITH_GMEM_RECYCLE 2
#define BM_OPT_MERGE_BM_SCALE_ACTIV 3
#define BM_OPT_LAYER_GROUP_WITH_WEIGHT_OPT 4

namespace bmnet {

typedef int CHIP_VER;
class TensorInst;
class TensorFixedInst;
class FrontendContext;
class BackendContext;
class NetParameter;

template <typename Dtype>
class Builder {
public:
  Builder(CHIP_VER ver);
  Builder(CHIP_VER ver,
          const char* in_ctable,
          const char* out_ctable);

  virtual ~Builder();

  void addCustomizedTensorInst(TensorInst *inst);
  void addCustomizedTensorInst(TensorFixedInst *inst);

  void build(int n, int c, int h, int w,
             int opt = BM_OPT_LAYER_GROUP_WITH_GMEM_RECYCLE);

  size_t total_neuron_size() { return (size_t)total_neuron_size_; }

  size_t output_offset() { return (size_t)output_offset_; }

  size_t output_size() { return (size_t)output_size_; }

  void store_prototxt(const char *dst);

  void store_weight(const char *dst);

  void store_cmdbuf(const char *dst);

  void store_model(const char *net_name,
                   const char *dst,
                   const char *plugin_path=nullptr,
                   const char *input_tensor=nullptr,
                   bool debug=false);

  std::vector<Dtype> weight;
  std::vector<uint8_t> cmdbuf;
  std::vector<std::string> output_layers;
  std::vector<shape_t> output_shapes;
  std::vector<float> output_thresholds;
  std::vector<uint64_t> output_offsets;
  std::set<std::string> cpu_layers;
  FrontendContext *front_ctx_;
protected:
  void createBackend(std::vector<float> &weight);
  void createBackend(std::vector<int8_t> &weight);
  virtual void runFrontend(int n, int c, int h, int w) = 0;
  void runOptimizer(int opt);
  void runBackend();
  void findCpuLayers(std::set<std::string>& layers);
  void backendHelper(std::vector<float> &weight,
                     std::vector<uint8_t> &cmdbuf);
  void backendHelper(std::vector<int8_t> &weight,
                     std::vector<uint8_t> &cmdbuf);

  virtual std::string get_default_input_tensor() { return default_input_tensor_; }

 protected:
  CHIP_VER ver_;
  int node_num_;
  BackendContext *backend_ctx_;
  NetParameter* build_net_;
  std::vector<int> input_shape_;
  u64 total_neuron_size_;
  u64 output_offset_;
  u64 output_size_;
  bool weight_optimized_;
  std::string in_ctable_;
  std::string out_ctable_;

 private:
  std::string default_input_tensor_{"data"};
};

} // namespace bmnet

#endif /* _BUILDER_H_ */
