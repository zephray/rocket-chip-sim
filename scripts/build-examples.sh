#!/bin/bash
pushd example/asm
make clean
make
popd
pushd example/c/c-hello
make clean
make
popd
pushd example/c/dhrystone
make clean
make
popd
pushd example/c/coremark
make clean
make
popd
