#!/bin/bash
export CC=/usr/local/bin/gcc
export CXX=/usr/local/bin/g++
rm -rf build
mkdir build
chmod 777 build
cd build
cmake -DCMAKE_INSTALL_PREFIX=. ..
make 
make install