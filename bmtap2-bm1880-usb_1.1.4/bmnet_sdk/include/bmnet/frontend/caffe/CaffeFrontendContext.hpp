/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_FRONTEND_CONTEXT_H_
#define _CAFFE_FRONTEND_CONTEXT_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <bmnet/calibration.pb.h>
#include <caffe.pb.h>
#include <bmnet/frontend/FrontendContext.hpp>
#include <bmnet/frontend/Layer.hpp>
#include <bmnet/frontend/caffe/CaffeNetParser.hpp>

namespace bmnet {

class CaffeLayer;
class CaffeNetParser;

/// Compile Caffe model prototxt file into a bmnet prototxt file.
template <typename Dtype>
class CaffeFrontendContext : public FrontendContext {
 public:
  CaffeFrontendContext(const int chip_ver, const std::string &deploy_proto, const char *caffemodel,
                       const char *in_ctable, bool enable_dequantized = false);

  ~CaffeFrontendContext() override;

  ::caffe::NetParameter *extract(std::vector<Dtype> *out_weight);

  ::caffe::NetParameter *extract();

  CaffeLayer *findLayer(std::string &name);

  NetParameter *convert(void *orig_net, std::vector<TensorShape> &input_shapes) override;

  void registerCustomizedLayer(void *layer) override;

  NetCalibrationParameter *getMutableNetCalibrationParameter();

 private:
  const int chip_ver_;
  const std::string deploy_proto_;
  const char *caffemodel_;
  const char *in_ctable_;
  CaffeNetParser *parser_;
  NetCalibrationParameter m_netCalibrationParameter;
};

}  // namespace bmnet

#endif /* _CAFFE_FRONTEND_CONTEXT_H_ */
