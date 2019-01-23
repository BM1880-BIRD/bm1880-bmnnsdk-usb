#ifndef __BMKERNEL_1882_H__
#define __BMKERNEL_1882_H__

#include <bmkernel/bm_kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ENGINE_TIU_0  0  // TPU Instruction Unit 0
#define ENGINE_TDMA_0 1  // TPU DMA 0
#define ENGINE_SDMA_0 2  // Shared DMA 0
#define ENGINE_TIU_1  3  // TPU Instruction Unit 1
#define ENGINE_TDMA_1 4  // TPU DMA 1
#define ENGINE_SDMA_1 5  // Shared DMA 1
#define ENGINE_CPU_0  6  // CPU, Reserved
#define ENGINE_ID_END 7  // Invalid

typedef struct bmk1882_context_t_ bmk1882_context_t;
typedef struct ec_desc bmk1882_op_t;

bmk1882_context_t * bmk1882_register(bmk_info_t *info);
void bmk1882_cleanup(bmk1882_context_t *ctx);
void bmk1882_reset(bmk1882_context_t *ctx);
u8 *bmk1882_acquire_cmdbuf(bmk1882_context_t *ctx, u32 *size);

void bmk1882_parallel_enable(bmk1882_context_t *ctx);
void bmk1882_parallel_disable(bmk1882_context_t *ctx);

void bmk1882_create_streams(bmk1882_context_t *ctx, int nr_streams);
void bmk1882_destroy_streams(bmk1882_context_t *ctx);
void bmk1882_set_stream(bmk1882_context_t *ctx, int i);

void bmk1882_add_dependency(
    bmk1882_context_t *ctx,
    bmk1882_op_t *before,
    bmk1882_op_t *after);

void bmk1882_cpu_op(
    bmk1882_context_t *ctx,
    const char* op_name, char *params, int size);

typedef struct {
  u32 n, c, w, col;
} bmk1882_matrix_lmem_shape_t;

typedef struct {
  u32 row, col;
} bmk1882_matrix_gmem_shape_t;

typedef struct {
  u32 n, c, h;
} bmk1882_matrix_lmem_stride_t;

typedef struct {
  u32 row;
} bmk1882_matrix_gmem_stride_t;

typedef struct {
  u32 n, c, h, w;
} bmk1882_tensor_lmem_shape_t, bmk1882_tensor_gmem_shape_t;

typedef struct {
  u32 n, c, h;
} bmk1882_tensor_lmem_stride_t, bmk1882_tensor_gmem_stride_t;

typedef struct {
  u8 tpu_idx;
  u32 start_address;
  bmk1882_matrix_lmem_shape_t shape;
  bmk1882_matrix_lmem_stride_t stride;
} bmk1882_matrix_lmem_t;

typedef struct {
  u64 start_address;
  bmk1882_matrix_gmem_shape_t shape;
  bmk1882_matrix_gmem_stride_t stride;
} bmk1882_matrix_gmem_t;

typedef struct {
  u8 tpu_idx;
  u32 start_address;
  fmt_t fmt;
  bmk1882_tensor_lmem_shape_t shape;
  bmk1882_tensor_lmem_stride_t stride;
} bmk1882_tensor_lmem_t;

typedef struct {
  u64 start_address;
  bmk1882_tensor_gmem_shape_t shape;
  bmk1882_tensor_gmem_stride_t stride;
} bmk1882_tensor_gmem_t;

typedef struct {
  u8 tpu_idx;
  bmk1882_matrix_gmem_t *dst;
  bmk1882_matrix_gmem_t *src;
  int transpose_rc;
} bmk1882_tdma_matrix_g2g_param_t;

typedef struct {
  u8 tpu_idx;
  bmk1882_matrix_lmem_t *dst;
  bmk1882_matrix_gmem_t *src;
  int transpose_rc;
} bmk1882_tdma_matrix_g2l_param_t;

