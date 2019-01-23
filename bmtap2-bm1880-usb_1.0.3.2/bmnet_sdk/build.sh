#!/bin/bash
##
## Copyright (C) Bitmain Technologies Inc.
## All Rights Reserved.
##

set -eux

rm -rf bmnet/build
mkdir -p bmnet/build
pushd bmnet/build
    cmake -DCMAKE_INSTALL_PREFIX=../../install \
          -DBUILD_CUSTOMIZED_LAYER_DEMO=ON ..
    make -j$(nproc)
    make install
popd
rm -rf bmnet/build
