CPPFLAGS ?= -Wall -Wextra -std=c++11

all: build/atomic build/module build/lock build/math build/rational build/cstring

build/atomic: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp test-atomic.cpp -o build/atomic

build/module: build
	g++ $(CPPFLAGS) -I ../include ../src/atomic.cpp ../src/module.cpp test-module.cpp -o build/module

build/lock: build
	gcc -Wall -Wextra -c ../dependencies/anlock/src/anlock.c -o build/anlock.o
	g++ $(CPPFLAGS) -I ../include ../src/lock.cpp build/anlock.o test-lock.cpp -o build/lock
	rm build/anlock.o

build/math: build
	g++ $(CPPFLAGS) -I ../include ../src/numeric-info.cpp test-math.cpp -o build/math

build/rational: build
	g++ $(CPPFLAGS) -I ../include ../src/numeric-info.cpp ../src/rational.cpp test-rational.cpp -o build/rational

build/cstring: build
	g++ $(CPPFLAGS) -I ../include ../src/cstring.cpp test-cstring.cpp -o build/cstring

build:
	mkdir build

clean:
	rm -rf build
