#!/bin/bash

workspace=`pwd`

mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Release -H${workspace} -B${workspace}/build -G "Ninja"
cmake --build ${workspace}/build --config Release --target all -- -j 10
# ctest -C Release