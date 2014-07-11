CPPFLAGS ?= -Wall -Wextra -std=c++11

all: build/atomic

build/atomic: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp test-atomic.cpp -o build/atomic

build:
	mkdir build

clean:
	rm -rf build
