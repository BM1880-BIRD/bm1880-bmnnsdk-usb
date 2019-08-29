#ifndef __BMKERNEL_1682_H__
#define __BMKERNEL_1682_H__

#include <bmkernel/bm_kernel_legacy.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline const_fp32_t tl_constant(tensor_lmem *tlp)
{
  return tlp->operand.const_fp32;
}

bmerr_t bmk1682_dmabuf_convert(uint8_t *cmdbuf, size_t sz, uint8_t *dmabuf);
bmerr_t bmk1682_dmabuf_size(uint8_t *cmdbuf, size_t sz, size_t *psize);
bmerr_t bmk1682_dmabuf_relocate(uint8_t *dmabuf, u64 dmabuf_devaddr);
void bmk1682_dmabuf_dump(uint8_t *dmabuf);

typedef struct ec_desc bmk1682_op_t;
typedef bmk_chip_info_t bmk1682_chip_info_t;
typedef bmk_info_t bmk1682_info_t;

bmk_chip_info_t bmk1680_chip_info();

bmk1682_chip_info_t bmk1682_chip_info();

void * bmk1682_register(bmk1682_info_t *info);
void bmk1682_cleanup(void *ctx);
void bmk1682_enter(void *ctx);
void bmk1682_reset(void);
void bmk1682_exit(void);
u8 *bmk1682_acquire_cmdbuf(u32 *size);

void bmk1682_parallel_enable(void);
void bmk1682_parallel_disable(void);

void bmk1682_create_streams(int nr_streams);
void bmk1682_destroy_streams();
void bmk1682_set_stream(int i);

void bmk1682_add_dependency(
    bmk1682_op_t *before,
    bmk1682_op_t *after);

typedef u32 BLOB_OP;
#define BLOB_ADD 0
#define BLOB_SUB 1
#define BLOB_MUL 2
#define BLOB_DIV 3
#define BLOB_INVALID 4

typedef u32 SFU_OP;
#define SFU_XN 0  // POWN
#define SFU_EX 1  // EXP
#define SFU_LNX 2  // LNX
#define SFU_RSQ 3  // RSQ
#define SFU_XA 4  // POWEREXP
#define SFU_INVALID 5

typedef u32 TENSOR_OP;
#define TENSOR_ADD 0
#define TENSOR_SUB 1
#define TENSOR_MUL 2
#define TENSOR_DIV 3
#define TENSOR_MAX 4
#define TENSOR_CPY 5
#define TENSOR_MAC 6

typedef u32 LINEAR_OP;
#define LINEAR_MAC 0
#define LINEAR_ADD_SQR 1
#define LINEAR_SUB_SQR 2
#define LINEAR_INVALID 3

void bmk1682_tl_shape_to_nchw(shape_t s, int *n, int *c, int *h, int *w);

int bmk1682_tl_shape_to_size(shape_t s, bool aligned, fmt_t fmt);

int bmk1682_tl_size(tensor_lmem *tlp);

size_t bmk1682_tg_shape_to_size(shape_t s, fmt_t fmt);

tensor_lmem * bmk1682_tl_alloc(shape_t s, fmt_t fmt, u32 ctrls);
tensor_lmem * bmk1682_tl_alloc_bank(u32 bank_id, shape_t s, fmt_t fmt, u32 ctrls);

tensor_lmem * bmk1682_tl_prealloc(laddr_t la, shape_t s, fmt_t fmt);
tensor_lmem * bmk1682_tl_prealloc_align(laddr_t la, shape_t s, fmt_t fmt);

tensor_lmem * bmk1682_tl_alloc_const(float fval);
tensor_lmem * bmk1682_tl_alloc_const_u32(u32 ival);

tensor_lmem * bmk1682_tl_slice(tensor_lmem *tlp, int n_start, int n_end);

void bmk1682_tl_free(tensor_lmem *tlp);

/*
 * TPU API
 */
bmk1682_op_t * bmk1682_tl_arithmetic(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b,
    int op_code, bool ra);

bmk1682_op_t * bmk1682_tl_add(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b, ctrl_t ctrls);

bmk1682_op_t * bmk1682_tl_sub(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b, ctrl_t ctrls);

bmk1682_op_t * bmk1682_tl_mul(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b, ctrl_t ctrls);

bmk1682_op_t * bmk1682_tl_div(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b, ctrl_t ctrls);

