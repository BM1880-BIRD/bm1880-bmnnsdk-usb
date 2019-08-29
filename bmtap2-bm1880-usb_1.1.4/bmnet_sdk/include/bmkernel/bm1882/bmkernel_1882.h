#ifndef __BMKERNEL_1882_H__
#define __BMKERNEL_1882_H__

#include <bmkernel/bm_kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BMK1882_TIU        0  // Tensor Instruction Unit
#define BMK1882_TDMA       1  // TPU DMA
#define BMK1882_SDMA       2  // Shared DMA
#define BMK1882_CPU        3  // CPU
#define BMK1882_ENGINE_NUM 4  // Number of Engines

typedef struct bmk1882_context bmk1882_context_t;
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

/*
 * Fundamental structures for tensor and matrix
 */

typedef struct {
  u32 n, c, w, col;
} bmk1882_matrix_lmem_shape_t;

typedef struct {
  u32 row, col;
} bmk1882_matrix_tgmem_shape_t;

typedef struct {
  u32 n, c, h;
} bmk1882_matrix_lmem_stride_t;

typedef struct {
  u32 row;
} bmk1882_matrix_tgmem_stride_t;

typedef struct {
  u32 n, c, h, w;
} bmk1882_tensor_lmem_shape_t;

typedef struct {
  u32 n, c, h, w;
} bmk1882_tensor_tgmem_shape_t;

typedef struct {
  u32 n, c, h, w;
} bmk1882_tensor_lmem_stride_t;

typedef struct {
  u32 n, c, h;
} bmk1882_tensor_tgmem_stride_t;

typedef struct {
  u32 start_address;
  fmt_t fmt;
  bmk1882_tensor_lmem_shape_t shape;
  bmk1882_tensor_lmem_stride_t stride;
} bmk1882_tensor_lmem_t;

typedef struct {
  u32 start_address;
  fmt_t fmt;
  bmk1882_matrix_lmem_shape_t shape;
  bmk1882_matrix_lmem_stride_t stride;
} bmk1882_matrix_lmem_t;

typedef struct {
  u8  base_reg_index;
  u64 start_address;
  fmt_t fmt;
  bmk1882_tensor_tgmem_shape_t shape;
  bmk1882_tensor_tgmem_stride_t stride;
} bmk1882_tensor_tgmem_t;

typedef struct {
  u8  base_reg_index;
  u64 start_address;
  u64 reserved_size;
  bmk1882_tensor_tgmem_shape_t shape;
  bmk1882_tensor_tgmem_stride_t stride;
  u8 bit_length;
} bmk1882_compressed_tensor_tgmem_t;

typedef struct {
  u8  base_reg_index;
  u64 start_address;
  bmk1882_matrix_tgmem_shape_t shape;
  bmk1882_matrix_tgmem_stride_t stride;
} bmk1882_matrix_tgmem_t;

/*
 * TDMA Engine APIs: LMEM to LMEM (L2L)
 */

typedef struct {
  const bmk1882_tensor_lmem_t *src;
  const bmk1882_tensor_lmem_t *dst;
} bmk1882_tdma_l2l_tensor_copy_param_t;

bmk1882_op_t * bmk1882_tdma_l2l_tensor_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2l_tensor_copy_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *src;
  const bmk1882_tensor_lmem_t *dst;
  int right_shift;
  u32 lrn_step;
} bmk1882_tdma_l2l_tensor_lrn_shift_param_t;

bmk1882_op_t * bmk1882_tdma_l2l_tensor_lrn_shift(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2l_tensor_lrn_shift_param_t *p);

/*
 * TDMA Engine APIs: LMEM to TSM/GMEM (L2TG)
 */

typedef struct {
  const bmk1882_tensor_lmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_tdma_l2tg_tensor_copy_param_t;

bmk1882_op_t * bmk1882_tdma_l2t_tensor_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_copy_param_t *p);

bmk1882_op_t * bmk1882_tdma_l2g_tensor_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_copy_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_tdma_l2tg_tensor_copy_nc_transposed_param_t;

bmk1882_op_t * bmk1882_tdma_l2t_tensor_copy_nc_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_copy_nc_transposed_param_t *p);

