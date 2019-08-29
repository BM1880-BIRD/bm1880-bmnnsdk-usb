/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM168X_TENSORINST_TG_CUSTOMIZED_H_
#define _BM168X_TENSORINST_TG_CUSTOMIZED_H_

#include <bmnet/backend/TensorInst.hpp>
#include <bmnet/targets/plat-bm168x/BM168xBackendContext.hpp>

namespace bmnet {

class CustomizedTensorInst : public TensorInst {
 public:
  CustomizedTensorInst() : TensorInst() {}
  ~CustomizedTensorInst() {}
};

}  // namespace bmnet

#endif /* _BM168X_TENSORINST_TG_UPSAMPLE_H_ */
