/* Copyright Bitmain Technologies Inc.
 * Written by:
 *   Mingkang Qin <mingkang.qin@bitmain.com>
 * Created Time: 2018-05-30 11:18
 */

#ifndef _BM168X_PLAT_LIR_HPP_
#define _BM168X_PLAT_LIR_HPP_

#include <bmkernel/bm168x/bmkernel_1682.h>

namespace bmnet {

// DEPRECATED.
void bmk_fake_parallel_start();
// DEPRECATED.
void bmk_fake_parallel_end();

void parallel_enable();
void parallel_disable();

void tl_conv(tensor_lmem *ifmap, tensor_lmem *ofmap, tensor_lmem *weight, tensor_lmem *bias,
             tensor_lmem *relu, u8 ins_h, u8 ins_last_h, u8 ins_w, u8 ins_last_w, u8 dilation_h,
             u8 dilation_w, u8 pad_h_top, u8 pad_h_bottom, u8 pad_w_left, u8 pad_w_right,
             u8 stride_h, u8 stride_w, u16 kstride_n, u16 kstride_c, u16 kstride_h, u8 kernel_h,
             u8 kernel_w, bool kernel_flip, bool result_add);

void tl_pooling(tensor_lmem *ifmap, tensor_lmem *ofmap, tensor_lmem *oindex, tensor_lmem *relu,
                bool is_avg_pooling, int kh, int kw, u8 ins_h, u8 ins_last_h, u8 ins_w,
                u8 ins_last_w, u8 pad_h_top, u8 pad_h_bottom, u8 pad_w_left, u8 pad_w_right,
                u8 stride_h, u8 stride_w, float avg_pooling_const);

void tl_lrn_shift(tensor_lmem *src, tensor_lmem *dst, bool right_shift, int lrn_step);
void tl_load_stride(tensor_lmem *dst, gaddr_t ga, stride_t &gstride_p, ctrl_t c);
void tl_load_stride_u8(tensor_lmem *dst, gaddr_t ga, stride_t &gstride_p, ctrl_t c);
void tl_load(tensor_lmem *dst, gaddr_t ga, ctrl_t c);
void tl_store_stride(tensor_lmem *src, gaddr_t ga, stride_t &gstride_p, ctrl_t c);
void tl_store(tensor_lmem *src, gaddr_t ga, ctrl_t c);
void tl_copy_stride(tensor_lmem *dst, tensor_lmem *src, stride_t *st_dst, stride_t *st_src);
void tl_copy_gdma(tensor_lmem *dst, tensor_lmem *src);
void g_copy(gaddr_t g_dst, gaddr_t g_src, shape_t s, fmt_t fmt, ctrl_t ctrls);
void g_copy_stride(gaddr_t g_dst, shape_t s_dst, stride_t *t_dst,
                   gaddr_t g_src, shape_t s_src, stride_t *t_src,
                   fmt_t fmt, ctrl_t ctrls);
void tl_cw_transpose(tensor_lmem *dst, tensor_lmem *src);
void tl_mul(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, ctrl_t c);
void tl_div(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, ctrl_t c);
void tl_add(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, ctrl_t c);
void tl_sub(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, ctrl_t c);
void tl_sum(tensor_lmem *r, tensor_lmem *SRC, ctrl_t c);
void tl_mul_stride(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, stride_t *r_s,
                   stride_t *lhs_s, stride_t *rhs_s, ctrl_t c);
void tl_div_stride(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, stride_t *r_s,
                   stride_t *lhs_s, stride_t *rhs_s, ctrl_t c);
void tl_add_stride(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, stride_t *r_s,
                   stride_t *lhs_s, stride_t *rhs_s, ctrl_t c);
void tl_sub_stride(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, stride_t *r_s,
                   stride_t *lhs_s, stride_t *rhs_s, ctrl_t c);
void tl_mac(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, tensor_lmem *Bias, ctrl_t c);
void tl_add_square(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS);
void tl_sub_square(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS);
void tl_matrix_mac(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, tensor_lmem *Bias, ctrl_t c);
void tl_max(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS);
void tl_cmp(tensor_lmem *R_AB, tensor_lmem *R_CD, tensor_lmem *A, tensor_lmem *B, tensor_lmem *C,
            tensor_lmem *D);
void tl_img_sum(tensor_lmem *y, tensor_lmem *x, ctrl_t c);
void tl_xa(tensor_lmem *r, tensor_lmem *x, float a);
void tl_ex(tensor_lmem *y, tensor_lmem *x);
void tl_lnx(tensor_lmem *y, tensor_lmem *x);
void tl_rsq(tensor_lmem *y, tensor_lmem *x);
void tl_xn(tensor_lmem *y, tensor_lmem *x, int n);
void tl_arithmetic(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, TENSOR_OP op, bool add_result);
void tl_copy(tensor_lmem *r, tensor_lmem *LHS);
void tl_fill(tensor_lmem *r, float val);
void tl_cpu_op(const char *op_name, char *payload, size_t size);

}  // namespace bmnet

#endif
