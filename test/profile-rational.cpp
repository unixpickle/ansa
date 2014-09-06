#include "../src/rational.hpp"
#include "microtime.hpp"
#include <iostream>

using namespace ansa;
using std::cout;
using std::endl;
using std::flush;

uint64_t Time8BitWorst();
uint64_t Time8BitBest();
uint64_t Time64BitWorst();
uint64_t Time64BitBest();

int main() {
  cout << "Rational<uint8_t>::ScaleInteger() [worst case]..." << flush
    << Time8BitWorst() << endl;
  cout << "Rational<uint8_t>::ScaleInteger() [best case]..." << flush
    << Time8BitBest() << endl;
  cout << "Rational<uint64_t>::ScaleInteger() [worst case]..." << flush
    << Time64BitWorst() << endl;
  cout << "Rational<uint64_t>::ScaleInteger() [best case]..." << flush
    << Time64BitBest() << endl;
  return 0;
}

uint64_t Time8BitWorst() {
  Rational<uint8_t> rat(0xff, 0xff);
  uint64_t start = Microtime();
  for (int i = 0; i < 0x1000000; ++i) {
    rat.ScaleInteger(0xff);
  }
  return Microtime() - start;
}

uint64_t Time8BitBest() {
  Rational<uint8_t> rat(0x10, 0x5);
  uint64_t start = Microtime();
  for (int i = 0; i < 0x1000000; ++i) {
    rat.ScaleInteger(0x5);
  }
  return Microtime() - start;
}

uint64_t Time64BitWorst() {
  Rational<uint64_t> rat(UINT64_MAX, UINT64_MAX);
  uint64_t start = Microtime();
  for (int i = 0; i < 0x1000000; ++i) {
    rat.ScaleInteger(UINT64_MAX);
  }
  return Microtime() - start;
}

uint64_t Time64BitBest() {
  Rational<uint64_t> rat(1234, 1231);
  uint64_t start = Microtime();
  for (int i = 0; i < 0x1000000; ++i) {
    rat.ScaleInteger(1231);
  }
  return Microtime() - start;
}
