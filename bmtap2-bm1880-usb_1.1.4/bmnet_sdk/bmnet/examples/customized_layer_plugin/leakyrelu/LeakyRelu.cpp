#include <bmnet/builder/plugin/layer_api.hpp>
#include <cmath>

#include "layer_LeakyRelu.hpp"
#include "op_LeakyRelu.hpp"
#include "tg_leakyrelu.hpp"

namespace bmnet {
class LeakyRelu : public LayerAPI {
public:
  LeakyRelu() : LayerAPI() {

  }

  void init(FrontendContext *ctx) override {
    onnx_layer = new LeakyReluOpPlugin(ctx);
    caffe_layer = new LeakyReluLayerPlugin();
    int8_layer_inst = new TGLeakyReluPluginFixedInst();
  }
  const std::string layerName() override { return "LeakyRelu"; }
};
}


// the class factories

extern "C" bmnet::LayerAPI* create() {
  return new bmnet::LeakyRelu();
}

extern "C" void destroy(bmnet::LayerAPI* p) {
  delete p;
}
