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

class DumpShape {
public:
  DumpShape(const bmnet::BlobShape& shape) : shape_(shape) {}
  friend std::ostream& operator<<(std::ostream& os, const DumpShape& d) {
    os << "[ ";
    for (auto dim : d.shape_.dim())
      os << dim << " ";
    os << "]";
    return os;
  }
private:
  const bmnet::BlobShape& shape_;
};

__attribute__((unused))
static uint64_t GetTensorCount(const TensorShape &shape, int start_axis, int end_axis) {
  int count = 1;
  for (int i = start_axis; i < end_axis; ++i) {
    count *= shape.dim(i);
  }
  return count;
}

__attribute__((unused))
static uint64_t GetTensorCount(const TensorShape &shape, int start_axis) {
  return GetTensorCount(shape, start_axis, shape.dim_size());
}

__attribute__((unused))
static uint64_t GetTensorCount(const TensorShape &shape) {
  uint64_t count = 1;
  for (int i = 0; i < shape.dim_size(); i++) {
    count *= shape.dim(i);
  }
  return count;
}

__attribute__((unused))
static uint64_t GetTensorSize(const TensorShape &shape) {
  return GetTensorCount(shape) * shape.data_type_size();
}

__attribute__((unused))
static int GetTensorOffset(const TensorShape &shape,
  const std::vector<int>& indices) {
  int offset = 0;
  for (int i = 0; i < shape.dim_size(); ++i) {
    offset *= shape.dim(i);
    if ((int)indices.size() > i) {
      offset += indices[i];
    }
  }
  return offset;
}

__attribute__((unused))
static bool TensorShapeEqual(const TensorShape &a, const TensorShape &b) {
  if (a.dim_size() != b.dim_size()) {
    return false;
  }

  for (int i = 0; i < a.dim_size(); i++) {
    if (a.dim(i) != b.dim(i)) {
      return false;
    }
  }
  return true;
}

} // end namespace bmnet

#endif /* _TENSOROPS_H_ */
