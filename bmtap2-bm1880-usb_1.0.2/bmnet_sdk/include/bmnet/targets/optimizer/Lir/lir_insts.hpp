/* Copyright Bitmain Technologies Inc.
* Written by:
*   Mingkang Qin <mingkang.qin@bitmain.com>
* Created Time: 2018-05-10 14:27
*/

/*
 The purpose of this file is to get the low level instrutions of net graph and
 do low level optimizations. The low level instructions can refer to the tl instructions
 in bmkernel for simplify.
*/
#ifndef _LIR_INSTS_HPP_
#define _LIR_INSTS_HPP_

#include <vector>
#include <set>
#include <list>
#include <string>
#include <assert.h>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <map>
#include <bmkernel/bm168x/bmkernel_1682.h>
#include <bmnet/targets/optimizer/Lir/lir_types.hpp>

using namespace std;

namespace bmnet{

class Value;

enum class OperandKind : unsigned char {
  In,
  InOut,
  Out,
};

// operand related macro
using Operand = std::pair<Value *, OperandKind>;
#define OP_VALUE(OP) ((OP).first)
#define OP_REG_NO(OP) ((OP).first->getRegNo())
#define OP_REG_RANGE(OP) (OP.first->getRegRange())
#define OP_REG_TYPE(OP) (OP.first->getRegType())
#define OP_REG_RANGE_START(OP) ((OP_REG_RANGE(OP)).first)
#define OP_REG_RANGE_LENGTH(OP) ((OP_REG_RANGE(OP)).second)
#define OP_KIND(OP) (OP.second)
#define MAX_REG_NO (Value::global_reg_no)


// Instruction Numbering related macro
#define GET_SN(__i)(F_->getIN()->getInstrNumber(__i))
#define GET_INST_IT(k) (F_->getIN()->getInstr(k))

#define IS_GLOBAL_OPERAND(op) (OP_REG_TYPE(op) == REG_GLOBAL)
// Instruction related macro
#define IN
#define OUT
#define IS_OVERLAP(__i, __j ) (is_g_overlape(__j, __j) || is_l_overlape(__i, __j))

// Instruction Type related macro
#define IS_FAKE_INST(inst) ((inst)->getKind() == Kinded::Kind::FakeParallelStartInstKind || \
                            (inst)->getKind() == Kinded::Kind::FakeParallelEndInstKind )
#define IS_MAC(__i) \
    ((__i)->getKind() == Kinded::Kind::MacInstKind)
#define IS_MAX(__i) \
    ((__i)->getKind() == Kinded::Kind::MaxInstKind)
#define IS_ADD(__i) \
    ((__i)->getKind() == Kinded::Kind::AddInstKind)
#define IS_GDMA(__i) \
    ((__i)->getKind() == Kinded::Kind::LoadStrideInstKind || \
     (__i)->getKind() == Kinded::Kind::StoreStrideInstKind || \
     (__i)->getKind() == Kinded::Kind::StoreInstKind || \
     (__i)->getKind() == Kinded::Kind::LoadInstKind)
#define IS_STORE(__i) \
     ((__i)->getKind() == Kinded::Kind::StoreStrideInstKind || \
      (__i)->getKind() == Kinded::Kind::StoreInstKind)
#define IS_LOAD(__i) \
     ((__i)->getKind() == Kinded::Kind::LoadStrideInstKind || \
      (__i)->getKind() == Kinded::Kind::LoadInstKind)
#define IS_CALC(__i) \
     (!IS_DMA(__i))
#define IS_CONV(__i) \
     ((__i)->getKind() == Kinded::Kind::ConvolutionInstKind)
#define IS_PSTART(__i) \
    ((__i)->getKind() == Kinded::Kind::FakeParallelStartInstKind)
#define IS_PEND(__i) \
    ((__i)->getKind() == Kinded::Kind::FakeParallelEndInstKind)
