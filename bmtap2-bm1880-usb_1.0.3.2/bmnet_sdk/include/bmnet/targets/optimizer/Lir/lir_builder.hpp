/* Copyright Bitmain Technologies Inc.
* Written by:
*   Mingkang Qin <mingkang.qin@bitmain.com>
* Created Time: 2018-05-11 14:27
*/
#ifndef _LIR_BUILDER_HPP_
#define _LIR_BUILDER_HPP_

#include <bmnet/targets/optimizer/Lir/lir_function.hpp>

namespace bmnet {

class LirBuilder{
public:
  LirBuilder(LirFunction * func):     F_(func){}
  LirFunction * F_;

  std::string getLayerTypeAndLayerName();
  void setLayerTypeAndLayerName(LirInst* lirInst);
  FakeParallelStartInst * buildFakeParallelStartInst();
  FakeParallelEndInst * buildFakeParallelEndInst();

  ConvInst * buildConvInst( tensor_lmem *ifmap,
                                 tensor_lmem *ofmap,
                                 tensor_lmem *weight,
                                 tensor_lmem *bias,
                                 tensor_lmem *relu,
                                 u8 ins_h, u8 ins_last_h, u8 ins_w, u8 ins_last_w,
                                 u8 dilation_h, u8 dilation_w,
                                 u8 pad_h_top, u8 pad_h_bottom, u8 pad_w_left, u8 pad_w_right,
                                 u8 stride_h, u8 stride_w,
                                 u16 kstride_n, u16 kstride_c, u16 kstride_h,
                                 u8 kernel_h, u8 kernel_w,
                                 bool kernel_flip,
                                 bool result_add);

  PoolingInst * buildPoolingInst( tensor_lmem *ifmap,
                                        tensor_lmem *ofmap,
                                        tensor_lmem *oindex,
                                        tensor_lmem *relu,
                                        bool is_avg_pooling,
                                        int kh, int kw,
                                        u8 ins_h, u8 ins_last_h, u8 ins_w, u8 ins_last_w,
                                        u8 pad_h_top, u8 pad_h_bottom, u8 pad_w_left, u8 pad_w_right,
                                        u8 stride_h, u8 stride_w,
                                        float avg_pooling_const);

  LrnShiftInst * buildLrnShiftInst(    tensor_lmem *src,
                                          tensor_lmem *dst,
                                          bool right_shift,
                                          int lrn_step);

  LoadStrideInst * buildLoadStrideInst( tensor_lmem     *tlp, gaddr_t ga, stride_t &gstride_p, ctrl_t c);
  LoadInst * buildLoadInst( tensor_lmem     *tlp, gaddr_t ga, ctrl_t c);
  StoreStrideInst * buildStoreStrideInst ( tensor_lmem* tlp,         gaddr_t ga, stride_t  &gstride_p, ctrl_t c);
  StoreInst * buildStoreInst (tensor_lmem     *tlp,  gaddr_t ga, ctrl_t c);
  CopyStrideInst *buildCopyStrideInst(tensor_lmem *dst, tensor_lmem *src,
                                      stride_t * st_dst, stride_t * st_src);
  CopyGdmaInst *buildCopyGdmaInst(tensor_lmem *dst, tensor_lmem *src);
  TransposeCWInst *buildTransposeCWInst(tensor_lmem *dst, tensor_lmem *src);
  GCopyInst * buildGCopyInst(gaddr_t g_dst, gaddr_t g_src, shape_t s, fmt_t fmt);
  GCopyStrideInst * buildGCopyStrideInst(gaddr_t g_dst, shape_t s_dst, stride_t *&t_dst,
                                         gaddr_t g_src,  shape_t s_src, stride_t *&t_src, fmt_t fmt);
  GCopyStrideTransposeInst * buildGCopyStrideTransposeInst(gaddr_t g_dst, shape_t s_dst, stride_t *&t_dst,
                          gaddr_t g_src,  shape_t s_src, stride_t *&t_src, bool transpose,  fmt_t fmt);

  AddInst * buildAddInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, ctrl_t c);
  SubInst * buildSubInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, ctrl_t c);
  MulInst * buildMulInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, ctrl_t c);
  DivInst * buildDivInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, ctrl_t c);
  SumInst * buildSumInst(tensor_lmem *r, tensor_lmem *SRC, ctrl_t c);

  AddStrideInst * buildAddStrideInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS,
                                            stride_t *r_s, stride_t *lhs_s, stride_t *rhs_s, ctrl_t c);
  SubStrideInst * buildSubStrideInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS,
                                            stride_t *r_s, stride_t *lhs_s, stride_t *rhs_s, ctrl_t c);
  MulStrideInst * buildMulStrideInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS,
                                            stride_t *r_s, stride_t *lhs_s, stride_t *rhs_s, ctrl_t c);
  DivStrideInst * buildDivStrideInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS,
                                            stride_t *r_s, stride_t *lhs_s, stride_t *rhs_s, ctrl_t c);

  MaxInst * buildMaxInst(tensor_lmem * r, tensor_lmem *LHS, tensor_lmem *RHS);
  MacInst * buildMacInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS, tensor_lmem *Bias, ctrl_t c);
  XaInst * buildXaInst(tensor_lmem *r, tensor_lmem * X, float A);
  MatrixMacInst * buildMatrixMacInst(tensor_lmem *r, tensor_lmem *LHS, tensor_lmem *RHS,
                                            tensor_lmem *Bias, ctrl_t c);
  CmpInst * buildCmpInst(tensor_lmem *r_ab, tensor_lmem *r_cd, tensor_lmem *a,
                              tensor_lmem *b, tensor_lmem *c, tensor_lmem *d);
  SfuInst * buildSfuInst(tensor_lmem * r, tensor_lmem *LHS, SFU_PARAM_T param);
  ArithInst * buildArithInst(tensor_lmem * r, tensor_lmem * LHS,
                             tensor_lmem * RHS, Arith_PARAM_T param);
  ImgSumInst * buildImgSumInst(tensor_lmem * r, tensor_lmem * lhs, ctrl_t c);
  CpuInst * buildCpuInst(const char* op_name, char* payload, size_t size);
};

}

#endif

