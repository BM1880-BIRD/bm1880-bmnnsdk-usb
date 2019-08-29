# Custom layer plugin

## How to add a custom plugin


The following ``layer_api.hpp`` is the plugin api for ``bm_builder.bin``.

```
/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#pragma once
#include <bmnet/frontend/Layer.hpp>
#include <bmnet/backend/Instruction.hpp>

#define LAYERAPI_VERSION "1.0.0"

namespace bmnet {
class LayerAPI {
public:
  LayerAPI() {}

  virtual ~LayerAPI() {
    if (onnx_layer) delete onnx_layer;
    if (caffe_layer) delete caffe_layer;
    if (int8_layer_inst) delete int8_layer_inst;
    if (float_layer_inst) delete float_layer_inst;
  }
  virtual void init(FrontendContext *ctx) = 0;
  const std::string getAPIVersion() { return LAYERAPI_VERSION; }
  virtual const std::string layerName() = 0;
  virtual Layer* getCaffeLayer() { return caffe_layer; }
  virtual Layer* getOnnxLayer() { return onnx_layer; }
  virtual Instruction* getInt8Instruction() { return int8_layer_inst; }
  virtual Instruction* getFloatInstruction() { return float_layer_inst; }

  typedef LayerAPI *create_t();
  typedef void destroy_t(LayerAPI *);
protected:
  bmnet::Layer *onnx_layer = nullptr;
  bmnet::Layer *caffe_layer = nullptr;
  bmnet::Instruction *int8_layer_inst = nullptr;
  bmnet::Instruction *float_layer_inst = nullptr;
};
}
```

``bm_builder.bin`` will automatically register the frontend and backend layers according to the target arguments from the given command.

To start writing a plugin, you'll need an entrance point for ``bm_builder.bin``. There are two virtual functions that need to be override. ``init`` is where the instance to be created, and ``layerName`` is the name for this plugin (**Don't mix with the names in frontend and backend!**).

```
  virtual void init(FrontendContext *ctx) = 0;
  ...
  virtual const std::string layerName() = 0;
```

The following file ``relu/Elu.cpp`` is a great example to start:

```
#include <bmnet/builder/plugin/layer_api.hpp>
#include <cmath>

#include "layer_Elu.hpp"
#include "op_Elu.hpp"
#include "tg_elu.hpp"

namespace bmnet {
class Elu : public LayerAPI {
public:
  Elu() : LayerAPI() {

  }

  void init(FrontendContext *ctx) override {
    onnx_layer = new EluOpPlugin(ctx);
    caffe_layer = new EluLayerPlugin();
    int8_layer_inst = new TGEluPluginFixedInst();
    float_layer_inst = new TGEluPluginInst();
  }
  const std::string layerName() override { return "Elu"; }
};
}


// the class factories

extern "C" bmnet::LayerAPI* create() {
  return new bmnet::Elu();
}

extern "C" void destroy(bmnet::LayerAPI* p) {
  delete p;
}
```

### bmnet IR

This is the custom parameter of bmnet IR. Any values can be carried to backend with int array ``i32_param`` and float array ``f32_param``.

```
message TGCustomizedParameter {
  optional DependInfo dep_info = 999;
  optional string sub_type = 1;
  repeated int32 i32_param = 2;
  repeated float f32_param = 3;
}
```

### Caffe frontend

The example code for caffe frontend can be found in ``relu/layer_Elu.hpp`` and ``relu/layer_Elu.cpp``. The following functions need to be override to work properly.

```
  std::string layer_name() {return std::string("ELU"); }
  void dump();
  void codegen(TensorOp *op);
```

The return value for function ``layer_name`` must match the name in the Caffe prototxt. ``dump`` is a function for printing debugging messages. ``codegen`` is the function that pass Caffe IR to bmnet IR.

The following is an example layer from lenet. To make sure ``bm_builder.bin`` gets the layer property from prototxt. You'll need to write the information in the ``value`` field under message ``custom``. We recommended to write in the format of YAML.

```
layer {
  name: "customized2",
  type: "ELU",
  bottom: "ip2",
  top: "customized2",
  custom {
    value: "{alpha: 0.1}"
  }
}
```