#define IS_BOUND(__i, __d) \
    ((__i)->getKind() == (__d == SEARCH_FORWARD ? \
    Kinded::Kind::FakeParallelEndInstKind :              \
    Kinded::Kind::FakeParallelStartInstKind))

#define SEARCH_FORWARD  (1)
#define SEARCH_BACKWARD (-1)

class Value : public Named,
              public Typed{
public:
  static size_t global_reg_no;
  Value(std:: string &name): Named(name) { xshape_no_ = UNDEFINED_REG; }
  Value(std::string name, tensor_lmem * t_info): Named(name), Typed(t_info){
    reg_no_ = global_reg_no;
    global_reg_no++;
    if(t_info->type == TL_TYPE_CONSTANT){
      reg_type_ = REG_CONST;
      memcpy(&tensor_info_, t_info, sizeof(tensor_lmem));
      const_value_ = tl_constant(t_info).fp32_val;
    }else{
      reg_type_ = REG_LOCAL;
      memcpy(&tensor_info_, t_info, sizeof(tensor_lmem));
      regRange_.first = tl_address(t_info);
      regRange_.second = getMemUsage();
    }
    xshape_no_ = UNDEFINED_REG;
  }

  // for load inst
  Value(std::string name, tensor_lmem * t_info, size_t gaddr, stride_t & stride):
         Named(name), Typed(t_info, true, stride){
    reg_no_ = global_reg_no;
    global_reg_no++;

    reg_type_ = REG_GLOBAL;
    regRange_.first = gaddr;
    regRange_.second = getMemUsage();

    xshape_no_ = UNDEFINED_REG;
  }

  Value(std::string name, tensor_lmem * t_info, size_t gaddr):
         Named(name), Typed(t_info, true){
    reg_no_ = global_reg_no;
    global_reg_no++;

    reg_type_ = REG_GLOBAL;
    regRange_.first = gaddr;
    regRange_.second = getMemUsage();

    xshape_no_ = UNDEFINED_REG;
  }

  Value(std::string name, shape_t shape, fmt_t fmt, size_t gaddr, stride_t* st):
    Named(name), Typed(shape, fmt, st){
    reg_no_ = global_reg_no;
    global_reg_no++;
    reg_type_ = REG_GLOBAL;
    regRange_.first = gaddr;
    regRange_.second = getMemUsage();

    xshape_no_ = UNDEFINED_REG;
  }

  Value(std::string name, float f): Named(name), Typed(){
    reg_type_ = REG_CONST;
    const_value_ = f;
    set_const_tensor(f);
    xshape_no_ = UNDEFINED_REG;
  }
  size_t getRegStartAddr() { return regRange_.first; }
  size_t getRegLength() { return regRange_.second; }
  REG_RANGE getRegRange() { return regRange_; }
  REG_TYPE getRegType() { return reg_type_; }
  size_t getRegNo() { return reg_no_; }
  float getConst(){ return const_value_; }

  void setRegNo(int reg_no) {reg_no_ = reg_no;}
  std::vector<size_t> & getRegs() { return regs_; }
  void setStartAddr(uint32_t startAddr) {
        regRange_.first = startAddr;
        tensor_info_.operand.laddr = startAddr;
  }
  size_t getStartAddr(){ return regRange_.first; }
  size_t getOperandSize() { return regRange_.second; }
  size_t getXsharpNo() {return xshape_no_;}
  void setXsharpNo(int reg_no) {xshape_no_ = reg_no; }
  size_t getXshapeSize() {return xshape_size_; }
  void setXsharpSize(size_t size) { xshape_size_ = size; }
  void setLiveRange(size_t inst_index){      live_range_ = inst_index; }
  size_t getLiveRange(){      return live_range_; }
  void set_const_tensor(float f) {
    shape_t shape = shape_t1(1);
    tensor_info_.type =  TL_TYPE_CONSTANT;
    tensor_info_.shape = shape;
    tensor_info_.operand.const_fp32.fp32_val = f;
    tensor_info_.aligned = false;
    tensor_info_.fmt = FMT_F32;
    tensor_info_.bank_id = 8;
    tensor_info_.reserved_size = 0;
  };

  void addReg(int reg_no) {regs_.push_back(reg_no);}
  tensor_lmem * getTensor() { return &tensor_info_; };
private:
  REG_RANGE regRange_;
  REG_TYPE reg_type_;
  size_t reg_no_;
  size_t xshape_no_;
  size_t xshape_size_;
  std::vector<size_t> regs_;
  float const_value_;
  size_t live_range_;

  // keep tensor info for now, may remove in the future
  tensor_lmem tensor_info_;
};