typedef struct {
  u8 tpu_idx;
  bmk1882_matrix_gmem_t *dst;
  bmk1882_matrix_lmem_t *src;
  int transpose_rc;
} bmk1882_tdma_matrix_l2g_param_t;

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_gmem_t *dst;
  bmk1882_tensor_gmem_t *src;
  int transpose_nc;
} bmk1882_tdma_tensor_g2g_param_t;

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *dst;
  bmk1882_tensor_gmem_t *src;
  int transpose_nc;
} bmk1882_tdma_tensor_g2l_param_t;

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_gmem_t *dst;
  bmk1882_tensor_lmem_t *src;
  int transpose_nc;
} bmk1882_tdma_tensor_l2g_param_t;

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *dst;
  bmk1882_tensor_lmem_t *src;
} bmk1882_tdma_tensor_l2l_param_t;

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *dst;
  bmk1882_tensor_lmem_t *src;
  int right_shift;
  u32 lrn_step;
} bmk1882_tdma_tensor_lrn_shift_param_t;

bmk1882_op_t * bmk1882_tdma_matrix_g2g(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_matrix_g2g_param_t *p);

bmk1882_op_t * bmk1882_tdma_matrix_g2l(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_matrix_g2l_param_t *p);

bmk1882_op_t * bmk1882_tdma_matrix_l2g(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_matrix_l2g_param_t *p);

bmk1882_op_t * bmk1882_tdma_tensor_g2g(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tensor_g2g_param_t *p);

bmk1882_op_t * bmk1882_tdma_tensor_g2l(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tensor_g2l_param_t *p);

bmk1882_op_t * bmk1882_tdma_tensor_l2g(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tensor_l2g_param_t *p);

bmk1882_op_t * bmk1882_tdma_tensor_l2l(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tensor_l2l_param_t *p);

bmk1882_op_t * bmk1882_tdma_tensor_lrn_shift(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tensor_lrn_shift_param_t *p);

bmk1882_tensor_lmem_t * bmk1882_lmem_alloc_tensor(
    bmk1882_context_t *ctx,
    u8 tpu_idx,
    bmk1882_tensor_lmem_shape_t s,
    fmt_t fmt,
    int eu_align);

void bmk1882_lmem_free_tensor(
    bmk1882_context_t *ctx,
    bmk1882_tensor_lmem_t *t);

/*
 * General rules for tensor arithmetic APIs:
 *
 * 1, All tensors can be either signed or unsigned, if not mentioned otherwise.
 * 2, A tensor @x with both @x_high and @x_low as parameters can optionally be
 *    8-bit (when @x_high is NULL) or 16-bit (otherwise).
 */

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a;
  bmk1882_tensor_lmem_t *b;
  int rshift_width;
} bmk1882_mul_param_t;

bmk1882_op_t * bmk1882_tiu_mul(
    bmk1882_context_t *ctx,
    const bmk1882_mul_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a;
  s8 b;
  bool b_is_signed;
  int rshift_width;
} bmk1882_mul_const_param_t;

bmk1882_op_t * bmk1882_tiu_mul_const(
    bmk1882_context_t *ctx,
    const bmk1882_mul_const_param_t *p);

