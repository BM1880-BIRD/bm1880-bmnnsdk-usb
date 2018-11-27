/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM188X_TENSORINST_TG_CUSTOMIZED_H_
#define _BM188X_TENSORINST_TG_CUSTOMIZED_H_

#include <bmnet/targets/plat-bm188x/BM188xBackendContext.hpp>
#include <bmnet/backend/TensorFixedInst.hpp>
#include <bmkernel/bm1880/bmkernel_1880.h>

namespace bmnet {

class CustomizedTensorFixedInst : public TensorFixedInst {
public:
  CustomizedTensorFixedInst() : TensorFixedInst() {}
  ~CustomizedTensorFixedInst() {}

  void set_backend_context(BackendContext* ctx);

protected:
  BM188xBackendContext* _ctx;
  u64 get_global_neuron_base();
  u64 get_global_weight_base();
};

} // end namespace of bmnet.

#endif /* _BM168X_TENSORINST_TG_UPSAMPLE_H_ */