class LirFunction;
class LirInst : public Value, public Kinded{
public:
  LirInst(LirFunction *F, std::string &name, Kinded::Kind kind)
            :Value(name), F_(F), Kinded(kind), bd_cmd_id(0), gdma_cmd_id(0), ctrl_(0){}
  LirInst(LirFunction *F, std::string &name, Kinded::Kind kind, std::vector<Operand> ops)
            :Value(name), F_(F), Kinded(kind), bd_cmd_id(0), gdma_cmd_id(0), ctrl_(0){
    //std::cout << "Build Inst " << name << " ";
    for(auto &op: ops){
      if(op.first != NULL){
        ops_.push_back(op);
      }
    }
  }

  void pushOperand(Operand op);
  void dumpOperands();
  Operand getOperand(size_t idx);
  Operand & getOperandRef(size_t idx);
  size_t getOperandNum();
  std::vector<Operand> getDsts();
  size_t getDstNum();
  std::vector<Operand> getSrcs();
  Operand getNthDest(int idx);
  Operand getNthSrc(int idx);
  size_t getSrcNum();
  tensor_lmem * getTensorOfDst0();
  tensor_lmem * getTensorOfDst1();
  tensor_lmem * getTensorOfSrc0();
  tensor_lmem * getTensorOfSrc1();
  tensor_lmem * getTensorOfSrc2();
  tensor_lmem * getTensorOfSrc3();

  void setNthOperandRegNo(int reg_no, int op_idx);
  void setNthOperandStartAddr(uint32_t startAddr, int op_idx);
  void setNthOperandLiveRange(size_t inst_index, int op_idx);
  std::string getOpType() {return opType;}
  std::string getOpName() {return opName;}
  void setOpType(std::string type) {opType = type;}
  void setOpName(std::string name) {opName = name;}
  void setCmdId(size_t bd_id, size_t gdma_id){bd_cmd_id = bd_id; gdma_cmd_id = gdma_id;}
  unsigned int getCurNsTime() { return cur_op_ns_;};
  void setCurNsTime(unsigned int c) { cur_op_ns_ = c;};
  size_t getBdCmdId(){return bd_cmd_id;}
  size_t getGdmaCmdId(){return gdma_cmd_id;}
  void setResultAdd(u32 c) { ctrl_ = c&CTRL_RA; }
  bool isResultAdd() { return ctrl_ & CTRL_RA; }
private:
  size_t bd_cmd_id, gdma_cmd_id;
  unsigned int cur_op_ns_; //<! execute time for current operator,  nano seconds
  LirFunction * F_;
  std::vector<Operand> ops_{};
  u32 ctrl_;
  std::string opType;
  std::string opName;
};

using LirInstList = std::list<LirInst *>;
using InstrIterator = LirInstList::iterator;

// help class for instructions
class InstructionNumbering{
  using NumberedInstructionMap = std::vector<InstrIterator>;
  using InstructionNumbersMap = std::unordered_map<LirInst *, size_t>;
  /// Maps the number to an instruction.
  NumberedInstructionMap numToInstr_;
  /// Maps an instruction to its number.
  InstructionNumbersMap instrToNum_;

public:
  InstructionNumbering(LirFunction &M);
  void insertInstr(std::pair<LirInst*, size_t> &instrPair);
  InstrIterator getInstr(size_t instrNumber);
  size_t getInstrNumber(LirInst * lirInst);
  size_t getInstrCount();
};






