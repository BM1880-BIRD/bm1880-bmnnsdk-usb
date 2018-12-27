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

function build_cpu_op()
{
  toolchain=""
  if [ $1 == "armv8" ]; then
    toolchain="-DCMAKE_TOOLCHAIN_FILE=${PWD}/cpu_op/toolchain-aarch64-linux.cmake"
  fi
  echo "toochain $toolchain"
  rm -rf cpu_op/build
  mkdir -p cpu_op/build
  pushd cpu_op/build
    cmake $toolchain \
        -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH ..
    make
    make install
  popd
  rm -rf cpu_op/build
}

build_cpu_op "armv8"
build_cpu_op "x86_64"
