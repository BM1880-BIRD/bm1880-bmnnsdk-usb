#ifndef BM1882_SDMA_REG_H
#define BM1882_SDMA_REG_H

#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef unsigned long ulong;
typedef unsigned long long ullong;

#define SDMA_REG_BYTES 0x40

typedef struct {
  u32 valid;
  u32 enable_stride;
  u32 direction;
  u32 cmd_id;
  u32 special_function;
  u32 gmem_data_type;
  u32 copy_chw;
  u32 cmd_id_bd;
  u32 const_to_fill;
  u32 winograd_scale_factor;
  u32 lrn_shift_dirction;
  u32 add_result;

  u64 src_addr;
  u64 dst_addr;

  u32 src_n;
  u32 src_c;
  u32 src_h;
  u32 src_w;

  u32 dst_c;
  u32 dst_h;
  u32 dst_w;

  u32 src_n_stride;
  u32 src_c_stride;
  u32 src_h_stride;

  u32 dst_n_stride;
  u32 dst_c_stride;
  u32 dst_h_stride;
} sdma_reg_t;

static inline void parse_sdma_reg(sdma_reg_t *r, const u32 *buf) {
  r->valid = buf[0 / 4] & 1;
  r->enable_stride = (buf[0 / 4] >> 5) & 1;
  r->direction = (buf[0 / 4] >> 6) & 0b11;
  r->add_result = (buf[0 / 4] >> 9) & 1;
  r->cmd_id = (buf[0 / 4] >> 16) & 0xffff;
  r->special_function = buf[4 / 4] & 0b111;
  r->gmem_data_type = (buf[4 / 4] >> 8) & 1;
  r->winograd_scale_factor = (buf[4 / 4] >> 9) & 0xf;
  r->lrn_shift_dirction = (buf[4 / 4] >> 13) & 1;
  r->copy_chw = (buf[4 / 4] >> 14) & 1;
  r->cmd_id_bd = (buf[4 / 4] >> 16) & 0xffff;
  r->const_to_fill = buf[0x0c / 4] & 0xff;

  r->src_addr = ((u64)((buf[0x34 / 4] >> 24) & 0xff) << 32) | buf[0x30 / 4];
  r->dst_addr = ((u64)((buf[0x34 / 4] >> 16) & 0xff) << 32) | buf[0x2c / 4];

  r->src_n = buf[0x34 / 4] & 0xffff;
  r->src_c = (buf[0x20 / 4] >> 16) & 0xffff;
  r->src_h = (buf[0x28 / 4] >> 16) & 0xffff;
  r->src_w = buf[0x28 / 4] & 0xffff;

  r->dst_c = buf[0x20 / 4] & 0xffff;
  r->dst_h = (buf[0x24 / 4] >> 16) & 0xffff;
  r->dst_w = buf[0x24 / 4] & 0xffff;

  r->src_n_stride = buf[0x1c / 4];
  r->src_c_stride = ((buf[0x38 / 4] & 0xffff) << 16) | ((buf[0x18 / 4] >> 16) & 0xffff);
  r->src_h_stride = buf[0x18 / 4] & 0xffff;

  r->dst_n_stride = buf[0x14 / 4];
  r->dst_c_stride = (buf[0x38 / 4] & 0xffff0000) | ((buf[0x10 / 4] >> 16) & 0xffff);
  r->dst_h_stride = buf[0x10 / 4] & 0xffff;
}

static inline void print_sdma_reg(sdma_reg_t *r) {
  if (r == NULL) return;

  printf(
      "SDMA REG:\n"
      "r->valid = %d\n"
      "r->enable_stride = %d\n"
      "r->direction = %d\n"
      "r->add_result = %d\n"
      "r->cmd_id = %d\n"
      "r->special_function = %d\n"
      "r->gmem_data_type = %d\n"
      "r->winograd_scale_factor = %d\n"
      "r->lrn_shift_dirction = %d\n"
      "r->copy_chw = %d\n"
      "r->cmd_id_bd = %d\n"
      "r->const_to_fill = %d\n"
      "r->src_addr = 0x%lx\n"
      "r->dst_addr = 0x%lx\n"
      "r->src_n = %d\n"
      "r->src_c = %d\n"
      "r->src_h = %d\n"
      "r->src_w = %d\n"
      "r->dst_c = %d\n"
      "r->dst_h = %d\n"
      "r->dst_w = %d\n"
      "r->src_n_stride = %d\n"
      "r->src_c_stride = %d\n"
      "r->src_h_stride = %d\n"
      "r->dst_n_stride = %d\n"
      "r->dst_c_stride = %d\n"
      "r->dst_h_stride = %d\n",
      r->valid, r->enable_stride, r->direction, r->add_result, r->cmd_id, r->special_function,
      r->gmem_data_type, r->winograd_scale_factor, r->lrn_shift_dirction, r->copy_chw, r->cmd_id_bd,
      r->const_to_fill, (ulong)r->src_addr, (ulong)r->dst_addr, r->src_n, r->src_c, r->src_h,
      r->src_w, r->dst_c, r->dst_h, r->dst_w, r->src_n_stride, r->src_c_stride, r->src_h_stride,
      r->dst_n_stride, r->dst_c_stride, r->dst_h_stride);
}

static inline void emit_sdma_reg(const sdma_reg_t *r, u32 *buf) {
  buf[0x3c / 4] = 0;
  buf[0x38 / 4] = (((r->dst_c_stride >> 16) & 0xffff) << 16) | ((r->src_c_stride >> 16) & 0xffff);
  buf[0x34 / 4] = (((r->src_addr >> 32) & 0xff) << 24) | (((r->dst_addr >> 32) & 0xff) << 16) |
                  (r->src_n & 0xffff);
  buf[0x30 / 4] = r->src_addr & (u32)-1;
  buf[0x2c / 4] = r->dst_addr & (u32)-1;
  buf[0x28 / 4] = ((r->src_h & 0xffff) << 16) | (r->src_w & 0xffff);
  buf[0x24 / 4] = ((r->dst_h & 0xffff) << 16) | (r->dst_w & 0xffff);
  buf[0x20 / 4] = ((r->src_c & 0xffff) << 16) | (r->dst_c & 0xffff);
  buf[0x1c / 4] = r->src_n_stride;
  buf[0x18 / 4] = ((r->src_c_stride & 0xffff) << 16) | (r->src_h_stride & 0xffff);
  buf[0x14 / 4] = r->dst_n_stride;
  buf[0x10 / 4] = ((r->dst_c_stride & 0xffff) << 16) | (r->dst_h_stride & 0xffff);
  buf[0x0c / 4] = r->const_to_fill & 0xff;
  buf[0x08 / 4] = 0;
  buf[0x04 / 4] = ((r->cmd_id_bd & 0xffff) << 16) | ((r->copy_chw & 1) << 14) |
                  ((r->lrn_shift_dirction & 1) << 13) | ((r->winograd_scale_factor & 0xf) << 9) |
                  ((r->gmem_data_type & 1) << 8) | (0b100 << 5) | (0b01 << 3) |
                  (r->special_function & 0b111);
  buf[0x00 / 4] = ((r->cmd_id & 0xffff) << 16) | ((r->add_result & 1) << 9) |
                  ((r->direction & 0b11) << 6) | ((r->enable_stride & 1) << 5) | (r->valid & 1);
}

#endif /* BM1880_SDMA_REG_H */
