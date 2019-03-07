/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BMNET_COMMON_H_
#define _BMNET_COMMON_H_

#include <gflags/gflags.h>
#include <glog/logging.h>

#ifndef GFLAGS_GFLAGS_H_
namespace gflags = google;
#endif  // GFLAGS_GFLAGS_H_

//using gflags::FATAL;

#if 1 // TODO(wwcai): can this build successfully on any platform?
#include <typeinfo>
#include <cxxabi.h>
#define TYPE_NAME(a) (abi::__cxa_demangle(typeid(a).name(), nullptr, nullptr, nullptr))
#else
#define TYPE_NAME(a) "unknown"
#endif

using bm_chip_version_t = int;
#define BM_CHIP_BM1680 0
#define BM_CHIP_BM1682 1
#define BM_CHIP_BM1684 2
#define BM_CHIP_BM1880 3
#define BM_CHIP_INVALID 4
#define INVALID_GLOBAL_ADDR 0xFFFFFFFFFFFFFFFF

#endif // _BMNET_COMMON_H_
