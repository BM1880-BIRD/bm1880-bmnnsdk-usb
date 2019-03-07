
/* Copyright Bitmain Technologies Inc.
* Written by:
*   Mingkang Qin <mingkang.qin@bitmain.com>
* Created Time: 2018-05-11 14:27
*/

#ifndef _LIR_FUNCTION_HPP_
#define _LIR_FUNCTION_HPP_

#include <bmnet/targets/optimizer/Lir/lir_insts.hpp>
#include <bmnet/bmnet.pb.h>

namespace bmnet {

typedef BlobShape TensorShape;

typedef enum NET_NAME{
  RESNET_50,
  VGG_19,
  GOOGLENET,
  MOBILENET,
  DARKNET_PN11,
  NOT_SUPPORTED,
}NET_NAME_;

using InstrItor = LirInstList::iterator;

class LirCodegen;
class BackendContext;
class PassManager;
class LirFunction : public Named{
  NET_NAME_ netName_;
  shape_t netShape_;
  LirInstList instrs_;
  InstructionNumbering *IN_;
  LirCodegen * cg_;
  BackendContext *ctx_;
  PassManager * passManager_;
public:
  LirFunction(std::string     name, BackendContext * ctx);
  ~LirFunction();

  BackendContext *getBackendContext();

  void pushInstr(LirInst * lirInst){
    instrs_.push_back(lirInst);
  }
  void setNetName();
  NET_NAME_ getNetName() { return netName_;}
  void setNetShape();
  shape_t getNetShape() { return netShape_;}
  LirInstList & getInstrs() { return instrs_; }
  InstrItor getInstrIterator(LirInst * lirInst);
  InstructionNumbering * getIN();
  size_t getInstCount() {return IN_->getInstrCount();}

  // instruction related function
  InstrItor insertPStartBefore(InstrItor it);
  InstrItor insertPEndBefore(InstrItor it);
  LirInst* preInst(LirInst *inst);
  LirInst* nextInst(LirInst *inst);
  InstrIterator preInst(InstrIterator instIt);
  InstrIterator nextInst(InstrIterator instIt);
  void removeInst(LirInst *inst);
  InstrItor removeInst(InstrItor it);
  InstrItor insertInstBefore(LirInst * insert_inst, LirInst * inst);
  void moveInstBefore(LirInst *a , LirInst * b);


  bool isOverLapedRange(REG_RANGE range0, REG_RANGE range1);
  bool inline is_seq_dma(IN InstrItor cur);
  std::vector<REG_RANGE> inline __is_overlape(
        IN InstrItor c,
        IN REG_TYPE  t
        );
  bool inline _is_overlape(
        IN InstrItor a,
        IN InstrItor b,
        IN REG_TYPE  t
        );
  bool inline is_l_overlape(IN InstrItor a, IN InstrItor b);
  bool inline is_g_overlape(IN InstrItor a, IN InstrItor b);
  vector<InstrItor> _isSeqMacConv(
        IN InstrItor start,
        IN InstrItor end,
        IN Kinded::Kind kind,
        OUT vector<InstrItor> & seq
        );

  void _move(
        IN InstrItor s,
        IN InstrItor d
        );
  bool _rerange(
        IN InstrItor ld,
        IN InstrItor start,
        IN InstrItor end
        );

  int _find_lmem(
        IN InstrItor start,
        IN InstrItor end,
        IN int length,
        OUT set<std::pair<int, int> >& r
        );
  void _get_parallel(
      IN InstrItor e,
      IN InstrItor *pstart,
      IN InstrItor *pend
      );

  // optimizer related function
  void peekLdInst();

  // base function
  void compileLir(BackendContext * ctx);
  void init(BackendContext * ctx);
  void dumpLir();
  void instNumbering();


  // code generation
  void lirCodegen();
};

}


#endif
