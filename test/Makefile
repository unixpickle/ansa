CPPFLAGS ?= -Wall -Wextra -std=c++11

all: build/atomic build/module

build/atomic: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp test-atomic.cpp -o build/atomic

build/module: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp ../src/module.cpp test-module.cpp -o build/module

build:
	mkdir build

clean:
	rm -rf build
