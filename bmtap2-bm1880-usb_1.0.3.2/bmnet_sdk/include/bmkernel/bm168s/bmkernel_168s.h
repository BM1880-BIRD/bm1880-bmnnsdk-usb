#ifndef __BMKERNEL_168S_H__
#define __BMKERNEL_168S_H__

#include <bmkernel/bm_kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bmk168s_context_t_ bmk168s_context_t;
typedef struct ec_desc bmk168s_op_t;

bmk168s_context_t * bmk168s_register(bmk_info_t *info);
void bmk168s_cleanup(bmk168s_context_t *ctx);
void bmk168s_reset(bmk168s_context_t *ctx);
u8 *bmk168s_acquire_cmdbuf(bmk168s_context_t *ctx, u32 *size);

void bmk168s_parallel_enable(bmk168s_context_t *ctx);
void bmk168s_parallel_disable(bmk168s_context_t *ctx);

void bmk168s_create_streams(bmk168s_context_t *ctx, int nr_streams);
void bmk168s_destroy_streams(bmk168s_context_t *ctx);
void bmk168s_set_stream(bmk168s_context_t *ctx, int i);

void bmk168s_add_dependency(
    bmk168s_context_t *ctx,
    bmk168s_op_t *before,
    bmk168s_op_t *after);

void bmk168s_cpu_op(
    bmk168s_context_t *ctx,
    const char* op_name, char *params, int size);

typedef struct {
  u32 n, c, w, col;
} bmk168s_matrix_lmem_shape_t;

typedef struct {
  u32 row, col;
} bmk168s_matrix_gmem_shape_t;

typedef struct {
  u32 n, c, h;
} bmk168s_matrix_lmem_stride_t;

typedef struct {
  u32 row;
} bmk168s_matrix_gmem_stride_t;

typedef struct {
  u32 n, c, h, w;
} bmk168s_tensor_lmem_shape_t, bmk168s_tensor_gmem_shape_t;

typedef struct {
  u32 n, c, h, w;
} bmk168s_tensor_lmem_stride_t, bmk168s_tensor_gmem_stride_t;

typedef struct {
  u32 start_address;
  fmt_t fmt;
  bmk168s_matrix_lmem_shape_t shape;
  bmk168s_matrix_lmem_stride_t stride;
} bmk168s_matrix_lmem_t;

typedef struct {
  u64 start_address;
  fmt_t fmt;
  bmk168s_matrix_gmem_shape_t shape;
  bmk168s_matrix_gmem_stride_t stride;
} bmk168s_matrix_gmem_t;

typedef struct {
  u32 start_address;
  fmt_t fmt;
  bmk168s_tensor_lmem_shape_t shape;
  bmk168s_tensor_lmem_stride_t stride;
} bmk168s_tensor_lmem_t;

typedef struct {
  u64 start_address;
  fmt_t fmt;
  bmk168s_tensor_gmem_shape_t shape;
  bmk168s_tensor_gmem_stride_t stride;
} bmk168s_tensor_gmem_t;

typedef struct {
  bmk168s_matrix_gmem_t *dst;
  bmk168s_matrix_gmem_t *src;
  int transpose_rc;
  int result_add;
} bmk168s_gdma_matrix_g2g_param_t;

typedef struct {
  bmk168s_matrix_lmem_t *dst;
  bmk168s_matrix_gmem_t *src;
  int transpose_rc;
  int result_add;
} bmk168s_gdma_matrix_g2l_param_t;

typedef struct {
  bmk168s_matrix_gmem_t *dst;
  bmk168s_matrix_lmem_t *src;
  int transpose_rc;
  int result_add;
} bmk168s_gdma_matrix_l2g_param_t;

typedef struct {
  bmk168s_tensor_gmem_t *dst;
  bmk168s_tensor_gmem_t *src;
  int transpose_nc;
  int result_add;
} bmk168s_gdma_tensor_g2g_param_t;

typedef struct {
  bmk168s_tensor_lmem_t *dst;
  bmk168s_tensor_gmem_t *src;
  int transpose_nc;
  int result_add;
} bmk168s_gdma_tensor_g2l_param_t;

typedef struct {
  bmk168s_tensor_gmem_t *dst;
  bmk168s_tensor_lmem_t *src;
  int transpose_nc;
  int result_add;
} bmk168s_gdma_tensor_l2g_param_t;

typedef struct {
  bmk168s_tensor_lmem_t *dst;
  bmk168s_tensor_lmem_t *src;
  int result_add;
} bmk168s_gdma_tensor_l2l_param_t;

typedef struct {
  bmk168s_tensor_lmem_t *dst;
  bmk168s_tensor_lmem_t *src;
  int right_shift;
  u32 lrn_step;
} bmk168s_gdma_tensor_lrn_shift_param_t;

bmk168s_op_t * bmk168s_gdma_matrix_g2g(
    bmk168s_context_t *ctx,
    const bmk168s_gdma_matrix_g2g_param_t *p);

bmk168s_op_t * bmk168s_gdma_matrix_g2l(
    bmk168s_context_t *ctx,
    const bmk168s_gdma_matrix_g2l_param_t *p);

bmk168s_op_t * bmk168s_gdma_matrix_l2g(
    bmk168s_context_t *ctx,
    const bmk168s_gdma_matrix_l2g_param_t *p);

bmk168s_op_t * bmk168s_gdma_tensor_g2g(
    bmk168s_context_t *ctx,
    const bmk168s_gdma_tensor_g2g_param_t *p);