typedef struct {
  u8 ins_h;
  u8 ins_last_h;
  u8 ins_w;
  u8 ins_last_w;
  u8 dilation_h;
  u8 dilation_w;
  u8 pad_h_top;
  u8 pad_h_bottom;
  u8 pad_w_left;
  u8 pad_w_right;
  u8 stride_h;
  u8 stride_w;
  u16 kstride_n;
  u16 kstride_c;
  u16 kstride_h;
  u8 kernel_h;
  u8 kernel_w;
  bool kernel_flip;
  bool result_add;
}CONV_PARAM_T;



//################# Inst Instruction #########################
class FakeParallelStartInst: public LirInst{
  public:
    FakeParallelStartInst(LirFunction *F, std::string name)
            : LirInst(F, name, Kinded::Kind::FakeParallelStartInstKind){}
};
class FakeParallelEndInst: public LirInst{
  public:
    FakeParallelEndInst(LirFunction *F, std::string name)
            : LirInst(F, name, Kinded::Kind::FakeParallelEndInstKind){}
};

class ConvInst: public LirInst{
private:
  CONV_PARAM_T conv_param_;
public:
  ConvInst(LirFunction * F, std::string name, Value *Dest, Value * Src, Value *Filter, Value *Bias,
                  Value * Relu, CONV_PARAM_T conv_param)
                  : LirInst(F, name, Kinded::Kind::ConvolutionInstKind, {
                    {Dest, OperandKind::Out},
                    {Src, OperandKind::In},
                    {Filter, OperandKind::In},
                    {Bias, OperandKind::In},
                    {Relu, OperandKind::In},
                    }), conv_param_(conv_param)
                  { setResultAdd(conv_param.result_add);}
  CONV_PARAM_T & getParams() { return conv_param_; }
};

typedef struct {
  bool is_avg_pooling;
  int kh;
  int kw;
  u8 ins_h;
  u8 ins_last_h;
  u8 ins_w;
  u8 ins_last_w;
  u8 pad_h_top;
  u8 pad_h_bottom;
  u8 pad_w_left;
  u8 pad_w_right;
  u8 stride_h;
  u8 stride_w;
  float avg_pooling_const;
}POOLING_PARAM_T;

class PoolingInst: public LirInst{
private:
  POOLING_PARAM_T pooling_param_;
public:
  PoolingInst(LirFunction * F, std::string name, Value *Dest, Value * Src, Value * Relu, POOLING_PARAM_T pooling_param)
              : LirInst(F, name, Kinded::Kind::PoolingInstKind, {
              {Dest, OperandKind::Out},
              {Src, OperandKind::In},
              {Relu, OperandKind::In},
              }), pooling_param_(pooling_param){}
  POOLING_PARAM_T & getParams() { return pooling_param_; }
};

typedef struct {
  bool b_right_shift;
  size_t step;
}LRN_PARAM_T;

class LrnShiftInst: public LirInst {
private:
LRN_PARAM_T lrn_param_;
public:
  LrnShiftInst(LirFunction * F, std::string name, Value * Dest, Value * Src, LRN_PARAM_T lrn_param)
              : LirInst(F, name, Kinded::Kind::LrnShiftInstKind, {
                {Dest, OperandKind::Out},
                {Src, OperandKind::In},
                }), lrn_param_(lrn_param){}
  LRN_PARAM_T & getParams() { return lrn_param_; }
};

typedef struct {
  stride_t s;
  ctrl_t c;
}DMA_PARAM_T;

class LoadInst: public LirInst{
private:
  DMA_PARAM_T load_param_;
public:
  LoadInst(LirFunction * F, std::string name, Value *Dest, Value * Src, DMA_PARAM_T load_param)
          :LirInst(F, name, Kinded::Kind::LoadInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }), load_param_(load_param){}
  DMA_PARAM_T & getParams() { return load_param_; }
};


