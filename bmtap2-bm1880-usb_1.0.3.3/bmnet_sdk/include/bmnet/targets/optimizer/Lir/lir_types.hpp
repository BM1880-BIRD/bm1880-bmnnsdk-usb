
/* Copyright Bitmain Technologies Inc.
* Written by:
*   Mingkang Qin <mingkang.qin@bitmain.com>
* Created Time: 2018-05-11 14:27
*/
#ifndef _LIR_TYPES_HPP_
#define _LIR_TYPES_HPP_

#include <bmnet/targets/optimizer/Lir/lir_traits.hpp>
#include <glog/logging.h>

namespace bmnet{

typedef enum reg_type{
  REG_LOCAL,
  REG_GLOBAL,
  REG_CONST
}REG_TYPE;

// <start, len>
using REG_RANGE = std::pair<uint32_t, uint32_t>;
// <start, end>
using REG_SCOPE = std::pair<uint32_t, uint32_t>;
using SPLIT_RANGE = std::pair<uint32_t, uint32_t>;
using LIVE_RANGE = std::pair<uint32_t, uint32_t>;

#define UNDEFINED_REG (-1)
#define L_SIZE (256 * 1024)
enum class ElemType : unsigned char {
  FloatTy,
  Int8QTy,
  Int32QTy,
  IndexTy,
};

struct Type final {
  size_t sizes_[max_tensor_dimensions] = {1,};
  size_t num_sizes_;
  ElemType elm_type_;
  bool aligned_;
  tl_type tl_type_;
  size_t reserved_;
  // memory usage in local or global memory
  size_t mem_usage_;
  size_t total_bytes_;

  void initDims(shape_t shape) {
    if(shape.dim >= 1)
      sizes_[0] = (shape.w == 0) ? 1 : shape.w;
    if(shape.dim >= 2)
      sizes_[1] = (shape.h == 0) ? 1 : shape.h;
    if(shape.dim >= 3)
      sizes_[2] = (shape.c == 0) ? 1 : shape.c;
    if(shape.dim >= 4)
      sizes_[3] = (shape.n == 0) ? 1 : shape.n;

    num_sizes_ = shape.dim;
  }
  ElemType initElmFmt(fmt_t fmt){
    switch(fmt){
      case FMT_F32:
        return ElemType::FloatTy;
      case FMT_I8:
        return ElemType::Int8QTy;
      assert(0);
    }
  }
public:

  Type(){}
  void init(tensor_lmem * t_info){
    assert(t_info->fmt == 0);
    initDims(t_info->shape);
    elm_type_ = initElmFmt(t_info->fmt);
    aligned_ = t_info->aligned;
    reserved_ = t_info->reserved_size;
    mem_usage_ = bmk1682_tl_size(t_info);
    total_bytes_ = sizes_[3] * sizes_[2] * sizes_[1] * sizes_[0] * getElmTypeSize();
  }

  void init(tensor_lmem * t_info, bool is_gm){
    initDims(t_info->shape);
    elm_type_ = initElmFmt(t_info->fmt);
    if(is_gm){
      mem_usage_ = sizes_[3] * sizes_[2] * sizes_[1] * sizes_[0] * getElmTypeSize();
    }else{
      mem_usage_ = bmk1682_tl_size(t_info);
    }
    total_bytes_ = sizes_[3] * sizes_[2] * sizes_[1] * sizes_[0] * getElmTypeSize();
  }

  void init(tensor_lmem * t_info, bool is_gm, stride_t & st){
    initDims(t_info->shape);
    elm_type_ = initElmFmt(t_info->fmt);
    if(is_gm){
      switch(num_sizes_){
        case 1:
          mem_usage_ = sizes_[0] * st.w;
          break;
        case 2:
          mem_usage_ = sizes_[1] * st.h;
          break;
        case 3:
          mem_usage_ = sizes_[2] * st.c;
          break;
        case 4:
          mem_usage_ = sizes_[3] * st.n;
          break;
      }
      mem_usage_ *= getElmTypeSize();
      VLOG(4) << "size: " << sizes_[3] << " " << sizes_[2] << " " << sizes_[1] << " " <<sizes_[0] << std::endl;
      total_bytes_ = sizes_[3] * sizes_[2] * sizes_[1] * sizes_[0] * getElmTypeSize();
    }
  }

 void init(shape_t shape, fmt_t fmt){
   initDims(shape);
   elm_type_ = initElmFmt(fmt);
   mem_usage_ = sizes_[3] * sizes_[2] * sizes_[1] * sizes_[0] * getElmTypeSize();
   total_bytes_ = sizes_[3] * sizes_[2] * sizes_[1] * sizes_[0] * getElmTypeSize();
 }

  void init(shape_t shape, fmt_t fmt, stride_t *st){
    initDims(shape);
    elm_type_ = initElmFmt(fmt);
    switch(num_sizes_){
      case 1:
        mem_usage_ = sizes_[0] * st->w;
        break;
      case 2:
        mem_usage_ = sizes_[1] * st->h;
        break;
      case 3:
        mem_usage_ = sizes_[2] * st->c;
        break;
      case 4:
        mem_usage_ = sizes_[3] * st->n;
        break;
    }
    mem_usage_ *= getElmTypeSize();
    VLOG(4) << "size: " << sizes_[3] << " " << sizes_[2] << " " << sizes_[1] << " " <<sizes_[0] << std::endl;
    total_bytes_ = sizes_[3] * sizes_[2] * sizes_[1] * sizes_[0] * getElmTypeSize();
 }

  int getElmTypeSize(){
    return (elm_type_ == ElemType::FloatTy) ? 4 : 1;
  }

  size_t getMemUsage(){
    //VLOG(4) << "size: " << mem_usage_ << " reserved: "
    //          << reserved_ << std::endl;
    return mem_usage_ ;//+ reserved_;
  }

  // total bytes only related to its shape and data type
  size_t getTotalBytes(){
    return total_bytes_;
  }
};

using TypeRef = Type *;

class Typed{
private:
  Type Ty_;
public:
  Typed(){}
  Typed(tensor_lmem * t_info){
    Ty_.init(t_info);
  }
  Typed(tensor_lmem * t_info, bool is_gm){
    Ty_.init(t_info, is_gm);
  }

  Typed(tensor_lmem * t_info, bool is_gm, stride_t & st){
    Ty_.init(t_info, is_gm, st);
  }

  Typed(shape_t shape, fmt_t fmt, stride_t * st){
    if (st == NULL)
      Ty_.init(shape, fmt);
    else
      Ty_.init(shape, fmt, st);
  }

  TypeRef getTyped() {return &Ty_;}
  uint32_t getMemUsage() { return Ty_.getMemUsage();}
  uint32_t getTotalBytes() { return Ty_.getTotalBytes();}
};


}

#endif