In ``relu/layer_Elu.cpp`` you can pass the value from prototxt to bmnet IR. Caffe uses protobuf to store its model data. To get the custom string from you custom layer, you can call the getter function ``layer_.custom().value()``.

```
  const std::string &value = layer_.custom().value();
  YAML::Node yaml_data = YAML::Load(value);
  float alpha = yaml_data["alpha"].as<float>();
  ...
  TGCustomizedParameter* out_param = op->mutable_tg_customized_param();
  out_param->add_f32_param(alpha);
```

### Onnx frontend

Onnx checks if the custom layer is registered properly in Onnx runtime library. Which means you can only add a custom layer that has not been implemented in ``bm_builder.bin`` but exists in Onnx.

These functions have to be override in order to work properly. The returned layer name has to be the name stored in your Onnx model.

```
  std::string layer_name() override { return std::string("Elu"); }

  void dump() override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
```

Function ``makeOp`` is a wrapper for ``bm_builder.bin`` to create the instance of you custom layer.

```
  OnnxOperator *EluOpPlugin::makeOp(const ONNX_NAMESPACE::Node *node) {
    return new EluOpPlugin(ctx_, node);
  }
```

Custom Onnx frontend has the property of ``tg_customized``. This property will not set output tensor ``data_type_size`` for you. Make sure to setup your op type at the beginning of the ``codegen`` function if you want to set output data type size as input data type size.

```
void EluOpPlugin::codegen(TensorOp *op) {
  // Setup your op type
  op->set_type("tg_elu");
```

Onnx uses symbol search to get the stored parameters in models. You can use ``hasAttribute`` to check if the symbol exists, then retrieve your data using Onnx casting functions.

```
  if (pNode->hasAttribute(ONNX_NAMESPACE::Symbol("alpha"))) {
   // the "f" here means cast to float.
   alpha = pNode->f(ONNX_NAMESPACE::Symbol("alpha"));
  }
```

Cause the calibration tool for Onnx only calculates the input and output threshold. If your custom layer contains some data that need to be quantized, you'll have to override the following function to quantize your data. This example can be found in ``leakyrelu/op_LeakyRelu.cpp``.

```
void LeakyReluOpPlugin::quantize(qWeight_t *qWeight, qBias_t *qBias, NetCTable_t *NetCTable)
```

The rest is the same as adding a Caffe frontend.

### Adding backend

Our custom backend supports both CPU ops and TPU ops. TPU ops have some limitations due to different hardware. For example, "bm1880" only accepts ``int8_t`` TPU ops.

This is an example ``TGEluPluginFixedInst`` class for "bm1880" platforms.

```
class TGEluPluginFixedInst : public CustomizedTensorFixedInst {
public:
  TGEluPluginFixedInst() : CustomizedTensorFixedInst() {}
  ~TGEluPluginFixedInst() {}

  std::string inst_name() {return std::string("tg_elu"); }

  void dump();
  void compute();

};
```

These functions have to be override in order to work properly. The returned instance name has to be the name you defined in Caffe or Onnx frontend.

```
  std::string inst_name() {return std::string("tg_elu"); }

  void dump();
  void compute();
```

To add a TPU op for your custom layer, implement your algorithms with bmkernel functions in ``compute``.

#### Adding a cpu layer

To add a CPU plugin override the ``compute`` function and call ``add_cpu_op``. The string passed to the ``add_cpu_op`` function has to be the same as the file name of your CPU op library. Make sure to pass the quantize threshold to CPU op if you want to process you int8 data with float algorithms.

```
void TGEluPluginFixedInst::compute() {
  const TGCustomizedParameter& param = op_.tg_customized_param();
  if (op_.input_shape(0).data_type_size() == sizeof(int8_t)) {
    op_.add_threshold_x(m_inputCalibrationParameter[0].blob_param(0).threshold_y());
  }
  if (op_.output_shape(0).data_type_size() == sizeof(int8_t)) {
    op_.add_threshold_y(m_calibrationParameter.blob_param(0).threshold_y());
  }
  // If your cpu plugin is named as "ELU.so"
  add_cpu_op(ctx_, "ELU", op_);
}
```

**CPU plugin**

