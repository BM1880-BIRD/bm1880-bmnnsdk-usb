/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM168X_TENSORINST_TG_CUSTOMIZED_H_
#define _BM168X_TENSORINST_TG_CUSTOMIZED_H_

#include <bmnet/targets/plat-bm168x/BM168xBackendContext.hpp>
#include <bmnet/backend/TensorInst.hpp>
#include <bmkernel/bm168x/bmkernel_1682.h>

namespace bmnet {

class CustomizedTensorInst : public TensorInst {
public:
  CustomizedTensorInst() : TensorInst() {}
  ~CustomizedTensorInst() {}

  void set_backend_context(BackendContext* ctx);

protected:
  BM168xBackendContext* _ctx;
  u64 get_global_neuron_base();
  u64 get_global_weight_base();
};

} // end namespace of bmnet.

#endif /* _BM168X_TENSORINST_TG_UPSAMPLE_H_ */
