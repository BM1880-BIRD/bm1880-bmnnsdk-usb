/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _TENSOROPS_H_
#define _TENSOROPS_H_

#include <iostream>
#include <bmnet/bmnet.pb.h>
#include <bmkernel/bm168x/bmkernel_1682.h>
#include <bmnet/utils/common.hpp>

#define MAX_W (1 << 11)

namespace bmnet {

using TensorOp = LayerParameter;
using TensorShape = BlobShape;

static uint64_t GetTensorCount(const TensorShape &shape, int start_axis, int end_axis) {
  assert(start_axis <= end_axis);
  assert(start_axis >= 0);
  assert(end_axis >= 0);
  assert(start_axis <= shape.dim_size());
  assert(end_axis <= shape.dim_size());
  int count = 1;
  for (int i = start_axis; i < end_axis; ++i) {
    count *= shape.dim(i);
  }
  return count;
}

static uint64_t GetTensorCount(const TensorShape &shape, int start_axis) {
  return GetTensorCount(shape, start_axis, shape.dim_size());
}

static uint64_t GetTensorCount(const TensorShape &shape) {
  uint64_t count = 1;
  for (int i = 0; i < shape.dim_size(); i++) {
    count *= shape.dim(i);
  }
  return count;
}

static uint64_t GetTensorSize(const TensorShape &shape) {
  return GetTensorCount(shape) * shape.data_type_size();
}

static int GetTensorOffset(const TensorShape &shape,
  const std::vector<int>& indices) {
  CHECK_LE(indices.size(), shape.dim_size());
  int offset = 0;
  for (int i = 0; i < shape.dim_size(); ++i) {
    offset *= shape.dim(i);
    if (indices.size() > i) {
      CHECK_GE(indices[i], 0);
      CHECK_LT(indices[i], shape.dim(i));
      offset += indices[i];
    }
  }
  return offset;
}

static void DumpShape(std::string desc, const TensorShape &shape) {
  std::cout << desc << " dim_size " << shape.dim_size() << std::endl;
  for (int i = 0; i < shape.dim_size(); i++) {
    std::cout << "  dim : " << shape.dim(i) << std::endl;
  }
}

} // end namespace bmnet

#endif /* _TENSOROPS_H_ */
