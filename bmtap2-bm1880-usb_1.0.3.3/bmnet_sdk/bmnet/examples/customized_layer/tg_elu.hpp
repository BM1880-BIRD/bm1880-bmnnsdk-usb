/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM188X_TENSORINST_TG_ELU_H_
#define _BM188X_TENSORINST_TG_ELU_H_

#include <bmnet/targets/plat-bm188x/BM188xBackendContext.hpp>
#include <bmnet/targets/plat-bm188x/CustomizedTensorFixedInst.hpp>
#include <bmkernel/bm1880/bmkernel_1880.h>
namespace bmnet {

class TGEluFixedInst : public CustomizedTensorFixedInst {
public:
  TGEluFixedInst() : CustomizedTensorFixedInst() {}
  ~TGEluFixedInst() {}

  std::string inst_name() {return std::string("tg_elu"); }

  void dump();
  void compute();

};

}

#endif /* _BM188X_TENSORINST_TG_ELU_H_ */
