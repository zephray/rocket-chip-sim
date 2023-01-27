#!/bin/bash
set -x
cwd=$(pwd)
cp $cwd/config/CustomConfigs.scala $ROCKET_CHIP/src/main/scala/system/
cd $ROCKET_CHIP/vsim
make clean
make CONFIG=freechips.rocketchip.system.CustomConfig verilog
cd generated-src/
mkdir -p $cwd/t
cp freechips.rocketchip.system.CustomConfig.v $cwd/t/
cp freechips.rocketchip.system.CustomConfig.behav_srams.v $cwd/t/
# Uncomment below to clean output of rocket-chip
# make clean
cd $ROCKET_CHIP/src/main/resources/vsrc
cp EICG_wrapper.v $cwd/t/
cp ClockDivider2.v $cwd/t/
cp ClockDivider3.v $cwd/t/
cp plusarg_reader.v $cwd/t/
rm -rf $cwd/gen
mkdir -p $cwd/gen
cd $cwd
./scripts/vsplitmodule
# Clean up
rm -rf t
rm $ROCKET_CHIP/src/main/scala/system/CustomConfigs.scala