/*
 * @res = @a * @b + @res
 *
 * 1, @res_high must not be NULL since input @res must be 16-bit.
 * 2, If output @res is 8-bit (@res_is_int8 == 1), only @res_low is used
 *    as output tensor.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a;
  bmk1882_tensor_lmem_t *b;
  bool res_is_int8;
  int lshift_width;
  int rshift_width;
} bmk1882_mac_param_t;

bmk1882_op_t * bmk1882_tiu_mac(
    bmk1882_context_t *ctx,
    const bmk1882_mac_param_t *p);

/*
 * @res = @a * @b + @res
 *
 * 1, @res_high must not be NULL since input @res must be 16-bit.
 * 2, If output @res is 8-bit (@res_is_int8 == 1), only @res_low is used
 *    as output tensor.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a;
  s8 b;
  bool b_is_signed;
  bool res_is_int8;
  int lshift_width;
  int rshift_width;
} bmk1882_mac_const_param_t;

bmk1882_op_t * bmk1882_tiu_mac_const(
    bmk1882_context_t *ctx,
    const bmk1882_mac_const_param_t *p);

/*
 * @a and @b must all be 16-bit.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a_high;
  bmk1882_tensor_lmem_t *a_low;
  bmk1882_tensor_lmem_t *b_high;
  bmk1882_tensor_lmem_t *b_low;
} bmk1882_add_param_t;

bmk1882_op_t * bmk1882_tiu_add(
    bmk1882_context_t *ctx,
    const bmk1882_add_param_t *p);

/*
 * @a must be 16-bit.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a_high;
  bmk1882_tensor_lmem_t *a_low;
  s16 b;
  bool b_is_signed;
} bmk1882_add_const_param_t;

bmk1882_op_t * bmk1882_tiu_add_const(
    bmk1882_context_t *ctx,
    const bmk1882_add_const_param_t *p);

/*
 * 1, @a and @b must all be 16-bit.
 * 2, @res must be signed.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a_high;
  bmk1882_tensor_lmem_t *a_low;
  bmk1882_tensor_lmem_t *b_high;
  bmk1882_tensor_lmem_t *b_low;
} bmk1882_sub_param_t;

bmk1882_op_t * bmk1882_tiu_sub(
    bmk1882_context_t *ctx,
    const bmk1882_sub_param_t *p);

/*
 * @a and @b must both be signed or unsigned.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *max;
  bmk1882_tensor_lmem_t *a;
  bmk1882_tensor_lmem_t *b;
} bmk1882_max_param_t;

bmk1882_op_t * bmk1882_tiu_max(
    bmk1882_context_t *ctx,
    const bmk1882_max_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *max;
  bmk1882_tensor_lmem_t *a;
  s8 b;
  bool b_is_signed;
} bmk1882_max_const_param_t;

bmk1882_op_t * bmk1882_tiu_max_const(
    bmk1882_context_t *ctx,
    const bmk1882_max_const_param_t *p);

/*
 * @a and @b must both be signed or unsigned.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *min;
  bmk1882_tensor_lmem_t *a;
  bmk1882_tensor_lmem_t *b;
} bmk1882_min_param_t;

bmk1882_op_t * bmk1882_tiu_min(
    bmk1882_context_t *ctx,
    const bmk1882_min_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *min;
  bmk1882_tensor_lmem_t *a;
  s8 b;
  bool b_is_signed;
} bmk1882_min_const_param_t;

bmk1882_op_t * bmk1882_tiu_min_const(
    bmk1882_context_t *ctx,
    const bmk1882_min_const_param_t *p);

/*
 * 1, @a must be 16-bit and signed.
 * 2, @res must be 16-bit.
 * 3, @bits must be signed and ranges in [-16, 16].
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a_high;
  bmk1882_tensor_lmem_t *a_low;
  bmk1882_tensor_lmem_t *bits;
} bmk1882_arith_shift_param_t;

bmk1882_op_t * bmk1882_tiu_arith_shift(
    bmk1882_context_t *ctx,
    const bmk1882_arith_shift_param_t *p);

/*
 * TODO: bmk1882_tl_logic_shift()
 */

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res;
  bmk1882_tensor_lmem_t *a;
  bmk1882_tensor_lmem_t *b;
} bmk1882_and_int8_param_t;

bmk1882_op_t * bmk1882_tiu_and_int8(
    bmk1882_context_t *ctx,
    const bmk1882_and_int8_param_t *p);

/*
 * All parameters must be 16-bit.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a_high;
  bmk1882_tensor_lmem_t *a_low;
  bmk1882_tensor_lmem_t *b_high;
  bmk1882_tensor_lmem_t *b_low;
} bmk1882_and_int16_param_t;

bmk1882_op_t * bmk1882_tiu_and_int16(
    bmk1882_context_t *ctx,
    const bmk1882_and_int16_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res;
  bmk1882_tensor_lmem_t *a;
  bmk1882_tensor_lmem_t *b;
} bmk1882_or_int8_param_t;

bmk1882_op_t * bmk1882_tiu_or_int8(
    bmk1882_context_t *ctx,
    const bmk1882_or_int8_param_t *p);

/*
 * All parameters must be 16-bit.
 */

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a_high;
  bmk1882_tensor_lmem_t *a_low;
  bmk1882_tensor_lmem_t *b_high;
  bmk1882_tensor_lmem_t *b_low;
} bmk1882_or_int16_param_t;

