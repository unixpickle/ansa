#include <ansa/math>
#include <ansa/numeric-info>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

template <typename T>
void TestLogFloor();

template <typename T>
void TestLogCeil();

int main() {
  TestLogFloor<unsigned char>();
  TestLogCeil<unsigned char>();
  TestLogFloor<unsigned short>();
  TestLogCeil<unsigned short>();
  TestLogFloor<unsigned int>();
  TestLogCeil<unsigned int>();
  TestLogFloor<unsigned long>();
  TestLogCeil<unsigned long>();
  TestLogFloor<unsigned long long>();
  TestLogCeil<unsigned long long>();
  return 0;
}

template <typename T>
void TestLogFloor() {
  ScopedPass pass("Testing Log2Floor<", NumericInfo<T>::name, ">");
  int bitCount = NumericInfo<T>::bitCount;
  
  for (int i = 0; i < bitCount; i++) {
    assert(Log2Floor((T)1 << i) == i);
    if (i < bitCount - 1) {
      assert(Log2Floor(((T)1 << (i + 1)) - 1) == i);
    } else {
      assert(Log2Floor(((T)1 << i) + 1) == i);
    }
  }
}

template <typename T>
void TestLogCeil() {
  ScopedPass pass("Testing Log2Ceil<", NumericInfo<T>::name, ">");
  int bitCount = NumericInfo<T>::bitCount;
  
  for (int i = 0; i < bitCount; i++) {
    assert(Log2Ceil((T)1 << i) == i);
    if (i < bitCount - 1 && i > 0) {
      assert(Log2Ceil(((T)1 << (i + 1)) - 1) == i + 1);
    } else {
      assert(Log2Ceil(((T)1 << i) + 1) == i + 1);
    }
  }
}
