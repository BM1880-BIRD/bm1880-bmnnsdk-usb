/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
/*
 * bmnet/test/onnx_bm_builder.cpp
 *
 * Copyright Bitmain Technologies Inc.
 * Written by:
 *   Wanwei CAI <wanwei.cai@bitmain.com>
 * Created Time: 2018-07-02 16:23
 */

#include <iostream>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <getopt.h>

#include <bmkernel/bm1880/bmkernel_1880.h>
#include <bmnet/builder/OnnxBuilder.hpp>

#include "op_LeakyRelu.hpp"
#include "op_Elu.hpp"
#include "tg_leakyrelu.hpp"
#include "tg_elu.hpp"

using namespace::bmnet;

struct _arg {
  int         target;
  bool        enable_fusion_layers;
  bool        enable_layer_group;
  const char *name;
  const char *onnxmodel;
  const char *modified_proto;
  const char *weight_bin;
  const char *shape;
  const char *plugin;
  const char *input_tensor;
  const char *out_proto;
  const char *out_model;
  const char *out_weight;
  const char *out_cmdbuf;
};

static struct _arg arg = {.target = BM_CHIP_BM1682,
                          .enable_fusion_layers = false,
                          .enable_layer_group = false,
                          .name = NULL,
                          .onnxmodel = NULL,
                          .modified_proto = NULL,
                          .weight_bin = NULL,
                          .shape = NULL,
                          .plugin = NULL,
                          .input_tensor = NULL,
                          .out_proto = NULL,
                          .out_model = NULL,
                          .out_weight = NULL,
                          .out_cmdbuf = NULL};

static bool file_exist(const char* file) {
  std::ifstream f(file);
  return f.good();
}

