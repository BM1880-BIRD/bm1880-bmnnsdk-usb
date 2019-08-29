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
