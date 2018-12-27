/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_BUILDER_H_
#define _CAFFE_BUILDER_H_

#include <bmnet/builder/Builder.hpp>
#include <bmnet/bmnet_caffe.pb.h>

class NetParameter;

namespace bmnet {

template <typename Dtype>
class CaffeBuilder : public Builder<Dtype> {
public:
  CaffeBuilder(CHIP_VER ver,
               const char *modified_proto,
               const char *caffemodel,
               const char *weight_bin,
               const char *in_ctable,
               const char *out_ctable,
               bool enable_dequantized = false);

  CaffeBuilder(CHIP_VER ver,
               const char *modified_proto,
               const char *caffemodel,
               const char *weight_bin);

  ~CaffeBuilder() override;

  void setBaseNetParameter();

  void addCustomizedLayer(Layer *layer);

private:
  void runFrontend(int n, int c, int h, int w) override;

  caffe::NetParameter *base_net_;
};

}

#endif /* _CAFFE_BUILDER_H_ */
