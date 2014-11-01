CXXFLAGS ?= -Wall -Wextra -std=c++11
EXTRA_ARGS=$(wildcard ../src/*.cpp) -I../include

SOURCES=$(wildcard *.cpp)
PRODUCTS=$(SOURCES:%.cpp=build/%)

.PHONY: all clean

all: $(PRODUCTS)

build/profile%: profile%.cpp build
	$(CXX) $(CXXFLAGS) $(EXTRA_ARGS) -O3 $< -o $@

build/test%: test%.cpp build
	$(CXX) $(CXXFLAGS) $(EXTRA_ARGS) $< -o $@

build:
	mkdir build

clean:
	rm -rf build
