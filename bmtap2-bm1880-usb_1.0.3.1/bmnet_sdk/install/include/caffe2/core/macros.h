// Automatically generated header file for caffe2 macros. These
// macros are used to build the Caffe2 binary, and if you are
// building a dependent library, they will need to be set as well
// for your program to link correctly.

#pragma once

// Caffe2 version. The plan is to increment the minor version every other week
// as a track point for bugs, until we find a proper versioning cycle.

#define CAFFE2_VERSION_MAJOR 0
#define CAFFE2_VERSION_MINOR 8
#define CAFFE2_VERSION_PATCH 2
#define CAFFE2_GIT_VERSION "v0.1.11-10038-g4a77dda"

static_assert(
    CAFFE2_VERSION_MINOR < 100,
    "Programming error: you set a minor version that is too big.");
static_assert(
    CAFFE2_VERSION_PATCH < 100,
    "Programming error: you set a patch version that is too big.");

#define CAFFE2_VERSION                                         \
  (CAFFE2_VERSION_MAJOR * 10000 + CAFFE2_VERSION_MINOR * 100 + \
   CAFFE2_VERSION_PATCH)

/* #undef CAFFE2_ANDROID */
#define CAFFE2_BUILD_SHARED_LIBS
#define CAFFE2_FORCE_FALLBACK_CUDA_MPI
/* #undef CAFFE2_HAS_MKL_DNN */
/* #undef CAFFE2_HAS_MKL_SGEMM_PACK */
#define CAFFE2_PERF_WITH_AVX
#define CAFFE2_PERF_WITH_AVX2
/* #undef CAFFE2_THREADPOOL_MAIN_IMBALANCE */
/* #undef CAFFE2_THREADPOOL_STATS */
/* #undef CAFFE2_UNIQUE_LONG_TYPEMETA */
#define CAFFE2_USE_EXCEPTION_PTR
/* #undef CAFFE2_USE_ACCELERATE */
/* #undef CAFFE2_USE_CUDNN */
#define CAFFE2_USE_EIGEN_FOR_BLAS
/* #undef CAFFE2_USE_FBCODE */
#define CAFFE2_USE_GFLAGS
#define CAFFE2_USE_GOOGLE_GLOG
/* #undef CAFFE2_USE_LITE_PROTO */
/* #undef CAFFE2_USE_MKL */
/* #undef CAFFE2_USE_IDEEP */
/* #undef CAFFE2_USE_NVTX */
/* #undef CAFFE2_USE_TRT */
/* #undef CAFFE2_DISABLE_NUMA */

#ifndef EIGEN_MPL2_ONLY
#define EIGEN_MPL2_ONLY
#endif

// Useful build settings that are recorded in the compiled binary
#define CAFFE2_BUILD_STRINGS { \
  {"GIT_VERSION", "v0.1.11-10038-g4a77dda"}, \
  {"CXX_FLAGS", "-msse3 -msse4.1 -msse4.2   --std=c++11  -fvisibility-inlines-hidden -rdynamic -DONNX_NAMESPACE=onnx_c2 -D_FORCE_INLINES -D_MWAITXINTRIN_H_INCLUDED -D__STRICT_ANSI__ -fopenmp -O2 -fPIC -Wno-narrowing -Wall -Wextra -Wno-missing-field-initializers -Wno-type-limits -Wno-array-bounds -Wno-unknown-pragmas -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-result -Wno-strict-overflow -Wno-strict-aliasing -Wno-error=deprecated-declarations -Wno-stringop-overflow"}, \
  {"BUILD_TYPE", "Release"}, \
  {"BLAS", "MKL"}, \
  {"USE_CUDA", "OFF"}, \
  {"USE_NCCL", "OFF"}, \
  {"USE_MPI", "ON"}, \
  {"USE_GFLAGS", "ON"}, \
  {"USE_GLOG", "ON"}, \
  {"USE_GLOO", ""}, \
  {"USE_NNPACK", "ON"}, \
  {"USE_OPENMP", "OFF"}, \
  {"FORCE_FALLBACK_CUDA_MPI", "1"}, \
  {"HAS_MKL_DNN", ""}, \
  {"HAS_MKL_SGEMM_PACK", ""}, \
  {"PERF_WITH_AVX", "1"}, \
  {"PERF_WITH_AVX2", "1"}, \
  {"UNIQUE_LONG_TYPEMETA", ""}, \
  {"USE_EXCEPTION_PTR", "1"}, \
  {"USE_ACCELERATE", ""}, \
  {"USE_EIGEN_FOR_BLAS", "ON"}, \
  {"USE_LITE_PROTO", ""}, \
  {"USE_MKL", ""}, \
  {"USE_NVTX", ""}, \
  {"USE_TRT", ""}, \
  {"DISABLE_NUMA", ""}, \
}
