/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_BUILDER_H_
#define _ONNX_BUILDER_H_

#include <bmnet/builder/Builder.hpp>
#include <bmnet/frontend/onnx/Module.h>

namespace bmnet {

template <typename Dtype>
class OnnxBuilder : public Builder<Dtype> {
public:
  OnnxBuilder(CHIP_VER ver, const char *model_path);

  OnnxBuilder(CHIP_VER ver, const std::string &model_str);

  ~OnnxBuilder() override;

  void addCustomizedLayer(Layer *layer);

  std::string get_default_input_tensor() override;

  Module &getOnnxModule() { return m_onnxModule; }

private:
  void runFrontend(int n, int c, int h, int w) override;

  size_t input_n, input_c, input_h, input_w;

  Module m_onnxModule;
};

}

#endif /* _ONNX_BUILDER_H_ */