class LoadStrideInst: public LirInst{
private:
  DMA_PARAM_T load_param_;
public:
  LoadStrideInst(LirFunction * F, std::string name, Value *Dest, Value * Src, DMA_PARAM_T load_param)
          :LirInst(F, name, Kinded::Kind::LoadStrideInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }), load_param_(load_param){}
  DMA_PARAM_T & getParams() { return load_param_; }
};

class StoreInst: public LirInst{
private:
  DMA_PARAM_T store_param_;
public:
  StoreInst(LirFunction * F, std::string name, Value *Dest, Value * Src, DMA_PARAM_T store_param)
          :LirInst(F, name, Kinded::Kind::StoreInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }), store_param_(store_param){}
  DMA_PARAM_T & getParams() { return store_param_; }
};

class StoreStrideInst: public LirInst{
private:
  DMA_PARAM_T store_param_;
public:
  StoreStrideInst(LirFunction * F, std::string name, Value *Dest, Value * Src, DMA_PARAM_T store_param)
          :LirInst(F, name, Kinded::Kind::StoreStrideInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }), store_param_(store_param){}
  DMA_PARAM_T & getParams() { return store_param_; }
};

typedef struct {
  stride_t st_dst;
  stride_t st_src;
}COPY_STRIDE_PARAM_T;

class CopyStrideInst: public LirInst{
private:
  COPY_STRIDE_PARAM_T param_;
public:
  CopyStrideInst(LirFunction * F, std::string name, Value *Dest, Value * Src,
                  COPY_STRIDE_PARAM_T param)
          :LirInst(F, name, Kinded::Kind::CopyStrideInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }), param_(param){}
  COPY_STRIDE_PARAM_T & getParams() { return param_; }
};

class CopyGdmaInst: public LirInst{
public:
  CopyGdmaInst(LirFunction * F, std::string name, Value *Dest, Value * Src)
          :LirInst(F, name, Kinded::Kind::CopyGdmaInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }){}
};

class TransposeCWInst: public LirInst{
public:
  TransposeCWInst(LirFunction * F, std::string name, Value *Dest, Value * Src)
          :LirInst(F, name, Kinded::Kind::TransposeCWInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }){}
};

typedef struct {
  stride_t t_src;
  stride_t t_dst;
  shape_t s_src;
  shape_t s_dst;
  float val;
  bool transpose;
  fmt_t fmt;
}G_COPY_PARAM_T;

class GCopyInst: public LirInst{
private:
  G_COPY_PARAM_T copy_param_;
public:
  GCopyInst(LirFunction * F, std::string name, Value *Dest, Value * Src, G_COPY_PARAM_T copy_param)
          :LirInst(F, name, Kinded::Kind::GCopyInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }), copy_param_(copy_param){}
  G_COPY_PARAM_T & getParams() { return copy_param_; }
};

class GCopyStrideInst: public LirInst{
private:
  G_COPY_PARAM_T copy_param_;
public:
  GCopyStrideInst(LirFunction * F, std::string name, Value *Dest, Value * Src, G_COPY_PARAM_T copy_param)
          :LirInst(F, name, Kinded::Kind::GCopyStrideInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }), copy_param_(copy_param){}
  G_COPY_PARAM_T & getParams() { return copy_param_; }
};

class GCopyStrideTransposeInst: public LirInst{
private:
  G_COPY_PARAM_T copy_param_;
public:
  GCopyStrideTransposeInst(LirFunction * F, std::string name, Value *Dest, Value * Src, G_COPY_PARAM_T copy_param)
          :LirInst(F, name, Kinded::Kind::GCopyStrideTransposeInstKind, {
          {Dest, OperandKind::Out},
          {Src, OperandKind::In}
          }), copy_param_(copy_param){}
  G_COPY_PARAM_T & getParams() { return copy_param_; }
};

