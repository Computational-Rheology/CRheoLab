#! /bin/bash
rm -rf build /usr/local/bin/CRheo
mkdir build
cmake -S . -B build/
cd build
sudo make install 
