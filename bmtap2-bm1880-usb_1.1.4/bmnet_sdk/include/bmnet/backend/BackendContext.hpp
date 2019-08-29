/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BACKEND_CONTEXT_H_
#define _BACKEND_CONTEXT_H_

#include <bmnet/bmnet.pb.h>
#include <cstring>
#include <vector>

#include <glog/logging.h>

typedef struct {
  int chip_version;
  int nodechip_shift;
  int npu_shift;
  int eu_shift;
  int local_mem_shift;
  int local_mem_banks;
  uint64_t global_mem_size;
  int nodechip_num;
  int npu_num;
  int eu_num;
  int local_mem_size;
  int unit_size; // such as sizeof(float) in bm1682, and sizeof(int8) in bm1880
} hw_info_t;

namespace bmnet {
class Instruction;
//class TensorFixedInst;

class BackendContext {

public:
  virtual ~BackendContext() {}
  // compile the graph to cmdbuf.
  virtual void build(NetParameter &net, const char* term_layer=nullptr) = 0;
  virtual void enter() = 0;
  virtual void exit() = 0;
  virtual void submit() = 0;
  virtual void registerInstruction(Instruction *inst) = 0;

  void write_cmdbuf(const void* cmdbuf, uint32_t size) {
    cmdbuf_.resize(size);
    memcpy(&cmdbuf_[0], cmdbuf, size);
  }

  void read_cmdbuf(std::vector<uint8_t>& out_cmdbuf) {
    out_cmdbuf.assign(cmdbuf_.begin(), cmdbuf_.end());
  }

  void enable_profile(bool enable) {
    profile_enabled_ = enable;
  }

  bool profile_enabled() {
    return profile_enabled_;
  }

  virtual float GetBlobCalibrationThreshold(const std::string &layerName, const std::string &blobName) {
    LOG(FATAL) << "This backend context has not implemented this function yet.";
    return -1.f;
  }
public:
  hw_info_t hw;

protected:
  BackendContext() : cmdbuf_(), profile_enabled_(false) {}

private:
  std::vector<uint8_t> cmdbuf_;
  bool profile_enabled_;
};

} // End bmnet namespace

#endif /* _BACKEND_CONTEXT_H_ */
