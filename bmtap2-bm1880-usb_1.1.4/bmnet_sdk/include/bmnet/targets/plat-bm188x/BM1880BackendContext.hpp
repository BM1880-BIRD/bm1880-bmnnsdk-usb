/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _BM1880_BACKEND_CONTEXT_H_
#define _BM1880_BACKEND_CONTEXT_H_

#include <bmnet/targets/plat-bm188x/BM188xBackendContext.hpp>

namespace bmnet {

class BM1880BackendContext : public BM188xBackendContext {
 public:
  BM1880BackendContext(int chip_ver, int nodechip_num, std::vector<int8_t> &weight);
  ~BM1880BackendContext() override;

  void submit() override;

  laddr_t get_high_8bit_addr(tensor_lmem *low_addr, shape_t low_shape, u32 eu_num) const {
    laddr_t laddr = tl_address(low_addr);
    int size = bmk1880_tl_shape_to_size(bmk_, low_shape, true, FMT_I8);
    return ((laddr + size + eu_num - 1) / eu_num) * eu_num + laddr % eu_num;
  }

  int tl_shape_to_size(shape_t s, bool aligned, fmt_t fmt) const {
    return bmk1880_tl_shape_to_size(bmk_, s, aligned, fmt);
  }

  int tl_size(tensor_lmem *tlp) const { return bmk1880_tl_size(bmk_, tlp); }

  tensor_lmem *tl_alloc(shape_t s, fmt_t fmt, u32 ctrls) const {
    return bmk1880_tl_alloc(bmk_, s, fmt, ctrls);
  }

  tensor_lmem *tl_alloc_bank(u32 bank_id, shape_t s, fmt_t fmt, u32 ctrls) const {
    return bmk1880_tl_alloc_bank(bmk_, bank_id, s, fmt, ctrls);
  }

  tensor_lmem *tl_prealloc(laddr_t la, shape_t s, fmt_t fmt) const {
    return bmk1880_tl_prealloc(bmk_, la, s, fmt);
  }

  tensor_lmem *tl_prealloc_align(laddr_t la, shape_t s, fmt_t fmt) const {
    return bmk1880_tl_prealloc_align(bmk_, la, s, fmt);
  }

  void tl_free(tensor_lmem *tlp) const { return bmk1880_tl_free(bmk_, tlp); }

  void create_streams(int streams) const { bmk1880_create_streams(bmk_, streams); }

  void set_stream(int stream) const { bmk1880_set_stream(bmk_, stream); }

  void destroy_streams() const { bmk1880_destroy_streams(bmk_); }

  void parallel_enable() const override { return bmk1880_parallel_enable(bmk_); }

  void parallel_disable() const override { return bmk1880_parallel_disable(bmk_); }

  void set_layer_id(u16 layer_id) const override {}
  int layer_id() const override { return -1; }

  bmk1880_op_t *tpu_zero(tensor_lmem *addr) const {
    assert(addr->fmt == FMT_I8 || addr->fmt == FMT_U8);
    bmk1880_xor_int8_param_t p;
    p.res = p.a = p.b = addr;
    return bmk1880_tpu_xor_int8(bmk_, &p);
  }

  bmk1880_op_t *tpu_copy(bmk1880_copy_param_t *param) const {
    return bmk1880_tpu_copy(bmk_, param);
  }

  bmk1880_op_t *tpu_copy_with_stride(bmk1880_copy_with_stride_param_t *param) const {
    return bmk1880_tpu_copy_with_stride(bmk_, param);
  }

  bmk1880_op_t *tpu_lut(bmk1880_lut_param_t *param) const { return bmk1880_tpu_lut(bmk_, param); }

  bmk1880_op_t *tpu_relu(bmk1880_relu_param_t *param) const {
    return bmk1880_tpu_relu(bmk_, param);
  }

  bmk1880_op_t *tpu_or_int8(bmk1880_or_int8_param_t *param) const {
    return bmk1880_tpu_or_int8(bmk_, param);
  }

  bmk1880_op_t *tpu_and_int8(bmk1880_and_int8_param_t *param) const {
    return bmk1880_tpu_and_int8(bmk_, param);
  }

  bmk1880_op_t *tpu_max(bmk1880_max_param_t *param) const { return bmk1880_tpu_max(bmk_, param); }