bmk1882_op_t * bmk1882_tiu_or_int16(
    bmk1882_context_t *ctx,
    const bmk1882_or_int16_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res;
  bmk1882_tensor_lmem_t *a;
  bmk1882_tensor_lmem_t *b;
} bmk1882_xor_int8_param_t;

bmk1882_op_t * bmk1882_tiu_xor_int8(
    bmk1882_context_t *ctx,
    const bmk1882_xor_int8_param_t *p);

/*
 * All parameters must be 16-bit.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a_high;
  bmk1882_tensor_lmem_t *a_low;
  bmk1882_tensor_lmem_t *b_high;
  bmk1882_tensor_lmem_t *b_low;
} bmk1882_xor_int16_param_t;

bmk1882_op_t * bmk1882_tiu_xor_int16(
    bmk1882_context_t *ctx,
    const bmk1882_xor_int16_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *dst;
  bmk1882_tensor_lmem_t *src;
} bmk1882_copy_param_t;

bmk1882_op_t * bmk1882_tiu_copy(
    bmk1882_context_t *ctx,
    const bmk1882_copy_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *dst;
  bmk1882_tensor_lmem_stride_t dst_stride;
  bmk1882_tensor_lmem_t *src;
  bmk1882_tensor_lmem_stride_t src_stride;
} bmk1882_copy_with_stride_param_t;

bmk1882_op_t * bmk1882_tiu_copy_with_stride(
    bmk1882_context_t *ctx,
    const bmk1882_copy_with_stride_param_t *p);

/*
 * @res and @a must be both signed or unsigned.
 */
typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *res_high;
  bmk1882_tensor_lmem_t *res_low;
  bmk1882_tensor_lmem_t *a;
} bmk1882_mdsum_param_t;

bmk1882_op_t * bmk1882_tiu_mdsum(
    bmk1882_context_t *ctx,
    const bmk1882_mdsum_param_t *p);

/*
 * NOTE:
 *   @table is treated logically as a linear list of length @table_n, where
 *   @table_n is a multiple of 16 and is smaller than or equal to 256.
 *   When stored in local memory, @table is a tensor of shape (1, npu_num,
 *   1, @table_n), that is, the data of the linear list should be copied across
 *   each NPU's local memory by user. The behavior when these copies differ is
 *   not defined.
 */

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *ofmap;
  bmk1882_tensor_lmem_t *ifmap;
  bmk1882_tensor_lmem_t *table;
} bmk1882_lut_param_t;

bmk1882_op_t * bmk1882_tiu_lut(
    bmk1882_context_t *ctx,
    const bmk1882_lut_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *ofmap;
  bmk1882_tensor_lmem_t *ifmap;
} bmk1882_relu_param_t;

bmk1882_op_t * bmk1882_tiu_relu(
    bmk1882_context_t *ctx,
    const bmk1882_relu_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *ofmap;
  bmk1882_tensor_lmem_t *ifmap;
  bmk1882_tensor_lmem_t *weight;
  bmk1882_tensor_lmem_t *bias;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  u8 dilation_h, dilation_w;
  bool relu_enable;
  int rshift_width;
} bmk1882_conv_param_t;

bmk1882_op_t * bmk1882_tiu_conv(
    bmk1882_context_t *ctx,
    const bmk1882_conv_param_t *p);

typedef struct {
  bmk1882_tensor_lmem_t *ofmap;
  bmk1882_tensor_lmem_t *ifmap;
  bmk1882_tensor_lmem_t *weight;
  bmk1882_tensor_lmem_t *bias;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  bool relu_enable;
  int rshift_width;
} bmk1882_winograd_param_t;

