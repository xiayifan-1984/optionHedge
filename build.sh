#!/usr/bin/bash
export CC=/usr/local/bin/gcc
export CXX=/usr/local/bin/g++
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
=======
rm -rf build
mkdir build
chmod 777 build
cd build
cmake -DCMAKE_INSTALL_PREFIX=. ..
make 
make install
