/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_BUILDER_H_
#define _CAFFE_BUILDER_H_

#include <bmnet/builder/Builder.hpp>
#include <caffe.pb.h>

class NetParameter;

namespace bmnet {

template <typename Dtype>
class CaffeBuilder : public Builder<Dtype> {
public:
  explicit CaffeBuilder(CHIP_VER ver,
               const char *deploy_proto,
               const char *caffemodel,
               const char *weight_bin,
               const char *in_ctable,
               const char *out_ctable,
               bool enable_dequantized);

  explicit CaffeBuilder(CHIP_VER ver,
               const std::string& deploy_proto,
               const char *caffemodel,
               const char *weight_bin,
               const char *in_ctable,
               const char *out_ctable,
               bool enable_dequantized);

  explicit CaffeBuilder(CHIP_VER ver,
               const char *deploy_proto,
               const char *caffemodel,
               const char *weight_bin);

  explicit CaffeBuilder(CHIP_VER ver,
               const char *bmnet_proto,
               const char *weight_bin);

  ~CaffeBuilder() override;

  void addCustomizedLayer(Layer *layer);

private:
  void createBuilder(CHIP_VER ver,
                     const std::string& proto,
                     const char*caffemodel,
                     const char *in_ctable,
                     const char *weight_bin,
                     bool enable_dequantized);
  void updateWeight(const ::caffe::NetParameter *net,
                    std::vector<Dtype> *weight);
  void runFrontend(std::vector<TensorShape> nchw) override;
  NetCalibrationParameter* getMutableNetCalibrationParameter();
  ::caffe::NetParameter *base_net_;
};

}

#endif /* _CAFFE_BUILDER_H_ */