bmk1882_op_t * bmk1882_tiu_winograd(
    bmk1882_context_t *ctx,
    const bmk1882_winograd_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *ofmap;
  bmk1882_tensor_lmem_t *ifmap;
  u8 kh, kw;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
} bmk1882_max_pooling_param_t;

bmk1882_op_t * bmk1882_tiu_max_pooling(
    bmk1882_context_t *ctx,
    const bmk1882_max_pooling_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *ofmap;
  bmk1882_tensor_lmem_t *ifmap;
  u8 kh, kw;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  u8 avg_pooling_const;
  int rshift_width;
} bmk1882_avg_pooling_param_t;

bmk1882_op_t * bmk1882_tiu_avg_pooling(
    bmk1882_context_t *ctx,
    const bmk1882_avg_pooling_param_t *p);

typedef struct {
  u8 tpu_idx;
  bmk1882_tensor_lmem_t *ofmap;
  bmk1882_tensor_lmem_t *ifmap;
  bmk1882_tensor_lmem_t *weight;
  bmk1882_tensor_lmem_t *bias;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  int rshift_width;
} bmk1882_depthwise_param_t;

bmk1882_op_t * bmk1882_tiu_depthwise(
    bmk1882_context_t *ctx,
    const bmk1882_depthwise_param_t *p);

typedef struct {
  bmk1882_matrix_lmem_t *res;
  bmk1882_matrix_lmem_t *left;
  bmk1882_matrix_lmem_t *right;
  bmk1882_matrix_lmem_t *bias;
  int lshift_width;
  int rshift_width;
  bool res_is_int8;
  ctrl_t ctrls;
} bmk1882_matrix_mac_param_t;

bmk1882_op_t * bmk1882_tiu_matrix_mac(
    bmk1882_context_t *ctx,
    const bmk1882_matrix_mac_param_t *p);

typedef struct {
  bmk1882_tensor_lmem_t *res;
  bmk1882_tensor_lmem_t *left;
  bmk1882_tensor_lmem_t *right;
} bmk1882_matrix_mac_2_param_t;

bmk1882_op_t * bmk1882_tiu_matrix_mac_2(
    bmk1882_context_t *ctx,
    const bmk1882_matrix_mac_2_param_t *p);

typedef struct {
  u32 version;
  u32 npu_num;
  u32 eu_num;
  u32 lmem_size;
  u32 lmem_banks;
  u32 lmem_bank_size;
  u32 tsm_size;
  u32 tsm_banks;
  u32 tsm_bank_size;
} bmk1882_chip_info_t;

bmk1882_chip_info_t bmk1882_chip_info(void);

bmk1882_tensor_lmem_stride_t bmk1882_tensor_lmem_default_stride(
    bmk1882_context_t *ctx,
    bmk1882_tensor_lmem_shape_t s,
    bool eu_align);

bmk1882_tensor_lmem_shape_t bmk1882_tensor_lmem_shape(
    int n, int c, int h, int w);
bmk1882_tensor_gmem_shape_t bmk1882_tensor_gmem_shape(
    int n, int c, int h, int w);

bmk1882_tensor_gmem_stride_t bmk1882_tensor_gmem_default_stride(
    bmk1882_tensor_gmem_shape_t s);

bmk1882_matrix_lmem_t * bmk1882_lmem_alloc_matrix(
    bmk1882_context_t *ctx,
    u8 tpu_idx,
    bmk1882_matrix_lmem_shape_t s,
    int eu_align);

bmk1882_matrix_lmem_shape_t bmk1882_matrix_lmem_default_shape(
    bmk1882_context_t *ctx,
    u32 row,
    u32 col);

bmk1882_matrix_lmem_t * bmk1882_lmem_alloc_matrix(
    bmk1882_context_t *ctx,
    u8 tpu_idx,
    bmk1882_matrix_lmem_shape_t s,
    int eu_align);

void bmk1882_lmem_free_matrix(
    bmk1882_context_t *ctx,
    bmk1882_matrix_lmem_t *t);

#ifdef __cplusplus
}
#endif

#endif /* __BMKERNEL_1880_H__ */