class GFillInst: public LirInst{
private:
  G_COPY_PARAM_T copy_param_;
public:
  GFillInst(LirFunction * F, std::string name, Value *Dest, G_COPY_PARAM_T copy_param)
          :LirInst(F, name, Kinded::Kind::GFillInstKind, {
          {Dest, OperandKind::Out},
          }), copy_param_(copy_param){}
  G_COPY_PARAM_T & getParams() { return copy_param_; }
};

class GFillStrideInst: public LirInst{
private:
  G_COPY_PARAM_T copy_param_;
public:
  GFillStrideInst(LirFunction * F, std::string name, Value *Dest, G_COPY_PARAM_T copy_param)
          :LirInst(F, name, Kinded::Kind::GFillStrideInstKind, {
          {Dest, OperandKind::Out},
          }), copy_param_(copy_param){}
  G_COPY_PARAM_T & getParams() { return copy_param_; }
};


typedef struct {
  ctrl_t c;
}MD_PARAM_T;

class MulInst: public LirInst {
private:
  MD_PARAM_T md_param_;
public:
  MulInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS, MD_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::MulInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_PARAM_T & getParams() { return md_param_; }
};

class DivInst: public LirInst {
private:
  MD_PARAM_T md_param_;
public:
  DivInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS, MD_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::DivInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_PARAM_T & getParams() { return md_param_; }
};

class AddInst: public LirInst {
private:
  MD_PARAM_T md_param_;
public:
  AddInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS, MD_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::AddInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_PARAM_T & getParams() { return md_param_; }
};

class SubInst: public LirInst {
private:
  MD_PARAM_T md_param_;
public:
  SubInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS, MD_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::SubInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_PARAM_T & getParams() { return md_param_; }
};

class SumInst: public LirInst {
  private:
    MD_PARAM_T md_param_;
  public:
    SumInst(LirFunction * F, std::string name, Value *Dest, Value * Src, MD_PARAM_T md_param)
            : LirInst(F, name, Kinded::Kind::SumInstKind, {
            {Dest, OperandKind::Out},
            {Src, OperandKind::In},
            }), md_param_(md_param){setResultAdd(md_param.c);}
    MD_PARAM_T & getParams() {return md_param_;}
};

typedef struct {
  stride_t dst_s;
  stride_t src0_s;
  stride_t src1_s;
  ctrl_t c;
}MD_STRIDE_PARAM_T;

class AddStrideInst: public LirInst {
private:
  MD_STRIDE_PARAM_T md_param_;
public:
  AddStrideInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS,
                     MD_STRIDE_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::AddStrideInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_STRIDE_PARAM_T & getParams() { return md_param_; }
};

class SubStrideInst: public LirInst {
private:
  MD_STRIDE_PARAM_T md_param_;
public:
  SubStrideInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS,
                     MD_STRIDE_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::SubStrideInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_STRIDE_PARAM_T & getParams() { return md_param_; }
};

class MulStrideInst: public LirInst {
private:
  MD_STRIDE_PARAM_T md_param_;
public:
  MulStrideInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS,
                     MD_STRIDE_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::MulStrideInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_STRIDE_PARAM_T & getParams() { return md_param_; }
};

class DivStrideInst: public LirInst {
private:
  MD_STRIDE_PARAM_T md_param_;
public:
  DivStrideInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS,
                     MD_STRIDE_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::DivStrideInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_STRIDE_PARAM_T & getParams() { return md_param_; }
};

