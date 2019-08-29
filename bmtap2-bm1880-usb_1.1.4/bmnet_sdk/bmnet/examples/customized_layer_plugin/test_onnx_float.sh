#! /bin/bash
##
## Copyright (C) Bitmain Technologies Inc.
## All Rights Reserved.
##
#

# setup environment varables.
PWD=$(pwd)
INSTALL_PATH=${PWD}/../../../install/
export PATH=${INSTALL_PATH}/bin/:${PATH}
export LD_LIBRARY_PATH=${INSTALL_PATH}/lib/

echo $PATH

# compile network into bmodel file.
bm_builder.bin -t bm1682 \
  -n test \
  -i ./test/float/output.onnx \
  -s 1,0,0,0 \
  --enable-layer-group=yes \
  -u ${INSTALL_PATH}/lib/ \
  -p test_opt_from_onnx.proto \
  -o test_onnx_1_1_28_28.bmodel || exit $?

# run bmodel.
test_bmnet_bmodel \
  ./test/float/test_input_1_1_28_28.bin \
  test_onnx_1_1_28_28.bmodel \
  output.bin \
  1 1 28 28 || exit $?

# compare with reference result.
#compare_bin.py i1 \
#  output.bin \
#  ./test/test_onnx_output_1_1_28_28_ref.bin \
#  1 || exit $?