bmk1682_op_t * bmk1682_tl_add_stride(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b,
    stride_t *r_s, stride_t *a_s, stride_t *b_s);

bmk1682_op_t * bmk1682_tl_sub_stride(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b,
    stride_t *r_s, stride_t *a_s, stride_t *b_s);

bmk1682_op_t * bmk1682_tl_mul_stride(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b,
    stride_t *r_s, stride_t *a_s, stride_t *b_s, ctrl_t ctrls);

bmk1682_op_t * bmk1682_tl_div_stride(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem *b,
    stride_t *r_s, stride_t *a_s, stride_t *b_s);

bmk1682_op_t * bmk1682_tl_copy_stride(
    tensor_lmem *dst,
    tensor_lmem *src,
    stride_t *pdstride,
    stride_t *psstride);

bmk1682_op_t * bmk1682_tl_copy(tensor_lmem *dst, tensor_lmem *src);

bmk1682_op_t * bmk1682_tl_cw_transpose(tensor_lmem *dst, tensor_lmem *src);

bmk1682_op_t * bmk1682_tl_fill(tensor_lmem * dst, float val);
bmk1682_op_t * bmk1682_tl_clear(tensor_lmem *tlp);

bmk1682_op_t * bmk1682_tl_ex(tensor_lmem *y, tensor_lmem *x);
bmk1682_op_t * bmk1682_tl_lnx(tensor_lmem *y, tensor_lmem *x);
bmk1682_op_t * bmk1682_tl_xa(tensor_lmem *y, tensor_lmem *x, float a);
bmk1682_op_t * bmk1682_tl_xn(tensor_lmem *y, tensor_lmem *x, int n);
bmk1682_op_t * bmk1682_tl_rsq(tensor_lmem *y, tensor_lmem *x);

bmk1682_op_t * bmk1682_tl_mac(
    tensor_lmem *y, tensor_lmem *s,
    tensor_lmem *a, tensor_lmem *b,
    ctrl_t ctrls);

bmk1682_op_t * bmk1682_tl_add_square(
    tensor_lmem *y,
    tensor_lmem *a,
    tensor_lmem *b);

bmk1682_op_t * bmk1682_tl_sub_square(
    tensor_lmem *y,
    tensor_lmem *a,
    tensor_lmem *b);

bmk1682_op_t * bmk1682_tl_max(tensor_lmem *y, tensor_lmem *a, tensor_lmem *b);
bmk1682_op_t * bmk1682_tl_cmp(
    tensor_lmem *y, tensor_lmem *r,
    tensor_lmem *a, tensor_lmem *b,
    tensor_lmem *c, tensor_lmem *d);

bmk1682_op_t * bmk1682_tl_sum(tensor_lmem *y, tensor_lmem *x, ctrl_t ctrls);
bmk1682_op_t * bmk1682_tl_img_sum(tensor_lmem *y, tensor_lmem *x, ctrl_t ctrls);

bmk1682_op_t * bmk1682_tl_matrix_mac(
    tensor_lmem *ly,
    tensor_lmem *ll,
    tensor_lmem *lr,
    tensor_lmem *lb,
    ctrl_t ctrls);

bmk1682_op_t * bmk1682_tl_conv(
    tensor_lmem *ifmap, tensor_lmem *ofmap, tensor_lmem *weight,
    tensor_lmem *bias, tensor_lmem *relu,
    u8 ins_h, u8 ins_last_h, u8 ins_w, u8 ins_last_w,
    u8 dilation_h, u8 dilation_w,
    u8 pad_h_top, u8 pad_h_bottom, u8 pad_w_left, u8 pad_w_right,
    u8 stride_h, u8 stride_w, bool kernel_flip, bool result_add);

bmk1682_op_t * bmk1682_tl_conv_kstride(
    tensor_lmem *ifmap, tensor_lmem *ofmap, tensor_lmem *weight,
    tensor_lmem *bias, tensor_lmem *relu,
    u8 ins_h, u8 ins_last_h, u8 ins_w, u8 ins_last_w,
    u8 dilation_h, u8 dilation_w,
    u8 pad_h_top, u8 pad_h_bottom, u8 pad_w_left, u8 pad_w_right,
    u8 stride_h, u8 stride_w,
    u16 kstride_n, u16 kstride_c, u16 kstride_h, u8 kernel_h, u8 kernel_w,
    bool kernel_flip, bool result_add);

