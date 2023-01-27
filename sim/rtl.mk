all: simtop

VOBJ := obj_dir
CXX   := g++
FBDIR := .
VERBOSE ?= 0
TRACE ?= 1
MULTITHREAD ?= 0
TARGET ?= core_wrapper
CPUS ?= $(shell bash -c 'nproc --all')

.PHONY: all
simtop: $(VOBJ)/V$(TARGET)__ALL.a

SUBMAKE := $(MAKE) --no-print-directory --directory=$(VOBJ) -f
ifeq ($(VERILATOR_ROOT),)
VERILATOR := verilator
else
VERILATOR := $(VERILATOR_ROOT)/bin/verilator
endif
VFLAGS := --x-initial-edge -Wno-fatal -Wno-TIMESCALEMOD -Wno-WIDTH -MMD -cc \
		-I../gen -CFLAGS -Ofast --trace

ifeq ($(VERBOSE), 0)
VFLAGS += +define+PRINTF_COND=0
endif
ifeq ($(MULTITHREAD), 1)
VFLAGS += --threads 2
endif

$(VOBJ)/V$(TARGET)__ALL.a: $(VOBJ)/V$(TARGET).cpp $(VOBJ)/V$(TARGET).h
$(VOBJ)/V$(TARGET)__ALL.a: $(VOBJ)/V$(TARGET).mk

$(VOBJ)/V%.cpp $(VOBJ)/V%.h $(VOBJ)/V%.mk: $(FBDIR)/%.v
	$(VERILATOR) $(VFLAGS) $*.v

$(VOBJ)/V%.cpp: $(VOBJ)/V%.h
$(VOBJ)/V%.mk:  $(VOBJ)/V%.h
$(VOBJ)/V%.h: $(FBDIR)/%.v

$(VOBJ)/V%__ALL.a: $(VOBJ)/V%.mk
	$(SUBMAKE) V$*.mk -j$(CPUS)

.PHONY: clean
clean:
	rm -rf $(VOBJ)/*.mk
	rm -rf $(VOBJ)/*.cpp
	rm -rf $(VOBJ)/*.h
	rm -rf $(VOBJ)/
