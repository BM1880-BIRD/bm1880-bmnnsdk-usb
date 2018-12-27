/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BACKEND_CONTEXT_H_
#define _BACKEND_CONTEXT_H_

#include <bmnet/bmnet.pb.h>
#include <cstring>

#include <bmnet/targets/optimizer/Lir/lir_builder.hpp>

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
class TensorInst;
class TensorFixedInst;

class BackendContext {
 private:
  LirBuilder * LirBuilder_;
  LirFunction * LirFunction_;
  std::vector<uint8_t> cmdbuf_;
  // for Lir debug
  void * curInst_;
  bool profile_enabled_;

 protected:
  BackendContext() :cmdbuf_(), profile_enabled_(false) {
    LirFunction_ = new LirFunction("Net", this);
    LirBuilder_ = new LirBuilder(LirFunction_);
  }

 public:
  virtual ~BackendContext(){}
  virtual NetParameter* getNetParameter(){return NULL;}
  virtual void setNetParameter(NetParameter* net) {}
  virtual NetParameter* getBaseNetParameter(){return NULL;}
  virtual void setBaseNetParameter(NetParameter* base_net){}
  virtual void setNetTensorShape(NetParameter* net){}
  virtual void setNetTensorShape(const TensorShape &ts){}
  virtual const TensorShape* getNetTensorShape(){return NULL;}
  LirBuilder * getLirBuilder() const {return LirBuilder_;}
  LirFunction * getLirFunction() { return LirFunction_;}
  void dumpLir(){
    LirFunction_->dumpLir();
  }

  void compileLir(BackendContext * ctx){
    LirFunction_->compileLir(ctx);
  }

  // for Lir debug
  void setCurrentInst(void * curInst) { curInst_ = curInst; };
  void * getCurrentInst() {
    if(curInst_)
      return curInst_;
    else
      return NULL;
  }

  // compile the graph to cmdbuf.
  virtual void build(NetParameter &net, const char* term_layer=NULL) = 0;
  virtual void enter() = 0;
  virtual void exit() = 0;
  virtual void submit() = 0;

  virtual void registerCustomizedTensorInst(TensorInst *inst) { assert(0); }
  virtual void registerCustomizedTensorInst(TensorFixedInst *inst) { assert(0); }

  //  TODO fractoring
  virtual void update_weight(std::vector<float> &weight) { assert(0); }
  virtual void update_weight(std::vector<int8_t> &weight) { assert(0); }

  virtual bool ImportCalibrationTable(const char *ctableName) {}

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

public:
  hw_info_t hw;
};

} // End bmnet namespace

#endif /* _BACKEND_CONTEXT_H_ */