bmk1882_op_t * bmk1882_tdma_l2g_tensor_copy_nc_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_copy_nc_transposed_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_tdma_l2tg_tensor_copy_cw_transposed_param_t;

bmk1882_op_t * bmk1882_tdma_l2t_tensor_copy_cw_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_copy_cw_transposed_param_t *p);

bmk1882_op_t * bmk1882_tdma_l2g_tensor_copy_cw_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_copy_cw_transposed_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *src;
  const bmk1882_compressed_tensor_tgmem_t *dst;
} bmk1882_tdma_l2tg_tensor_copy_compressed_param_t;

bmk1882_op_t * bmk1882_tdma_l2t_tensor_copy_compressed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_copy_compressed_param_t *p);

bmk1882_op_t * bmk1882_tdma_l2g_tensor_copy_compressed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_copy_compressed_param_t *p);

typedef struct {
  u8 constant;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_tdma_l2tg_tensor_fill_constant_param_t;

bmk1882_op_t * bmk1882_tdma_l2t_tensor_fill_constant(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_fill_constant_param_t *p);

bmk1882_op_t * bmk1882_tdma_l2g_tensor_fill_constant(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_tensor_fill_constant_param_t *p);

typedef struct {
  const bmk1882_matrix_lmem_t *src;
  const bmk1882_matrix_tgmem_t *dst;
} bmk1882_tdma_l2tg_matrix_copy_param_t;

bmk1882_op_t * bmk1882_tdma_l2t_matrix_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_matrix_copy_param_t *p);

bmk1882_op_t * bmk1882_tdma_l2g_matrix_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_matrix_copy_param_t *p);

typedef struct {
  u32 src_address;
  u8 dst_base_reg_index;
  u64 dst_address;
  u32 bytes;
} bmk1882_tdma_l2tg_general_copy_param_t;

bmk1882_op_t * bmk1882_tdma_l2t_general_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_general_copy_param_t *p);

bmk1882_op_t * bmk1882_tdma_l2g_general_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_l2tg_general_copy_param_t *p);

/*
 * TDMA Engine APIs: TSM/GMEM to LMEM (TG2L)
 */

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_lmem_t *dst;
} bmk1882_tdma_tg2l_tensor_copy_param_t;

bmk1882_op_t * bmk1882_tdma_t2l_tensor_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_copy_param_t *p);

bmk1882_op_t * bmk1882_tdma_g2l_tensor_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_copy_param_t *p);

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_lmem_t *dst;
} bmk1882_tdma_tg2l_tensor_copy_nc_transposed_param_t;

bmk1882_op_t * bmk1882_tdma_t2l_tensor_copy_nc_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_copy_nc_transposed_param_t *p);

bmk1882_op_t * bmk1882_tdma_g2l_tensor_copy_nc_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_copy_nc_transposed_param_t *p);

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_lmem_t *dst;
} bmk1882_tdma_tg2l_tensor_copy_chw_rotated_param_t;

bmk1882_op_t * bmk1882_tdma_t2l_tensor_copy_chw_rotated(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_copy_chw_rotated_param_t *p);

bmk1882_op_t * bmk1882_tdma_g2l_tensor_copy_chw_rotated(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_copy_chw_rotated_param_t *p);

typedef struct {
  const bmk1882_compressed_tensor_tgmem_t *src;
  const bmk1882_tensor_lmem_t *dst;
} bmk1882_tdma_tg2l_tensor_copy_decompressed_param_t;

bmk1882_op_t * bmk1882_tdma_t2l_tensor_copy_decompressed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_copy_decompressed_param_t *p);

bmk1882_op_t * bmk1882_tdma_g2l_tensor_copy_decompressed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_copy_decompressed_param_t *p);

typedef struct {
  u8 constant;
  const bmk1882_tensor_lmem_t *dst;
} bmk1882_tdma_tg2l_tensor_fill_constant_param_t;

bmk1882_op_t * bmk1882_tdma_tg2l_tensor_fill_constant(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_tensor_fill_constant_param_t *p);

typedef struct {
  const bmk1882_matrix_tgmem_t *src;
  const bmk1882_matrix_lmem_t *dst;
} bmk1882_tdma_tg2l_matrix_copy_param_t;

bmk1882_op_t * bmk1882_tdma_t2l_matrix_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_matrix_copy_param_t *p);