static int parse_arg(int argc, char** argv) {
  int opt;
  const char *optstring = "t:n:c:m:w:s:p:o:g:b:u:i:0";
  struct option long_options[] = {
      {"target", required_argument, 0, 't'},
      {"name", required_argument, 0, 'n'},
      {"onnxmodel", required_argument, 0, 'c'},
      {"modified_proto", required_argument, 0, 'm'},
      {"weight_bin", required_argument, 0, 'w'},
      {"shape", required_argument, 0, 's'},
      {"plugin", required_argument, 0, 'u'},
      {"input_tensor", required_argument, 0, 'i'},
      {"out_proto", required_argument, 0, 'p'},
      {"out_model", required_argument, 0, 'o'},
      {"out_weight", required_argument, 0, 'g'},
      {"out_cmdbuf", required_argument, 0, 'b'},
      {"enable-fusion-layers", required_argument, 0, 0},
      {"enable-layer-group", required_argument, 0, 0},
      {NULL, 0, NULL, 0}
  };

  int option_index = 0;
  bool flag;
  const char *option;
  while ((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
    switch(opt) {
    case 0:
      option = long_options[option_index].name;
      VLOG(2) << "option" << " " << optarg;
      if (optarg)
        VLOG(2) << " with arg " <<  optarg;

      if (strcmp("yes", optarg) == 0) {
        flag = true;
      } else if (strcmp("no", optarg) == 0) {
        flag = false;
      } else {
        printf("invalid option arg %s\n", optarg);
        return -1;
      }

      if (strcmp("enable-fusion-layers", option) == 0) {
        arg.enable_fusion_layers = flag;
      } else if (strcmp("enable-layer-group", option) == 0) {
        arg.enable_layer_group = flag;
      } else {
        printf("invalid option %s\n", option);
        return -1;
      }
      break;
    case 't':
      VLOG(2) << "target" << " " << optarg;
      if (strcmp("bm1880", optarg) == 0) {
        arg.target = BM_CHIP_BM1880;
      } else {
        printf("invalid target type %s\n", optarg);
        return -1;
      }
      break;
    case 'n':
      VLOG(2) << "name" << " " << optarg;
      arg.name = optarg;
      break;
    case 'c':
      VLOG(2) << "caffemodel" << " " << optarg;
      if(file_exist(optarg)) {
        arg.onnxmodel = optarg;
      } else {
        LOG(ERROR) << optarg << " does not exist";
        return -1;
      }
      break;
    case 'm':
      printf("modified_proto %s\n", optarg);
      if(file_exist(optarg)) {
        arg.modified_proto = optarg;
      } else {
        LOG(ERROR) << optarg << " does not exist";
        return -1;
      }
      break;
    case 'w':
      printf("weight_bin %s\n", optarg);
      if(file_exist(optarg)) {
        arg.weight_bin = optarg;
      } else {
        LOG(ERROR) << optarg << " does not exist";
        return -1;
      }
      break;
    case 's':
      VLOG(2) << "input " << optarg;
      arg.shape = optarg;
      break;
    case 'u':
      VLOG(2) << "plugin path " << optarg;
      arg.plugin = optarg;
      break;
    case 'i':
      VLOG(2) << "input tensor " << optarg;
      arg.input_tensor = optarg;
      break;
    case 'p':
      VLOG(2) << "output_proto: " << optarg;
      arg.out_proto = optarg;
      break;
    case 'o':
      VLOG(2) << "output_bmodel_model: " << optarg;
      arg.out_model = optarg;
      break;
    case 'g':
      printf("output_weight: %s\n", optarg);
      arg.out_weight = optarg;
      break;
    case 'b':
      printf("output_cmdbuf: %s\n", optarg);
      arg.out_cmdbuf = optarg;
      break;
    default:
      return -1;
    }
  }

  return 0;
}

static bool parse_input_shape(
    std::vector<int>& shapes,
    const char* input,
    char delimiter)
{
  std::string token;
  std::istringstream s(input);
  while (std::getline(s, token, delimiter))
  {
    int dim = std::stoi(token, nullptr, 10);
    shapes.push_back(dim);
  }
  if (shapes.size() != 4) {
    return false;
  }
  return true;
}

static void usage(void) {
    std::cout << "Invalide arguments" << std::endl;
    std::cout << "  bm_builder_onnx.bin " << std::endl
              << "  --target=[bm1880]" << std::endl
              << "  --name=name_of_network" << std::endl
              << "  --onnxmodel=onnxmodel_file" << std::endl
              << "  --modified=modified_prototxt_file" << std::endl
              << "  --weight=weight_file" << std::endl
              << "  --shape=n,c,h,w, give 0 mean using shape info in model, example: --shape=n,0,0,0" << std::endl
              << "  --plugin=path_of_cpu_op_plugin" << std::endl
              << "  --input_tensor=input tendor anme" << std::endl
              << "  --enable-fusion-layers=yes|no [no]" << std::endl
              << "  --enable-layer-group=yes|no [no]" << std::endl
              << "  --out_proto=output_prototxt_file" << std::endl
              << "  --out_model=output_bmodel_file" << std::endl
              << "  --out_weight=output_weight_file" << std::endl
              << "  --out_cmdbuf=output_cmdbuf_file" << std::endl;
}

template <typename Dtype> void bm_build_onnx() {
  std::vector<int> shapes;
  if (arg.shape && !parse_input_shape(shapes, arg.shape, ',')) {
    usage();
    exit(-1);
  }

  OnnxBuilder<Dtype> *builder = new OnnxBuilder<Dtype>(arg.target, arg.onnxmodel);

  int option = 0;
  if (arg.enable_fusion_layers) {
    option = BM_OPT_LAYER_GROUP;
  } else if (arg.enable_layer_group) {
    option = BM_OPT_LAYER_GROUP_WITH_GMEM_RECYCLE;
  }


  builder->addCustomizedLayer(new LeakyReluOp(builder->front_ctx_));
  builder->addCustomizedLayer(new EluOp(builder->front_ctx_));
  if (arg.target == BM_CHIP_BM1880) {
    builder->addCustomizedTensorInst(new TGLeakyReluFixedInst());
    builder->addCustomizedTensorInst(new TGEluFixedInst());
  } else {
    assert(0);
  }

  if (shapes.size())
    builder->build(shapes[0], shapes[1], shapes[2], shapes[3], option);
  else
    builder->build(0, 0, 0, 0, option);

  if (arg.out_proto) {
    builder->store_prototxt(arg.out_proto);
  }

  if (arg.out_weight) {
    builder->store_weight(arg.out_weight);
  }

  if (arg.out_cmdbuf) {
    builder->store_cmdbuf(arg.out_cmdbuf);
  }

  if (arg.out_model) {
    builder->store_model(arg.name, arg.out_model, arg.plugin, arg.input_tensor);
  }
  delete builder;
}

int main(int argc, char** argv) {

  google::InitGoogleLogging("");
  google::SetStderrLogging(google::GLOG_INFO);

  std::cout << "<CMD> ";
  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << " ";
  }
  std::cout << std::endl;

  int ret = parse_arg(argc, argv);
  if (ret ||
      !arg.name ||
      (!arg.out_proto && !arg.out_model) ||
      (!arg.onnxmodel && !arg.modified_proto && !arg.weight_bin)) {
    usage();
    exit(-1);
  }

  if (arg.target == BM_CHIP_BM1880) {
    bm_build_onnx<int8_t>();
  }

  return 0;
}
