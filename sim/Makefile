TARGET := sim
OBJODIR := obj
RTLDIR := .
VERBOSE ?= 0
MULTITHREAD ?= 0
VTARGET ?= core_wrapper

ifeq ($(VERILATOR_ROOT),)
VERILATOR_ROOT ?= $(shell bash -c 'verilator -V | grep VERILATOR_ROOT | head -1 | sed -e " s/^.*=\s*//"')
endif
VROOT := $(VERILATOR_ROOT)
VINCD := $(VROOT)/include
RTLOBJDIR := $(RTLDIR)/obj_dir
RTLOBJ := $(RTLOBJDIR)/V$(VTARGET)__ALL.a

CC = g++
CXX = g++
LD = g++

LIBS := -lm

COMMONFLAGS := \
	-Wall -Ofast -g -D$(shell echo '$(VTARGET)' | tr '[:lower:]' '[:upper:]')

ifeq ($(VERBOSE), 1)
COMMONFLAGS += -DVERBOSE
endif
ifeq ($(MULTITHREAD), 1)
COMMONFLAGS += -DVL_THREADED
endif

CPPFLAGS := \
	-faligned-new \
	-std=c++17

LDFLAGS :=

INCLUDES += \
	-I. \
	-I$(RTLOBJDIR) \
	-I$(RTLDIR) \
	-I$(VINCD) \
	-I$(VINCD)/vltstd

CSRCS +=

CPPSRCS += \
	./main.cpp \
	./axiep.cpp \
	./memmap.cpp \
	verilated.cpp \
	verilated_vcd_c.cpp \
	verilated_threads.cpp

OBJS :=	$(CSRCS:%.c=$(OBJODIR)/%.o) \
		$(CPPSRCS:%.cpp=$(OBJODIR)/%.o)

OBJS += $(RTLOBJ)

$(RTLOBJ):
	@echo Building RTL
	TARGET=$(VTARGET) make -f rtl.mk

$(OBJODIR)/%.o: %.c $(RTLOBJ)
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(COMMONFLAGS) $(CCFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJODIR)/%.o: %.cpp $(RTLOBJ)
	@echo [CXX] $<
	@mkdir -p $(dir $@)
	$(CXX) $(COMMONFLAGS) $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJODIR)/%.o: $(VINCD)/%.cpp
	@echo [CXX] $<
	@mkdir -p $(dir $@)
	@$(CXX) $(COMMONFLAGS) $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

.PHONY: all
all: $(OBJS)
	@$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(TARGET)
	@echo 'all finish'

.PHONY: clean
clean:
	rm -rf $(OBJODIR)
	rm -f $(TARGET)
	make -f rtl.mk clean
	@echo 'clean finish'

.DEFAULT_GOAL:= all