bmk1882_op_t * bmk1882_tdma_g2l_matrix_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_matrix_copy_param_t *p);

typedef struct {
  const bmk1882_matrix_tgmem_t *src;
  const bmk1882_matrix_lmem_t *dst;
} bmk1882_tdma_tg2l_matrix_copy_row_col_transposed_param_t;

bmk1882_op_t * bmk1882_tdma_t2l_matrix_copy_row_col_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_matrix_copy_row_col_transposed_param_t *p);

bmk1882_op_t * bmk1882_tdma_g2l_matrix_copy_row_col_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_matrix_copy_row_col_transposed_param_t *p);

typedef struct {
  u8 src_base_reg_index;
  u64 src_address;
  u32 dst_address;
  u32 bytes;
} bmk1882_tdma_tg2l_general_copy_param_t;

bmk1882_op_t * bmk1882_tdma_t2l_general_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_general_copy_param_t *p);

bmk1882_op_t * bmk1882_tdma_g2l_general_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tdma_tg2l_general_copy_param_t *p);

/*
 * SDMA Engine APIs: TSM to GMEM (T2G)
 */

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_t2g_tensor_copy_param_t;

bmk1882_op_t * bmk1882_sdma_t2g_tensor_copy(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_t2g_tensor_copy_param_t *p);

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_t2g_tensor_copy_nc_transposed_param_t;

bmk1882_op_t * bmk1882_sdma_t2g_tensor_copy_nc_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_t2g_tensor_copy_nc_transposed_param_t *p);

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_t2g_tensor_copy_cw_transposed_param_t;

bmk1882_op_t * bmk1882_sdma_t2g_tensor_copy_cw_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_t2g_tensor_copy_cw_transposed_param_t *p);

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_compressed_tensor_tgmem_t *dst;
} bmk1882_sdma_t2g_tensor_copy_compressed_param_t;

bmk1882_op_t * bmk1882_sdma_t2g_tensor_copy_compressed(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_t2g_tensor_copy_compressed_param_t *p);

typedef struct {
  u8 constant;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_t2g_tensor_fill_constant_param_t;

bmk1882_op_t * bmk1882_sdma_t2g_tensor_fill_constant(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_t2g_tensor_fill_constant_param_t *p);

typedef struct {
  const bmk1882_matrix_tgmem_t *src;
  const bmk1882_matrix_tgmem_t *dst;
} bmk1882_sdma_t2g_matrix_copy_param_t;

bmk1882_op_t * bmk1882_sdma_t2g_matrix_copy(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_t2g_matrix_copy_param_t *p);

typedef struct {
  u8 src_base_reg_index;
  u64 src_address;
  u8 dst_base_reg_index;
  u64 dst_address;
  u32 bytes;
} bmk1882_sdma_t2g_general_copy_param_t;

bmk1882_op_t * bmk1882_sdma_t2g_general_copy(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_t2g_general_copy_param_t *p);

/*
 * SDMA Engine APIs: GMEM to TSM (G2T)
 */

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_g2t_tensor_copy_param_t;

bmk1882_op_t * bmk1882_sdma_g2t_tensor_copy(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_g2t_tensor_copy_param_t *p);

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_g2t_tensor_copy_nc_transposed_param_t;

bmk1882_op_t * bmk1882_sdma_g2t_tensor_copy_nc_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_g2t_tensor_copy_nc_transposed_param_t *p);