  bmk1880_op_t *tpu_max_const(bmk1880_max_const_param_t *param) const {
    return bmk1880_tpu_max_const(bmk_, param);
  }

  bmk1880_op_t *tpu_min(bmk1880_min_param_t *param) const { return bmk1880_tpu_min(bmk_, param); }

  bmk1880_op_t *tpu_min_const(bmk1880_min_const_param_t *param) const {
    return bmk1880_tpu_min_const(bmk_, param);
  }

  bmk1880_op_t *tpu_mul(bmk1880_mul_param_t *param) const { return bmk1880_tpu_mul(bmk_, param); }

  bmk1880_op_t *tpu_mul_const(bmk1880_mul_const_param_t *param) const {
    return bmk1880_tpu_mul_const(bmk_, param);
  }

  bmk1880_op_t *tpu_add(bmk1880_add_param_t *param) const { return bmk1880_tpu_add(bmk_, param); }

  bmk1880_op_t *tpu_add_const(bmk1880_add_const_param_t *param) const {
    return bmk1880_tpu_add_const(bmk_, param);
  }

  bmk1880_op_t *tpu_mac(bmk1880_mac_param_t *param) const { return bmk1880_tpu_mac(bmk_, param); }

  bmk1880_op_t *tpu_mac_const(bmk1880_mac_const_param_t *param) const {
    return bmk1880_tpu_mac_const(bmk_, param);
  }

  bmk1880_op_t *tpu_conv(bmk1880_conv_param_t *param) const {
    return bmk1880_tpu_conv(bmk_, param);
  }

  bmk1880_op_t *tpu_winograd(bmk1880_winograd_param_t *param) const {
    return bmk1880_tpu_winograd(bmk_, param);
  }

  bmk1880_op_t *tpu_max_pooling(bmk1880_max_pooling_param_t *param) const {
    return bmk1880_tpu_max_pooling(bmk_, param);
  }

  bmk1880_op_t *tpu_avg_pooling(bmk1880_avg_pooling_param_t *param) const {
    return bmk1880_tpu_avg_pooling(bmk_, param);
  }

  bmk1880_op_t *tpu_depthwise(bmk1880_depthwise_param_t *param) const {
    return bmk1880_tpu_depthwise(bmk_, param);
  }

  bmk1880_op_t *tpu_matrix_mac(bmk1880_matrix_mac_param_t *param) const {
    return bmk1880_tpu_matrix_mac(bmk_, param);
  }

  bmk1880_op_t *gdma_tg_copy(tensor_gmem *dst, tensor_gmem *src, ctrl_t ctrls) const {
    return bmk1880_gdma_copy_gmem(bmk_, dst, src, ctrls);
  }

  bmk1880_op_t *gdma_load(tensor_lmem *t, u64 gaddr, ctrl_t ctrls) const {
    return bmk1880_gdma_load(bmk_, t, gaddr, ctrls);
  }

  bmk1880_op_t *gdma_store(tensor_lmem *t, u64 gaddr, ctrl_t ctrls) const {
    return bmk1880_gdma_store(bmk_, t, gaddr, ctrls);
  }

  bmk1880_op_t *gdma_load_stride(tensor_lmem *t, u64 gaddr, stride_t stride, ctrl_t ctrls) const {
    return bmk1880_gdma_load_stride(bmk_, t, gaddr, stride, ctrls);
  }

  bmk1880_op_t *gdma_store_stride(tensor_lmem *t, u64 gaddr, stride_t stride, ctrl_t ctrls) const {
    return bmk1880_gdma_store_stride(bmk_, t, gaddr, stride, ctrls);
  }

  bmk1880_op_t *gdma_lmem_copy(tensor_lmem *dst, tensor_lmem *src) const {
    return bmk1880_gdma_copy_lmem(bmk_, dst, src);
  }

  bmk1880_op_t *gdma_lrn_shift(tensor_lmem *dst, tensor_lmem *src, bool right_shift,
                               int lrn_step) const {
    return bmk1880_gdma_lrn_shift(bmk_, dst, src, right_shift, lrn_step);
  }

  bmk1880_context_t *bm_get_bmk() const { return bmk_; }

 private:
  bmk1880_context_t *bmk_;
};

}  // namespace bmnet

#endif /* _BM1880_BACKEND_CONTEXT_H_ */
