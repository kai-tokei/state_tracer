#!/bin/sh

rm -rf build
mkdir build
cp sub_graph.txt ./build/sub_graph.txt

cd build
g++ ../main.cpp

./a.out 000 1
cat table.csv
cd ..
