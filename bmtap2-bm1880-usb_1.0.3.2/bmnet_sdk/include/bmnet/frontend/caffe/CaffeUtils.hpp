/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_UTILS_HPP_
#define _CAFFE_UTILS_HPP_

#include <string>

#include <bmnet/bmnet.pb.h>
#include <bmnet/bmnet_caffe.pb.h>

namespace bmnet {
namespace caffe {

using std::string;

// Copy NetParameters with SplitLayers added to replace any shared bottom
// blobs with unique bottom blobs provided by the SplitLayer.
void InsertSplits(const NetParameter &param, NetParameter *param_split);

// Check for deprecations and upgrade the NetParameter as needed.
bool UpgradeNetAsNeeded(const string &param_file, NetParameter *param);

void fixup_network(NetParameter *param);

NetParameter *netparam_prototxt(const char *deploy_proto);

NetParameter *extract_caffemodel(const char *deploy_proto, const char *caffemodel,
                                 std::vector<float> *out_weight);

NetParameter *extract_caffemodel(const char *deploy_proto, const char *caffemodel,
                                 std::vector<int8_t> *out_weight);
}  // namespace caffe
}  // namespace bmnet

#endif  // _CAFFE_UTILS_HPP_
