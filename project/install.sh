#!/bin/sh
cmake -S . -B out/build
cd out/build || exit
make install