CPPFLAGS ?= -Wall -Wextra -std=c++11

all: build/atomic build/atomic-ptr build/module build/lock32 build/lock64 build/math build/rational build/cstring build/bit-list build/linked-list build/profile-rational-o0 build/profile-rational-o3

build/atomic: build
	g++ $(CPPFLAGS) -I ../include test-atomic.cpp -o build/atomic

build/atomic-ptr: build
	g++ $(CPPFLAGS) -I ../include test-atomic-ptr.cpp -o build/atomic-ptr

build/module: build
	g++ $(CPPFLAGS) -I ../include ../src/module.cpp test-module.cpp -o build/module

build/lock32: build
	g++ $(CPPFLAGS) -I ../include ../src/lock.cpp test-lock.cpp -D__ANSA_LOCK_SIZE__=32 -o build/lock32

build/lock64: build
	g++ $(CPPFLAGS) -I ../include ../src/lock.cpp test-lock.cpp -D__ANSA_LOCK_SIZE__=64 -o build/lock64

build/math: build
	g++ $(CPPFLAGS) -I ../include test-math.cpp -o build/math

build/rational: build
	g++ $(CPPFLAGS) -I ../include ../src/rational.cpp test-rational.cpp -o build/rational

build/cstring: build
	g++ $(CPPFLAGS) -I ../include ../src/cstring.cpp test-cstring.cpp -o build/cstring

build/bit-list: build
	g++ $(CPPFLAGS) -I ../include test-bit-list.cpp -o build/bit-list

build/linked-list: build
	g++ $(CPPFLAGS) -I ../include test-linked-list.cpp -o build/linked-list

build/profile-rational-o0: build
	g++ $(CPPFLAGS) -I ../include ../src/rational.cpp profile-rational.cpp -o build/profile-rational-o0

build/profile-rational-o3: build
	g++ $(CPPFLAGS) -O3 -I ../include ../src/rational.cpp profile-rational.cpp -o build/profile-rational-o3

build:
	mkdir build

clean:
	rm -rf build