class MacInst: public LirInst {
private:
  MD_PARAM_T md_param_;
public:
  MacInst(LirFunction * F, std::string name, Value * Dest,  Value * RHS, Value * LHS,
           Value * Bias, MD_PARAM_T md_param)
          : LirInst(F, name, Kinded::Kind::MacInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          {Bias, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_PARAM_T & getParams() { return md_param_; }
};

class XaInst: public LirInst {
public:
  XaInst(LirFunction * F, std::string name, Value * Dest, Value * x, Value * a)
          : LirInst(F, name, Kinded::Kind::XaInstKind, {
          {Dest, OperandKind::Out},
          {x, OperandKind::In},
          {a, OperandKind::In},
          }){}
};

class MatrixMacInst: public LirInst {
private:
  MD_PARAM_T md_param_;
public:
  MatrixMacInst(LirFunction * F, std::string name, Value * Dest,  Value * RHS,
                     Value * LHS, Value * Bias, MD_PARAM_T md_param)
                     : LirInst(F, name, Kinded::Kind::MatrixMacInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          {Bias, OperandKind::In},
          }), md_param_(md_param){setResultAdd(md_param.c);}
  MD_PARAM_T & getParams() { return md_param_; }
};

class MaxInst: public LirInst {
public:
  MaxInst(LirFunction * F, std::string name, Value * Dest, Value * RHS, Value * LHS)
          : LirInst(F, name, Kinded::Kind::MaxInstKind, {
          {Dest, OperandKind::Out},
          {RHS, OperandKind::In},
          {LHS, OperandKind::In},
          }){}
};


class CmpInst: public LirInst {
public:
  CmpInst(LirFunction * F, std::string name, Value * R_AB, Value * R_CD, Value * A,
             Value *B, Value *C, Value *D)
          : LirInst(F, name, Kinded::Kind::CmpInstKind, {
          {R_AB, OperandKind::Out},
          {R_CD, OperandKind::Out},
          {A, OperandKind::In},
          {B, OperandKind::In},
          {C, OperandKind::In},
          {D, OperandKind::In}
          }){}
};

typedef struct{
  float a;
  int n;
  SFU_OP op;
}SFU_PARAM_T;

class SfuInst: public LirInst {
private:
  SFU_PARAM_T sfu_param_;
public:
  SfuInst(LirFunction * F, std::string name, Value * Dest, Value * Src, SFU_PARAM_T sfu_param)
          : LirInst(F, name, Kinded::Kind::SfuInstKind, {
            {Dest, OperandKind::Out},
            {Src, OperandKind::In}
          }), sfu_param_(sfu_param){}
  SFU_PARAM_T & getParams() { return sfu_param_; }
};

typedef struct{
  TENSOR_OP op;
  ctrl_t c;
}Arith_PARAM_T;

class ArithInst: public LirInst {
private:
  Arith_PARAM_T arith_param_;
public:
  ArithInst(LirFunction * F, std::string name, Value * Dest, Value * LHS, Value * RHS, Arith_PARAM_T arith_param)
          : LirInst(F, name, Kinded::Kind::ArithInstKind, {
            {Dest, OperandKind::Out},
            {LHS, OperandKind::In},
            {RHS, OperandKind::In}
          }), arith_param_(arith_param){}
  Arith_PARAM_T & getParams() { return arith_param_; }
};

class ImgSumInst: public LirInst {
private:
  MD_PARAM_T img_param_;
public:
  ImgSumInst(LirFunction * F, std::string name, Value * Dest, Value * Src, MD_PARAM_T img_param)
                : LirInst(F, name, Kinded::Kind::ImgSumInstKind, {
                  {Dest, OperandKind::Out},
                  {Src, OperandKind::In}
                  }), img_param_(img_param){}
  MD_PARAM_T & getParams() { return img_param_; }
};

typedef struct{
  char * op_name;
  char * payload;
  size_t size;
}CPU_PARAM_T;

class CpuInst: public LirInst {
private:
  CPU_PARAM_T cpu_param_;
public:
  CpuInst(LirFunction * F, std::string name, CPU_PARAM_T cpu_param)
               : LirInst(F, name, Kinded::Kind::CpuInstKind), cpu_param_(cpu_param){}
  CPU_PARAM_T & getParams() {return cpu_param_;}
};
}

#endif
