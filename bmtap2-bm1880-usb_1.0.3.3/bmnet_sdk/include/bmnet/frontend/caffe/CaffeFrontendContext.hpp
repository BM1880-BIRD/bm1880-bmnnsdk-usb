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

#include <bmnet/bmnet_caffe.pb.h>
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
  CaffeFrontendContext(const char *deploy_proto, const char *caffemodel,
                       bool enable_dequantized = false);
  explicit CaffeFrontendContext(const char *deploy_proto)
      : CaffeFrontendContext(deploy_proto, nullptr) {
    setDataTypeSize(sizeof(Dtype));
  }

  ~CaffeFrontendContext() override;

  caffe::NetParameter *extract(std::vector<Dtype> *out_weight);

  caffe::NetParameter *extract();

  caffe::NetParameter *netparam();

  CaffeLayer *findLayer(std::string &name);

  NetParameter *convert(void *orig_net, TensorShape *input_shape) override;

  void registerCustomizedLayer(void *layer) override;

 private:
  const char *deploy_proto_;
  const char *caffemodel_;
  CaffeNetParser *parser_;
};

}  // namespace bmnet

#endif /* _CAFFE_FRONTEND_CONTEXT_H_ */
