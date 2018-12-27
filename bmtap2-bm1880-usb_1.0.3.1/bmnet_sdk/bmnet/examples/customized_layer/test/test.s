ir_version: 3
producer_name: "onnx-caffe2"
producer_version: ""
domain: ""
model_version: 0
doc_string: ""
graph {
  name: "LeNet"
  doc_string: ""
  node { input: "data_0" input: "conv1_w_0" input: "conv1_b_0" output: "conv1_1" name: "" op_type: "Conv" attribute { name: "pads" ints: 0 ints: 0 ints: 0 ints: 0 type: INTS } attribute { name: "strides" ints: 1 ints: 1 type: INTS } attribute { name: "kernel_shape" ints: 5 ints: 5 type: INTS } }
  node { input: "conv1_1" output: "pool1_1" name: "" op_type: "MaxPool" attribute { name: "pads" ints: 0 ints: 0 ints: 0 ints: 0 type: INTS } attribute { name: "kernel_shape" ints: 2 ints: 2 type: INTS } attribute { name: "strides" ints: 2 ints: 2 type: INTS } }
  node { input: "pool1_1" input: "conv2_w_0" input: "conv2_b_0" output: "conv2_1" name: "" op_type: "Conv" attribute { name: "pads" ints: 0 ints: 0 ints: 0 ints: 0 type: INTS } attribute { name: "strides" ints: 1 ints: 1 type: INTS } attribute { name: "kernel_shape" ints: 5 ints: 5 type: INTS } }
  node { input: "conv2_1" output: "pool2_1" name: "" op_type: "MaxPool" attribute { name: "pads" ints: 0 ints: 0 ints: 0 ints: 0 type: INTS } attribute { name: "kernel_shape" ints: 2 ints: 2 type: INTS } attribute { name: "strides" ints: 2 ints: 2 type: INTS } }
  node { input: "pool2_1" input: "OC2_DUMMY_1" output: "OC2_DUMMY_0" op_type: "Reshape" }
  node { input: "OC2_DUMMY_0" input: "ip1_w_0" input: "ip1_b_0" output: "ip1_1" op_type: "Gemm" attribute { name: "transB" i: 1 type: INT } }
  node { input: "ip1_1" output: "customized1" name: "" op_type: "LeakyRelu" attribute { name: "alpha" f: 0.1 type: FLOAT }}
  node { input: "customized1" input: "ip2_w_0" input: "ip2_b_0" output: "ip2_1" op_type: "Gemm" attribute { name: "transB" i: 1 type: INT } }
  node { input: "ip2_1" output: "customized2" name: "" op_type: "Elu" attribute { name: "alpha" f: 0.1 type: FLOAT }}
  input { name: "data_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 1 } dim { dim_value: 1 } dim { dim_value: 28 } dim { dim_value: 28 } } } } }
  input { name: "conv1_w_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 20 } dim { dim_value: 1 } dim { dim_value: 5 } dim { dim_value: 5 } } } } }
  input { name: "conv1_b_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 20 } } } } }
  input { name: "conv2_w_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 50 } dim { dim_value: 20 } dim { dim_value: 5 } dim { dim_value: 5 } } } } }
  input { name: "conv2_b_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 50 } } } } }
  input { name: "ip1_w_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 500 } dim { dim_value: 800 } } } } }
  input { name: "ip1_b_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 500 } } } } }
  input { name: "ip2_w_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 10 } dim { dim_value: 500 } } } } }
  input { name: "ip2_b_0" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 10 } } } } }
  input { name: "OC2_DUMMY_1" type { tensor_type { elem_type: INT64 shape { dim { dim_value: 2 } } } } }
  output { name: "customized2" type { tensor_type { elem_type: FLOAT shape { dim { dim_value: 1 } dim { dim_value: 10 } } } } }
  initializer { 
dims: 2
data_type: INT64
name: "OC2_DUMMY_1"
raw_data: "\001\000\000\000\000\000\000\000 \003\000\000\000\000\000\000"
 }
}
opset_import { domain: "" version: 8 }
metadata_props { key: "data_scale" value: "0.00390625" }