typedef struct {
  const bmk1882_tensor_tgmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_g2t_tensor_copy_chw_rotated_param_t;

bmk1882_op_t * bmk1882_sdma_g2t_tensor_copy_chw_rotated(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_g2t_tensor_copy_chw_rotated_param_t *p);

typedef struct {
  const bmk1882_compressed_tensor_tgmem_t *src;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_g2t_tensor_copy_decompressed_param_t;

bmk1882_op_t * bmk1882_sdma_g2t_tensor_copy_decompressed(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_g2t_tensor_copy_decompressed_param_t *p);

typedef struct {
  u8 constant;
  const bmk1882_tensor_tgmem_t *dst;
} bmk1882_sdma_g2t_tensor_fill_constant_param_t;

bmk1882_op_t * bmk1882_sdma_g2t_tensor_fill_constant(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_g2t_tensor_fill_constant_param_t *p);

typedef struct {
  const bmk1882_matrix_tgmem_t *src;
  const bmk1882_matrix_tgmem_t *dst;
} bmk1882_sdma_g2t_matrix_copy_param_t;

bmk1882_op_t * bmk1882_sdma_g2t_matrix_copy(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_g2t_matrix_copy_param_t *p);

typedef struct {
  const bmk1882_matrix_tgmem_t *src;
  const bmk1882_matrix_tgmem_t *dst;
} bmk1882_sdma_g2t_matrix_copy_row_col_transposed_param_t;

bmk1882_op_t * bmk1882_sdma_g2t_matrix_copy_row_col_transposed(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_g2t_matrix_copy_row_col_transposed_param_t *p);

typedef struct {
  u8 src_base_reg_index;
  u64 src_address;
  u8 dst_base_reg_index;
  u64 dst_address;
  u32 bytes;
} bmk1882_sdma_g2t_general_copy_param_t;

bmk1882_op_t * bmk1882_sdma_g2t_general_copy(
    bmk1882_context_t *ctx,
    const bmk1882_sdma_g2t_general_copy_param_t *p);

/*
 * TIU Engine APIs
 *
 * General rules for tensor arithmetic APIs:
 *
 * 1, All tensors can be either signed or unsigned
 *    if not mentioned otherwise.
 * 2, A tensor @x with both @x_high and @x_low as
 *    parameters can optionally be 8-bit (when @x_high
 *    is NULL) or 16-bit (otherwise).
 */

typedef struct {
  const bmk1882_tensor_lmem_t *res_high;
  const bmk1882_tensor_lmem_t *res_low;
  const bmk1882_tensor_lmem_t *a;
  int b_is_const;
  union {
    const bmk1882_tensor_lmem_t *b;
    struct {
      s8 b_val;
      int b_is_signed;
    };
  };
  u8 rshift_bits;
} bmk1882_tiu_element_wise_mul_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_mul(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_mul_param_t *p);

/*
 * @res = @a * @b + @res
 *
 * 1, @res_high must not be NULL since input @res must be 16-bit.
 * 2, If output @res is 8-bit (@res_is_int8 == 1), only @res_low
 *    is used as output tensor.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *res_high;
  const bmk1882_tensor_lmem_t *res_low;
  const bmk1882_tensor_lmem_t *a;
  int b_is_const;
  union {
    const bmk1882_tensor_lmem_t *b;
    struct {
      s8 b_val;
      int b_is_signed;
    };
  };
  int res_is_int8;
  u8 lshift_bits;
  u8 rshift_bits;
} bmk1882_tiu_element_wise_mac_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_mac(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_mac_param_t *p);

/*
 * @a and @b must all be 16-bit.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *res_high;
  const bmk1882_tensor_lmem_t *res_low;
  const bmk1882_tensor_lmem_t *a_high;
  const bmk1882_tensor_lmem_t *a_low;
  int b_is_const;
  union {
    struct {
      const bmk1882_tensor_lmem_t *b_high;
      const bmk1882_tensor_lmem_t *b_low;
    };
    struct {
      s16 b_val;
      int b_is_signed;
    };
  };
  u8 rshift_bits;
} bmk1882_tiu_element_wise_add_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_add(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_add_param_t *p);

/*
 * 1, @a and @b must all be 16-bit.
 * 2, @res must be signed.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *res_high;
  const bmk1882_tensor_lmem_t *res_low;
  const bmk1882_tensor_lmem_t *a_high;
  const bmk1882_tensor_lmem_t *a_low;
  const bmk1882_tensor_lmem_t *b_high;
  const bmk1882_tensor_lmem_t *b_low;
  u8 rshift_bits;
} bmk1882_tiu_element_wise_sub_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_sub(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_sub_param_t *p);

/*
 * @a and @b must both be signed or unsigned.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *max;
  const bmk1882_tensor_lmem_t *a;
  int b_is_const;
  union {
    const bmk1882_tensor_lmem_t *b;
    struct {
      s8 b_val;
      int b_is_signed;
    };
  };
} bmk1882_tiu_element_wise_max_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_max(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_max_param_t *p);

/*
 * @a and @b must both be signed or unsigned.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *min;
  const bmk1882_tensor_lmem_t *a;
  int b_is_const;
  union {
    const bmk1882_tensor_lmem_t *b;
    struct {
      s8 b_val;
      int b_is_signed;
    };
  };
} bmk1882_tiu_element_wise_min_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_min(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_min_param_t *p);

/*
 * 1, @a must be 16-bit and signed.
 * 2, @res must be 16-bit.
 * 3, @bits must be signed and must range in [-16, 16].
 */
typedef struct {
  const bmk1882_tensor_lmem_t *res_high;
  const bmk1882_tensor_lmem_t *res_low;
  const bmk1882_tensor_lmem_t *a_high;
  const bmk1882_tensor_lmem_t *a_low;
  const bmk1882_tensor_lmem_t *bits;
} bmk1882_tiu_element_wise_arith_shift_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_arith_shift(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_arith_shift_param_t *p);

/*
 * TODO: bmk1882_tl_logic_shift()
 */

typedef struct {
  const bmk1882_tensor_lmem_t *res;
  const bmk1882_tensor_lmem_t *a;
  const bmk1882_tensor_lmem_t *b;
} bmk1882_tiu_element_wise_and_int8_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_and_int8(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_and_int8_param_t *p);

/*
 * All parameters must be 16-bit.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *res_high;
  const bmk1882_tensor_lmem_t *res_low;
  const bmk1882_tensor_lmem_t *a_high;
  const bmk1882_tensor_lmem_t *a_low;
  const bmk1882_tensor_lmem_t *b_high;
  const bmk1882_tensor_lmem_t *b_low;
} bmk1882_tiu_element_wise_and_int16_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_and_int16(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_and_int16_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *res;
  const bmk1882_tensor_lmem_t *a;
  const bmk1882_tensor_lmem_t *b;
} bmk1882_tiu_element_wise_or_int8_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_or_int8(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_or_int8_param_t *p);

/*
 * All parameters must be 16-bit.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *res_high;
  const bmk1882_tensor_lmem_t *res_low;
  const bmk1882_tensor_lmem_t *a_high;
  const bmk1882_tensor_lmem_t *a_low;
  const bmk1882_tensor_lmem_t *b_high;
  const bmk1882_tensor_lmem_t *b_low;
} bmk1882_tiu_element_wise_or_int16_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_or_int16(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_or_int16_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *res;
  const bmk1882_tensor_lmem_t *a;
  const bmk1882_tensor_lmem_t *b;
} bmk1882_tiu_element_wise_xor_int8_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_xor_int8(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_xor_int8_param_t *p);

/*
 * All parameters must be 16-bit.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *res_high;
  const bmk1882_tensor_lmem_t *res_low;
  const bmk1882_tensor_lmem_t *a_high;
  const bmk1882_tensor_lmem_t *a_low;
  const bmk1882_tensor_lmem_t *b_high;
  const bmk1882_tensor_lmem_t *b_low;
} bmk1882_tiu_element_wise_xor_int16_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_xor_int16(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_xor_int16_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *src;
  const bmk1882_tensor_lmem_t *dst;
} bmk1882_tiu_element_wise_copy_param_t;

bmk1882_op_t * bmk1882_tiu_element_wise_copy(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_element_wise_copy_param_t *p);

/*
 * @res and @a must be both signed or unsigned.
 * TODO: explain the shape and layout of @res when it's 16-bit
 */
typedef struct {
  int res_is_int8;
  const bmk1882_tensor_lmem_t *res;
  const bmk1882_tensor_lmem_t *input;
  u8 rshift_bits;
} bmk1882_tiu_mdsum_param_t;

bmk1882_op_t * bmk1882_tiu_mdsum(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_mdsum_param_t *p);

/*
 * NOTE:
 *   @table is treated logically as a linear list of
 *   length @table_n, where @table_n is a multiple of
 *   16 and is smaller than or equal to 256.
 *   When stored in local memory, @table is a tensor
 *   of shape (1, npu_num, 1, @table_n), that is, the
 *   data of the linear list should be copied across
 *   each NPU's local memory by user. The behavior when
 *   these copies differ is undefined.
 */
typedef struct {
  const bmk1882_tensor_lmem_t *ofmap;
  const bmk1882_tensor_lmem_t *ifmap;
  const bmk1882_tensor_lmem_t *table;
} bmk1882_tiu_lookup_table_param_t;

bmk1882_op_t * bmk1882_tiu_lookup_table(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_lookup_table_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *ofmap;
  const bmk1882_tensor_lmem_t *ifmap;
  const bmk1882_tensor_lmem_t *weight;
  const bmk1882_tensor_lmem_t *bias;
  int enable_double_conv;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  u8 dilation_h, dilation_w;
  int relu_enable;
  u8 rshift_bits;
  u8 ps32_mode;
} bmk1882_tiu_convolution_param_t;

bmk1882_op_t * bmk1882_tiu_convolution(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_convolution_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *ofmap;
  const bmk1882_tensor_lmem_t *ifmap;
  u8 kh, kw;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
} bmk1882_tiu_max_pooling_param_t;

bmk1882_op_t * bmk1882_tiu_max_pooling(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_max_pooling_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *ofmap;
  const bmk1882_tensor_lmem_t *ifmap;
  u8 kh, kw;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  u8 avg_pooling_const;
  u8 rshift_bits;
} bmk1882_tiu_average_pooling_param_t;

bmk1882_op_t * bmk1882_tiu_average_pooling(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_average_pooling_param_t *p);

typedef struct {
  const bmk1882_tensor_lmem_t *ofmap;
  const bmk1882_tensor_lmem_t *ifmap;
  const bmk1882_tensor_lmem_t *weight;
  const bmk1882_tensor_lmem_t *bias;
  u8 ins_h, ins_last_h;
  u8 ins_w, ins_last_w;
  u8 pad_top, pad_bottom;
  u8 pad_left, pad_right;
  u8 stride_h, stride_w;
  u8 rshift_bits;
} bmk1882_tiu_depthwise_convolution_param_t;

bmk1882_op_t * bmk1882_tiu_depthwise_convolution(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_depthwise_convolution_param_t *p);

typedef struct {
  const bmk1882_matrix_lmem_t *res;
  const bmk1882_matrix_lmem_t *left;
  const bmk1882_matrix_lmem_t *right;
  const bmk1882_matrix_lmem_t *bias;
  u8 lshift_bits;
  u8 rshift_bits;
  int res_is_int8;
  int relu_enable;
  int add_result;
} bmk1882_tiu_matrix_multiplication_param_t;

bmk1882_op_t * bmk1882_tiu_matrix_multiplication(
    bmk1882_context_t *ctx,
    const bmk1882_tiu_matrix_multiplication_param_t *p);

/*
 * Helpers
 */

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
    int eu_align);

bmk1882_tensor_tgmem_stride_t bmk1882_tensor_tgmem_default_stride(
    bmk1882_tensor_tgmem_shape_t s);

bmk1882_matrix_lmem_shape_t bmk1882_matrix_lmem_default_shape(
    bmk1882_context_t *ctx,
    u32 row,
    u32 col);

bmk1882_matrix_lmem_stride_t bmk1882_matrix_lmem_default_stride(
    bmk1882_context_t *ctx,
    bmk1882_matrix_lmem_shape_t s);

bmk1882_tensor_lmem_t * bmk1882_lmem_alloc_tensor(
    bmk1882_context_t *ctx,
    bmk1882_tensor_lmem_shape_t s,
    fmt_t fmt,
    int eu_align);

bmk1882_tensor_lmem_t * bmk1882_lmem_alloc_ps32_tensor(
    bmk1882_context_t *ctx,
    bmk1882_tensor_lmem_shape_t s,
    fmt_t fmt,
    int eu_align);

void bmk1882_lmem_free_tensor(
    bmk1882_context_t *ctx,
    const bmk1882_tensor_lmem_t *t);

bmk1882_matrix_lmem_t * bmk1882_lmem_alloc_matrix(
    bmk1882_context_t *ctx,
    bmk1882_matrix_lmem_shape_t s,
    fmt_t fmt,
    int eu_align);

void bmk1882_lmem_free_matrix(
    bmk1882_context_t *ctx,
    const bmk1882_matrix_lmem_t *t);

#ifdef __cplusplus
}
#endif

#endif /* __BMKERNEL_1880_H__ */