bmk1682_op_t * bmk1682_tl_pooling_fwd(
    tensor_lmem *ifmap, tensor_lmem *ofmap,
    tensor_lmem *oindex, tensor_lmem *relu,
    bool is_avg_pooling,
    int kh, int kw,
    u8 ins_h, u8 ins_last_h, u8 ins_w, u8 ins_last_w,
    u8 pad_h_top, u8 pad_h_bottom, u8 pad_w_left, u8 pad_w_right,
    u8 stride_h, u8 stride_w,
    float avg_pooling_const);

bmk1682_op_t * bmk1682_tl_tanh_fwd(
    tensor_lmem *r, tensor_lmem *a);
bmk1682_op_t * bmk1682_tl_tanh_bwd(
    tensor_lmem *r, tensor_lmem *a, tensor_lmem * b);
bmk1682_op_t * bmk1682_tl_sigmoid_fwd(
    tensor_lmem *r, tensor_lmem * a);
bmk1682_op_t * bmk1682_tl_sigmoid_bwd(
    tensor_lmem *r , tensor_lmem *a , tensor_lmem *b);

/*
 * GDMA API
 */
bmk1682_op_t * __tl_load(
    tensor_lmem *tlp, gaddr_t ga,
    const stride_t *gstride_p, fmt_t gmem_fmt,
    bool transposed, bool result_add);

#define bmk1682_tl_load(tlp, ga, ctrls)                                 \
  __tl_load(tlp, ga, NULL, FMT_INVALID, ctrls & CTRL_TP, ctrls & CTRL_RA)
#define bmk1682_tl_load_stride(tlp, ga, gstride, ctrls)                 \
  __tl_load(tlp, ga, &gstride, FMT_INVALID, ctrls & CTRL_TP, ctrls & CTRL_RA)
#define bmk1682_tl_load_stride_u8(tlp, ga, gstride, ctrls)              \
  __tl_load(tlp, ga, &gstride, FMT_U8, ctrls & CTRL_TP, ctrls & CTRL_RA)

bmk1682_op_t * __tl_store(
    tensor_lmem *tlp,
    gaddr_t ga,
    const stride_t *gstride_p,
    fmt_t data_fmt,
    bool is_transpose,
    bool result_add);

#define bmk1682_tl_store(tlp, ga, ctrls)                                \
  __tl_store(tlp, ga, NULL, FMT_INVALID, ctrls & CTRL_TP, ctrls & CTRL_RA)
#define bmk1682_tl_store_stride(tlp, ga, gstride, ctrls)                \
  __tl_store(tlp, ga, &gstride, FMT_INVALID, ctrls & CTRL_TP, ctrls & CTRL_RA)
#define bmk1682_tl_store_fmt(tlp, ga, gfmt, ctrls)                      \
  __tl_store(tlp, ga, NULL, gfmt, ctrls & CTRL_TP, ctrls & CTRL_RA)

bmk1682_op_t * bmk1682_tl_lrn_shift(
    tensor_lmem * src,
    tensor_lmem * dst,
    bool right_shift,
    int lrn_step);

bmk1682_op_t * bmk1682_tl_copy_gdma(tensor_lmem *dst, tensor_lmem *src);
bmk1682_op_t * bmk1682_tl_fill_gdma(tensor_lmem *dst, float val);

bmk1682_op_t * bmk1682_g_copy_stride(
    gaddr_t d_ga, shape_t d_shape, stride_t *p_d_stride,
    gaddr_t s_ga, shape_t s_shape, stride_t *p_s_stride,
    fmt_t fmt, ctrl_t ctrls);

bmk1682_op_t * bmk1682_g_fill_stride(
    gaddr_t ga, shape_t shape, stride_t *g_stride,
    fmt_t fmt, float val);

bmk1682_op_t * bmk1682_g_fill(
    gaddr_t ga, shape_t shape, fmt_t fmt, float val);

bmk1682_op_t * bmk1682_g_copy(
    gaddr_t d_ga, gaddr_t s_ga, shape_t shape, fmt_t fmt, ctrl_t ctrls);

/*
 * CPU API and others
 */
void arm_sync(const char *commnet);
void bmk1682_cpu_op(const char* op_name, char *params, int size);

#ifdef __cplusplus
}
#endif

#endif /* __BMKERNEL_1682_H__ */
