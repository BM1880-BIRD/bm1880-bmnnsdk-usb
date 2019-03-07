#! /bin/bash
##
## Copyright (C) Bitmain Technologies Inc.
## All Rights Reserved.
##
#
set -eux

# setup environment varables.
INSTALL_PATH=${PWD}/../../../install/
export PATH=${INSTALL_PATH}/bin/:${PATH}
export LD_LIBRARY_PATH=${INSTALL_PATH}/lib/

echo $PATH

# compile network into bmodel file.
bm_builder_demo.bin -t bm1880 \
  -n test \
  -c ./test/int8/bmnet_lenet_test.caffemodel \
  -m ./test/test_deploy.proto \
  --in_ctable=./test/int8/bmnet_lenet_calibration.pb2 \
  --out_ctable=./test/int8/bmnet_lenet_ctable_opt.pb2 \
  --enable-layer-group=yes \
  -s 1,1,28,28 \
  -u ${INSTALL_PATH}/lib/ \
  -p test_frontend_opt.proto \
  -o test_1_1_28_28.bmodel

# run bmodel.
test_bmnet_bmodel \
  ./test/int8/test_input_1_1_28_28.bin \
  test_1_1_28_28.bmodel \
  output.bin \
  1 1 28 28

# compare with reference result.
compare_bin.py i1 \
  output.bin \
  ./test/int8/test_output_1_1_28_28_ref.bin \
  1
