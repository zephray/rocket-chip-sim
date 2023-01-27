#!/bin/bash
cpus=$(nproc --all)
pushd sim
make clean
make -j$cpus
popd
