# rocket-chip-sim

My own wrapper for simulating rocket-chip in Verilator.

## Usage

Make sure the dependencies are installed:

```
sudo apt install libverilog-perl
```

Verilator could be either installed from distribution or built from source.

Set ```ROCKET_CHIP``` env var to point to the rocket-chip installation, if not, clone from official repo.

```
git clone https://github.com/chipsalliance/rocket-chip
export ROCKET_CHIP=$(pwd)/rocket-chip
```

Run ```./scripts/build.sh```. Alternatively, run ```./scripts/genrtl.sh``` to generate individual RTL files, or run ```./scripts/build-sim.sh``` to rebuild simulator binary.

The example folder has some programs that can be run on the simulator.

For example, to run hello world (assuming it has been compiled):

```
./sim/sim --ram example/asm/hello.bin --trace
```

To customize the core configuration, modify the ```config/CustomConfigs.scala``` and re-build.

## Why

The rocket-chip comes with a bundled simulator/ emulator. That works fine for most purposes. However personally I found it a bit slow due to the way it simulates the RAM and how it loads the program. I want my own binary to run as soon as the simulator is up (maybe after a few instructions, but definitely not after thousands or instructions or GBs of waveform dumps), so I created this. Many of the infrastructure shares with the projects I have done before so this is like 2 hours of work, making it justified.

## License

Unless otherwise noted, the source code is licensed under MIT license.
