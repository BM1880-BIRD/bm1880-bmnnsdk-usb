/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM188X_TENSORINST_TG_LEAKYELU_H_
#define _BM188X_TENSORINST_TG_LEAKYELU_H_

#include <bmnet/targets/plat-bm188x/BM188xBackendContext.hpp>
#include <bmnet/targets/plat-bm188x/CustomizedTensorFixedInst.hpp>
#include <bmkernel/bm_kernel.h>
namespace bmnet {

class TGLeakyReluFixedInst : public CustomizedTensorFixedInst {
public:
  TGLeakyReluFixedInst() : CustomizedTensorFixedInst() {}
  ~TGLeakyReluFixedInst() {}

  std::string inst_name() {return std::string("tg_leakyrelu"); }

  void dump();
  void compute();

private:
    void forward(
        gaddr_t bottom_gaddr, gaddr_t top_gaddr,
        int input_n, int input_c,
        int input_h, int input_w);
};

}

#endif /* _BM188X_TENSORINST_TG_ELU_H_ */
