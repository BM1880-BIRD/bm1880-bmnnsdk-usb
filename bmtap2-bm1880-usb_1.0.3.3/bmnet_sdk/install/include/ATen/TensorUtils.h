#pragma once

#include "ATen/Tensor.h"
#include "ATen/TensorGeometry.h"
#include "ATen/Utils.h"

// These functions are NOT in Utils.h, because this file has a dep on Tensor.h

namespace at {

// The following are utility functions for checking that arguments
// make sense.  These are particularly useful for native functions,
// which do NO argument checking by default.

struct AT_API TensorArg {
  Tensor tensor;
  const char* name;
  int pos; // 1-indexed
  TensorArg(Tensor tensor, const char* name, int pos)
    : tensor(std::move(tensor)), name(name), pos(pos) {}
  const Tensor* operator->() const { return &tensor; }
  const Tensor& operator*() const { return tensor; }
};

struct AT_API TensorGeometryArg {
  TensorGeometry tensor;
  const char* name;
  int pos; // 1-indexed
  /* implicit */ TensorGeometryArg(TensorArg arg)
    : tensor(TensorGeometry{arg.tensor}), name(arg.name), pos(arg.pos) {}
  TensorGeometryArg(TensorGeometry tensor, const char* name, int pos)
    : tensor(tensor), name(name), pos(pos) {}
  const TensorGeometry* operator->() const { return &tensor; }
  const TensorGeometry& operator*() const { return tensor; }
};

// A string describing which function did checks on its input
// arguments.
// TODO: Consider generalizing this into a call stack.
using CheckedFrom = const char*;

// The undefined convention: singular operators assume their arguments
// are defined, but functions which take multiple tensors will
// implicitly filter out undefined tensors (to make it easier to perform
// tests which should apply if the tensor is defined, and should not
// otherwise.)
//
// NB: This means that the n-ary operators take lists of TensorArg,
// not TensorGeometryArg, because the Tensor to TensorGeometry
// conversion will blow up if you have undefined tensors.

AT_API std::ostream& operator<<(std::ostream & out, TensorGeometryArg t);
AT_API void checkDim(CheckedFrom c, const TensorGeometryArg& t, int64_t dim);
// NB: this is an inclusive-exclusive range
AT_API void checkDimRange(CheckedFrom c, const TensorGeometryArg& t, int64_t dim_start, int64_t dim_end);
AT_API void checkSameDim(CheckedFrom c, const TensorGeometryArg& t1, const TensorGeometryArg& t2);
AT_API void checkContiguous(CheckedFrom c, const TensorGeometryArg& t);
AT_API void checkAllContiguous(CheckedFrom c, at::ArrayRef<TensorArg> ts);
AT_API void checkSize(CheckedFrom c, const TensorGeometryArg& t, IntList sizes);
AT_API void checkSize(CheckedFrom c, const TensorGeometryArg& t, int64_t dim, int64_t size);
AT_API void checkNumel(CheckedFrom c, const TensorGeometryArg& t, int64_t numel);
AT_API void checkSameNumel(CheckedFrom c, const TensorGeometryArg& t1, const TensorGeometryArg& t2);
AT_API void checkAllSameNumel(CheckedFrom c, ArrayRef<TensorArg> tensors);
AT_API void checkScalarType(CheckedFrom c, const TensorArg& t, ScalarType s);
AT_API void checkScalarTypes(CheckedFrom c, const TensorArg& t, at::ArrayRef<ScalarType> l);
AT_API void checkSameGPU(CheckedFrom c, const TensorArg& t1, const TensorArg& t2);
AT_API void checkAllSameGPU(CheckedFrom c, ArrayRef<TensorArg> tensors);
AT_API void checkSameType(CheckedFrom c, const TensorArg& t1, const TensorArg& t2);
AT_API void checkAllSameType(CheckedFrom c, ArrayRef<TensorArg> tensors);
AT_API void checkSameSize(CheckedFrom c, const TensorArg& t1, const TensorArg& t2);
AT_API void checkDefined(CheckedFrom c, const TensorArg& t);
AT_API void checkAllDefined(CheckedFrom c, at::ArrayRef<TensorArg> t);

// FixMe: does TensorArg slow things down?
AT_API void checkBackend(CheckedFrom c, at::ArrayRef<Tensor> t, at::Backend backend);

// Methods for getting data_ptr if tensor is defined
AT_API void * maybe_data_ptr(const Tensor& tensor);
AT_API void * maybe_data_ptr(const TensorArg& tensor);

}
