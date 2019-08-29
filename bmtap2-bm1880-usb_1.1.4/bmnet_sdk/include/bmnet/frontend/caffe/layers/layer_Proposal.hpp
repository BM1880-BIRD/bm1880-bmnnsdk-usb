/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_PROPOSAL_H_
#define _CAFFE_LAYER_PROPOSAL_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CustomizedCaffeLayer.hpp>

namespace bmnet {

class ProposalLayer : public CaffeLayer {
 public:
  explicit ProposalLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~ProposalLayer() override = default;

  std::string layer_name() override { return std::string("Proposal"); }

  void dump() override {}
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
};

}  // namespace bmnet
#endif
