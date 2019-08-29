/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM_TENSORINST_TG_ELU_H_
#define _BM_TENSORINST_TG_ELU_H_

#include <bmnet/targets/plat-bm168x/BM168xBackendContext.hpp>
#include <bmnet/targets/plat-bm168x/CustomizedTensorInst.hpp>
#include <bmnet/targets/plat-bm188x/BM188xBackendContext.hpp>
#include <bmnet/targets/plat-bm188x/CustomizedTensorFixedInst.hpp>
#include <bmkernel/bm1880/bmkernel_1880.h>

namespace bmnet {

class TGEluPluginInst : public CustomizedTensorInst {
public:
  TGEluPluginInst() : CustomizedTensorInst() {}
  ~TGEluPluginInst() {}

  std::string inst_name() {return std::string("tg_elu"); }

  void dump();
  void compute();

private:
  void cpu_forward();
  void npu_forward();
};

class TGEluPluginFixedInst : public CustomizedTensorFixedInst {
public:
  TGEluPluginFixedInst() : CustomizedTensorFixedInst() {}
  ~TGEluPluginFixedInst() {}

  std::string inst_name() {return std::string("tg_elu"); }

  void dump();
  void compute();

};

}

#endif  /* _BM_TENSORINST_TG_ELU_H_ */