To create a new custom cpu plugin, new a cpp file with the following format. Override the function ``run`` with your algorithm. Make sure you register your CPU op by calling ``REGISTER_CPU_OP``. The following example also shows how to process int8 data with float algorithms.

```
namespace bmnet {

class EluOp: public CpuOp {

public:

  void run() {

    assert(op_.type() == "ELU");
    const TensorShape& input_shape = op_.input_shape(0);
    int count = GetTensorCount(input_shape);

    char *input_data = NULL;
    char *output_data = NULL;
    float *bottom_data = NULL;
    float *top_data = NULL;
    // Dequantize to float if needed
    if (op_.threshold_x_size() > 0) {
      #if DEBUG
      std::cout << "[Elu]thx:" << op_.threshold_x(0)<<std::endl;
      #endif
      input_data = reinterpret_cast<char*>(op_.global_input(0));
      bottom_data = (float*)malloc(sizeof(float) * count);
      for (int i = 0; i < count; ++i) {
        bottom_data[i] = input_data[i] * op_.threshold_x(0) /128.0;
        #if DEBUG
        std::cout << "bottom:" << i<<"="<<bottom_data[i] << std::endl;
        #endif
      }
    }
    else {
      bottom_data = reinterpret_cast<float*>(op_.global_input(0));
    }
    // quantize to int8 if needed
    if (op_.threshold_y_size() > 0) {
      #if DEBUG
      std::cout << "[Elu]thy:" << op_.threshold_y(0)<<std::endl;
      #endif
      output_data = reinterpret_cast<char*>(op_.global_output(0));
      top_data = (float*)malloc(sizeof(float) * count);
    }
    else {
      top_data = reinterpret_cast<float*>(op_.global_output(0));
    }

    float alpha = op_.tg_customized_param().f32_param(0);

    #if DEBUG
    std::cout << " [elu run] bottom:" << bottom_data
              << " top: " << top_data
              << " count: " << count
              << " alpha:" << alpha
              << std::endl;
    #endif

    for (int i = 0; i < count; ++i) {
      top_data[i] = std::max(bottom_data[i], (float)0)
          + alpha * (exp(std::min(bottom_data[i], (float)0)) - 1);
    }

    for (int i = 0; i < count; ++i) {
      if (op_.threshold_y_size() > 0) {
        int fixed_data = (int)(top_data[i] * 128  / op_.threshold_y(0) + 0.5);
        output_data[i] = (fixed_data < -128) ? -128 : ((fixed_data > 127) ? 127 : fixed_data);
        #if DEBUG
        std::cout << " output: " <<i<<"="<<top_data[i]<<","<<(int)output_data[i] << std::endl;
        #endif
      }
      else {
        #if DEBUG
        std::cout << " output: " <<i<<"="<<top_data[i]<< std::endl;
        #endif
      }
    }
    if (op_.threshold_y_size() > 0) {
      free(top_data);
    }
    if (op_.threshold_x_size() > 0) {
      free(bottom_data);
    }

    #if DEBUG
    std::cout << "cpu_op: elu_op done" << std::endl;
    #endif
  }

};

}
// Pass you class name here
REGISTER_CPU_OP(EluOp);
```

### Adding your custom frontend and backend to CMake files

#### Custom Plugin

Add your frontend files and backend files to ``CMakeLists.txt``.

```
add_library(Elu SHARED
    relu/Elu.cpp
    relu/op_Elu.cpp
    relu/tg_elu.cpp
    relu/layer_Elu.cpp)
// Add dependencies means Elu will be built if bmnet onnx yaml-cpp exists
add_dependencies(Elu bmnet onnx yaml-cpp)
// Add library dependencies to dynamic library Elu
target_link_libraries(Elu "libyaml-cpp.so")
install(TARGETS Elu DESTINATION lib/plugin)
```

#### CPU Plugin

Add your cpp file to function ``add_cpu_plugin`` in ``cpu_op/CMakeLists.txt``.

```
add_cpu_plugin(ELU.cpp LeakyRelu.cpp)
```

## Build your custom plugin

Follow the instructions below.

```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=<path>
make -j8
make install
cd ../
./build_cpu_op.sh
```
