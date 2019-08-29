/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#include <bmnet/targets/cpu/cpu_op.hpp>
#define DEBUG 0

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

REGISTER_CPU_OP(EluOp);
