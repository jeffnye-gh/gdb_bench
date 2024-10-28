.PHONY: clean run lib_spdlog.built lib_gdb_server.built

CPP = g++
GDB_TOP := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
TARGET = bin/gdb_example
# --------------------------------------------------------------
ALL_SRC=$(wildcard src/*.cpp)
ALL_OBJ=$(subst    src/,obj/,$(ALL_SRC:.cpp=.o))
ALL_DEP= $(ALL_OBJ:.o=.d)
# --------------------------------------------------------------
DEP  = -MMD -MP
DEF  = -DSTRING_DEFINE="\"v1.1.1\""
INC  = -I./inc -Igdb-server/include
OPT  = -g
STD  = -std=c++20
WARN = -Wall
LIBS = -Lgdb-server/build/src -lgdb-server -Lspdlog/install/lib -lspdlog

CFLAGS   = $(OPT) $(DEP) $(DEF) $(INC)
CPPFLAGS = $(CFLAGS) $(STD)
LDFLAGS  =
# --------------------------------------------------------------
default: run
only: $(TARGET)
# --------------------------------------------------------------
obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGET):  $(ALL_OBJ) obj/lib_spdlog.built obj/lib_gdb_server.built
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

obj/lib_spdlog.built:
	cd spdlog && mkdir -p build && cd build &&  \
	cmake -DCMAKE_INSTALL_PREFIX=../install .. && \
  make -j && make install
	touch obj/lib_spdlog.built

obj/lib_gdb_server.built:
	cd gdb-server && mkdir -p build && cd build && \
	cmake .. -Dspdlog_DIR=$(GDB_TOP)/spdlog/install/lib/cmake/spdlog && make -j
	touch obj/lib_gdb_server.built

run:  $(TARGET)
	$(TARGET)

clean:
	-rm -rf bin/* obj/*
	cd spdlog; rm -rf build
	cd gdb-server; rm -rf build























-include $(ALL_DEP)

