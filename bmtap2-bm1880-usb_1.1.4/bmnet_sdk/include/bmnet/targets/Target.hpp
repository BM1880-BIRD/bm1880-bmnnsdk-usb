/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef HOST_UTIL_H
#define HOST_UTIL_H

#include <bmnet/utils/debug.h>
#include <bmnet/utils/common.hpp>
#include <bmnet/backend/BackendContext.hpp>
#include <bmkernel/bm_kernel_legacy.h>

namespace bmnet {

#define MAX_HW (1 << 16)
#define RESIZE_W 2048

typedef struct nh_secs{
    unsigned int nsecs;
    unsigned int hsecs;
} NH_SECS;

int align_addr_to_eu_num(const BackendContext &ctx, int addr);

// for 32-bit fmt data, align to EU_NUM point, return in unit of byte
int get_csize_local(const BackendContext &ctx, int h, int w);

// for any fmt data, align to EU_NUM point, return in unit of byte
int get_csize_local_bitwidth(const BackendContext &ctx, int h, int w, int bitwidth);

// for any fmt data, align to EU_NUM point, return in unit of point
int get_cstride_local(const BackendContext &ctx, int h, int w);

int get_cstride_local(const BackendContext *ctx, int h, int w);

int get_slice_num_element_wise(const BackendContext &ctx, int blob_num, int count);

// fixed the width to 2048.
int get_height_with_fixed_width(const BackendContext &ctx, int w);

// for non-32-bit fmt data, align to 32 bit, return in unit of byte
int get_csize_global_bitwidth(const BackendContext &ctx, int h, int w, int bitwidth);

// for non-32-bit fmt data, align to 32 bit, return in unit of point
int get_cstride_global_bitwidth(const BackendContext &ctx, int h, int w, int bitwidth);

u64 shape_to_lmem_size(const BackendContext &ctx, shape_t& shape, bool aligned, int bitwidth = 32);

} // end namespace of bmnet.

#endif /* HOST_UTIL_H */