bmk168s_op_t * bmk168s_gdma_tensor_g2l(
    bmk168s_context_t *ctx,
    const bmk168s_gdma_tensor_g2l_param_t *p);

bmk168s_op_t * bmk168s_gdma_tensor_l2g(
    bmk168s_context_t *ctx,
    const bmk168s_gdma_tensor_l2g_param_t *p);

bmk168s_op_t * bmk168s_gdma_tensor_l2l(
    bmk168s_context_t *ctx,
    const bmk168s_gdma_tensor_l2l_param_t *p);

bmk168s_op_t * bmk168s_gdma_tensor_lrn_shift(
    bmk168s_context_t *ctx,
    const bmk168s_gdma_tensor_lrn_shift_param_t *p);

bmk168s_tensor_lmem_t * bmk168s_lmem_alloc_tensor(
    bmk168s_context_t *ctx,
    bmk168s_tensor_lmem_shape_t s,
    fmt_t fmt,
    int eu_align,
    int la_align);

void bmk168s_lmem_free_tensor(
    bmk168s_context_t *ctx,
    bmk168s_tensor_lmem_t *t);

bmk168s_matrix_lmem_t * bmk168s_lmem_alloc_matrix(
    bmk168s_context_t *ctx,
    bmk168s_matrix_lmem_shape_t s,
    fmt_t fmt,
    int eu_align,
    int la_align,
    int col_align);

void bmk168s_lmem_free_matrix(
    bmk168s_context_t *ctx,
    bmk168s_matrix_lmem_t *t);

void bmk168s_lmem_reuse_matrix(
    bmk168s_context_t *ctx,
    bmk168s_matrix_lmem_t *from,
    bmk168s_matrix_lmem_t *to,
    fmt_t fmt,
    int eu_align,
    int col_align);

/*
 * TODO: Tensor arithmetic APIs:
 */

typedef struct {
  bmk168s_tensor_lmem_t *ofmap;
  bmk168s_tensor_lmem_t *ifmap;
  bmk168s_tensor_lmem_t *weight;
  bmk168s_tensor_lmem_t *bias;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  u8 dilation_h, dilation_w;
  bool relu_enable;
  bool result_add;
  bool kernel_flip;
  int rshift_width;
} bmk168s_conv_param_t;

bmk168s_op_t * bmk168s_tpu_conv(
    bmk168s_context_t *ctx,
    const bmk168s_conv_param_t *p);

bmk168s_op_t * bmk168s_tpu_conv_fixed(
    bmk168s_context_t *ctx,
    const bmk168s_conv_param_t *p);

typedef struct {
  bmk168s_matrix_lmem_t *res;
  bmk168s_matrix_lmem_t *left;
  bmk168s_matrix_lmem_t *right;
  bmk168s_matrix_lmem_t *bias;
  bool   is_L_const;
  float  L_const_value;
  ctrl_t ctrls;
} bmk168s_fc_param_t;

bmk168s_op_t * bmk168s_tpu_fc(
    bmk168s_context_t *ctx,
    const bmk168s_fc_param_t *p);

typedef struct {
  bmk168s_tensor_lmem_t *ofmap;
  bmk168s_tensor_lmem_t *ifmap;
  u8 kh, kw;
  u8 ins_h, ins_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
} bmk168s_max_pooling_param_t;

bmk168s_op_t * bmk168s_tpu_max_pooling(
    bmk168s_context_t *ctx,
    const bmk168s_max_pooling_param_t *p);

typedef struct {
  bmk168s_tensor_lmem_t *ofmap;
  bmk168s_tensor_lmem_t *ifmap;
  u8 kh, kw;
  u8 ins_h, ins_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  float avg_pooling_const;
} bmk168s_avg_pooling_param_t;

bmk168s_op_t * bmk168s_tpu_avg_pooling(
    bmk168s_context_t *ctx,
    const bmk168s_avg_pooling_param_t *p);

typedef struct {
  bmk168s_tensor_lmem_t *ofmap;
  bmk168s_tensor_lmem_t *ifmap;
  bmk168s_tensor_lmem_t *weight;
  bmk168s_tensor_lmem_t *bias;
  u8 ins_h, ins_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  u8 dilation_h, dilation_w;
} bmk168s_depthwise_param_t;

bmk168s_op_t * bmk168s_tpu_depthwise(
    bmk168s_context_t *ctx,
    const bmk168s_depthwise_param_t *p);

typedef struct {
  bmk168s_matrix_lmem_t *res;
  bmk168s_matrix_lmem_t *left;
  bmk168s_matrix_lmem_t *right;
  bmk168s_matrix_lmem_t *bias;
  int    lshift_width;
  int    rshift_width;
  int    L_const_value;
  bool   is_res_int8;
  bool   is_L_const;
  bool   res_add_sign;
  ctrl_t ctrls;
} bmk168s_fc_int8_param_t;

bmk168s_op_t * bmk168s_tpu_fc_int8(
    bmk168s_context_t *ctx,
    const bmk168s_fc_int8_param_t *p);

typedef struct {
  u32 version;
  u32 npu_num;
  u32 eu_num;
  u32 lmem_size;
  u32 lmem_banks;
  u32 lmem_bank_size;
  u32 l2_sram_size;
  u32 l2_sram_banks;
  u32 l2_sram_bank_size;
} bmk168s_chip_info_t;

bmk168s_chip_info_t bmk168s_chip_info(void);

#ifdef __cplusplus
}
#endif

#endif /* __BMKERNEL_168S_H__ */
