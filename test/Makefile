CPPFLAGS ?= -Wall -Wextra -std=c++11

all: build/atomic build/module build/lock32 build/lock64 build/math build/rational build/cstring build/bit-list build/linked-list

build/atomic: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp test-atomic.cpp -o build/atomic

build/module: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp ../src/module.cpp test-module.cpp -o build/module

build/lock32: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp ../src/lock.cpp test-lock.cpp -D__ANSA_LOCK_SIZE__=32 -o build/lock32

build/lock64: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp ../src/lock.cpp test-lock.cpp -D__ANSA_LOCK_SIZE__=64 -o build/lock64

build/math: build
	g++ $(CPPFLAGS) -I ../include ../src/numeric-info.cpp test-math.cpp -o build/math

build/rational: build
	g++ $(CPPFLAGS) -I ../include ../src/numeric-info.cpp ../src/rational.cpp test-rational.cpp -o build/rational

build/cstring: build
	g++ $(CPPFLAGS) -I ../include ../src/cstring.cpp test-cstring.cpp -o build/cstring

build/bit-list: build
	g++ $(CPPFLAGS) -I ../include test-bit-list.cpp -o build/bit-list

build/linked-list: build
	g++ $(CPPFLAGS) -I ../include test-linked-list.cpp -o build/linked-list

build:
	mkdir build

clean:
	rm -rf build
