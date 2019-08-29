/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM188X_TENSORINST_TG_CUSTOMIZED_H_
#define _BM188X_TENSORINST_TG_CUSTOMIZED_H_

#include <bmkernel/bm1880/bmkernel_1880.h>
#include <bmnet/backend/TensorFixedInst.hpp>
#include <bmnet/targets/plat-bm188x/BM188xBackendContext.hpp>

namespace bmnet {

class CustomizedTensorFixedInst : public TensorFixedInst {
 public:
  CustomizedTensorFixedInst() : TensorFixedInst() {}
  ~CustomizedTensorFixedInst() override = default;
};

}  // namespace bmnet

#endif /* _BM168X_TENSORINST_TG_UPSAMPLE_H_ */
