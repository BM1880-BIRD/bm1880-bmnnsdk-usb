/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */

#ifndef CALIBRATION_LIB_H
#define CALIBRATION_LIB_H

#include <caffe2/core/init.h>
#include <caffe2/core/net.h>

#include <bmnet/calibration.pb.h>
#include <bmnet/common_calibration.pb.h>
#include <bmnet/frontend/onnx/Module.h>

namespace bmnet {

using BlobData = std::unordered_map<std::string, std::vector<caffe2::TensorCPU> >;

// Calibration will:
// 1. Run inference via caffe2-backend.
// 2. Calibrate the range of each blobs. (Create Ctable)
class Calibration {
 public:
  Calibration(){};

  void FeedBlob(const std::string pName, caffe2::TensorCPU &pTensor) {
    blobData[pName].emplace_back(pTensor.Clone());
  }

  caffe2::TensorCPU &FetchBlob(const std::string pName, const int32_t pIteration) {
    return blobData[pName][pIteration];
  }

  // For python
  void Profile(ONNX_NAMESPACE::ModelProto &pProto, int pIteration);

  // For C++ (implement in bmnet/test/Calibration_legacy.cpp)
  void Profile(Module *pModule, const char *pDbName, int pIteration);

  void updateThreshold(caffe2::NetDef &pDef, NetCalibrationParameter &netCtableParam,
                       std::unordered_map<std::string, float> &thresholdY);

  void thresholdFold(caffe2::NetDef &pDef, std::unordered_map<std::string, float> &thresholdY);

  void profileModel(int pIteration, caffe2::NetDef &pDef, const std::string &pDataLayer,
                    BlobData &blobData, NetCalibrationParameter &netCtableParam,
                    std::unordered_map<std::string, float> &thresholdY,
                    caffe2::Workspace *pWorkSpace);

 private:
  BlobData blobData;
};

}  // namespace bmnet

#endif  // CALIBRATION_LIB_H
