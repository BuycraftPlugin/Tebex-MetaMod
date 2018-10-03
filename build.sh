#!/bin/bash

cd "${0%/*}"
rm -f binaries/*.so
rm -f binaries/*.dll
make clean
make
mv *.so binaries/
mv *.dll binaries/

