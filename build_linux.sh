#!/bin/bash

workspace=`pwd`

mkdir -p build
cmake -DCMAKE_PREFIX_PATH=$HOME/capnproto -DCMAKE_BUILD_TYPE=Release -H${workspace} -B${workspace}/build -G "Ninja"
cmake --build ${workspace}/build --config Release --target all -- -j 3
# ctest -C Release