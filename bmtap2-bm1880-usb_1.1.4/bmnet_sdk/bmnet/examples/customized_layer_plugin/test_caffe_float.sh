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
  -c ./test/float/test.caffemodel \
  -m ./test/float/test_deploy_float.proto \
  --enable-layer-group=yes \
  -s 1,1,28,28 \
  -u ${INSTALL_PATH}/lib/ \
  -p test_frontend_opt.proto \
  -o test_1_1_28_28.bmodel || exit $?

# run bmodel.
test_bmnet_bmodel \
  ./test/float/test_input_1_1_28_28.bin \
  test_1_1_28_28.bmodel \
  output.bin \
  1 1 28 28 || exit $?

# compare with reference result.
bin2float.py compare \
  output.bin \
  ./test/float/test_output_1_1_28_28_ref.bin \
  0.00001 || exit $?

# compile network into bmodel file.
ELU_RUN_ON_CPU=1 bm_builder.bin -t bm1682 \
  -n test \
  -c ./test/float/test.caffemodel \
  -m ./test/float/test_deploy_float.proto \
  --enable-layer-group=yes \
  -s 1,1,28,28 \
  -u ${INSTALL_PATH}/lib/ \
  -p test_frontend_cpu_opt.proto \
  -o test_cpu_1_1_28_28.bmodel || exit $?

# run bmodel.
test_bmnet_bmodel \
  ./test/float/test_input_1_1_28_28.bin \
  test_cpu_1_1_28_28.bmodel \
  output_cpu.bin \
  1 1 28 28 || exit $?

# compare with reference result.
bin2float.py compare \
  output_cpu.bin \
  ./test/float/test_output_1_1_28_28_ref.bin \
  0.00001 || exit $?
