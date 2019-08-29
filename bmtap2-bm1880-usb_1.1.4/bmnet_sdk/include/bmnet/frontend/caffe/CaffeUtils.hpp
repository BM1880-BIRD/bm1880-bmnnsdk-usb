/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_UTILS_HPP_
#define _CAFFE_UTILS_HPP_

#include <string>

#include <bmnet/bmnet.pb.h>
#include <bmnet/common_calibration.pb.h>
#include <caffe.pb.h>

namespace bmnet {
namespace caffe {

using std::string;

// Copy NetParameters with SplitLayers added to replace any shared bottom
// blobs with unique bottom blobs provided by the SplitLayer.
void InsertSplits(const ::caffe::NetParameter &param, ::caffe::NetParameter *param_split,
                  NetCalibrationParameter *calib_param);

// Check for deprecations and upgrade the NetParameter as needed.
bool UpgradeNetAsNeeded(::caffe::NetParameter *param);

void fixup_network(::caffe::NetParameter *param, NetCalibrationParameter *calib_param);

template <typename Dtype>
::caffe::NetParameter *extract_caffemodel(const int chip_ver, const std::string &deploy_proto,
                                          const char *caffemodel, const char *in_ctable,
                                          std::vector<Dtype> *out_weight,
                                          NetCalibrationParameter *net_param);
}  // namespace caffe
}  // namespace bmnet

#endif  // _CAFFE_UTILS_HPP_
