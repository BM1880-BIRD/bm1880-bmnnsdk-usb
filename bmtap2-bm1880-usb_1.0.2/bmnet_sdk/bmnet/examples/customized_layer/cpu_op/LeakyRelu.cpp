/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#include <bmnet/targets/cpu/cpu_op.hpp>


namespace bmnet {

class LeakyReluOp: public CpuOp {

public:

  void run() {

    assert(op_.type() == "LeakyRelu");
    const TensorShape& input_shape = op_.input_shape(0);
    int count = GetTensorCount(input_shape);

    char *input_data = NULL;
    char *output_data = NULL;
    float *bottom_data = NULL;
    float *top_data = NULL;
    if (op_.threshold_x_size() > 0) {
      std::cout << "[LeakyRelu]thx:" << op_.threshold_x(0)<<std::endl;
      input_data = reinterpret_cast<char*>(op_.global_input(0));
      bottom_data = (float*)malloc(sizeof(float) * count);
      for (int i = 0; i < count; ++i) {
        bottom_data[i] = input_data[i] * op_.threshold_x(0) /128.0;
        std::cout << "bottom:" << i<<"="<<bottom_data[i] << std::endl;
      }
    }
    else {
      bottom_data = reinterpret_cast<float*>(op_.global_input(0));
    }

    if (op_.threshold_y_size() > 0) {
      std::cout << "[LeakyRelu]thy:" << op_.threshold_y(0)<<std::endl;
      output_data = reinterpret_cast<char*>(op_.global_output(0));
      top_data = (float*)malloc(sizeof(float) * count);
    }
    else {
      top_data = reinterpret_cast<float*>(op_.global_output(0));
    }

    float negative_slope = op_.tg_customized_param().f32_param(0);

    std::cout << " [leakyrelu run] bottom:" << bottom_data
              << " top: " << top_data
              << " count: " << count
              << " negative_slope:" << negative_slope
              << std::endl;

    for (int i = 0; i < count; ++i) {
      top_data[i] = std::max(bottom_data[i], (float)0)
          + negative_slope * (std::min(bottom_data[i], (float)0));
    }

    for (int i = 0; i < count; ++i) {
      if (op_.threshold_y_size() > 0) {
        int fixed_data = (int)(top_data[i] * 128  / op_.threshold_y(0) + 0.5);
        output_data[i] = (fixed_data < -128) ? -128 : ((fixed_data > 127) ? 127 : fixed_data);
        std::cout << " output: " <<i<<"="<<top_data[i]<<","<<(int)output_data[i] << std::endl;
      }
      else {
        std::cout << " output: " <<i<<"="<<top_data[i]<< std::endl;
      }
    }
    if (op_.threshold_y_size() > 0) {
      free(top_data);
    }
    if (op_.threshold_x_size() > 0) {
      free(bottom_data);
    }

    std::cout << "cpu_op: leakyrelu_op done" << std::endl;
  }

};

}

REGISTER_CPU_OP(LeakyReluOp);
