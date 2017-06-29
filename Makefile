# Makefile for test-wasm-mem
# Parameters:
#   DBG=0 or 1 (default = 0)

# Remove builtin suffix rules
.SUFFIXES:

# _DBG will be 0 if DBG isn't defined on the command line
_DBG = +$(DBG)
ifeq ($(_DBG), +)
  _DBG = 0
endif

bugpoint.wasm=$(binDir)/bugpoint
cc.wasm=$(binDir)/clang
llc.wasm=$(binDir)/llc
s2wasm=$(binDir)/s2wasm
wast2wasm=$(binDir)/wast2wasm
wasm2wast=$(binDir)/wasm2wast
wasm-link=$(binDir)/wasm-link

CFLAGS_Wno=-Wno-padded -Wno-format-pedantic -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c99-extensions

CC=clang
CFLAGS=-O0 -g --std=c++14 -Weverything -Werror $(CFLAGS_Wno) $(incDir) -DDBG=$(_DBG)

OD=objdump
ODFLAGS=-S -M x86_64,intel

LNK=$(CC)
LNKFLAGS=-lstdc++ -lm

COMPILE.cc=$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -x c++ -c

SRCS=si.cc Structure.cc
OBJS=$(patsubst %.cc,%.o,$(SRCS))
INCS=$(patsubst %.cc,%.h,$(SRCS))
OTHER_DEPS=Makefile

%.o: %.cc $(INCS) $(OTHER_DEPS)
	$(COMPILE.cc) $< -o $@
	$(OD) $(ODFLAGS) $@ > $(basename $@).asm

%: %.o
	$(LNK) $(LNKFLAGS) $(OBJS) -o $@

%.asm: %
	$(OD) $(ODFLAGS) $< > $@

all: si si.asm

run: si
	./$<

vg: si
	valgrind --leak-check=yes --track-origins=yes ./$<

si: $(OBJS)

clean:
	@rm -rf si *.asm $(OBJS)
