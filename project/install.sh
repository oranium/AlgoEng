#!/bin/sh
mkdir -p out
mkdir -p out/build
cmake -S . -B out/build
cd out/build || exit
make install
