#include <ansa/math>
#include <ansa/numeric-info>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

template <typename T>
void TestLogFloor();

template <typename T>
void TestLogCeil();

template <typename T>
void TestAlign();

template <typename T>
void TestMaxMin();

int main() {
  TestLogFloor<unsigned char>();
  TestLogCeil<unsigned char>();
  TestAlign<unsigned char>();
  TestMaxMin<unsigned char>();
  TestLogFloor<unsigned short>();
  TestLogCeil<unsigned short>();
  TestAlign<unsigned short>();
  TestMaxMin<unsigned short>();
  TestLogFloor<unsigned int>();
  TestLogCeil<unsigned int>();
  TestAlign<unsigned int>();
  TestMaxMin<unsigned int>();
  TestLogFloor<unsigned long>();
  TestLogCeil<unsigned long>();
  TestAlign<unsigned long>();
  TestMaxMin<unsigned long>();
  TestLogFloor<unsigned long long>();
  TestLogCeil<unsigned long long>();
  TestAlign<unsigned long long>();
  TestMaxMin<unsigned long long>();
  
  TestMaxMin<char>();
  TestMaxMin<short>();
  TestMaxMin<int>();
  TestMaxMin<long>();
  TestMaxMin<long long>();
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

template <typename T>
void TestAlign() {
  ScopedPass pass("Testing Align<", NumericInfo<T>::name, ">");
  
  assert(Align(3, 10) == 10);
  assert(Align(15, 0x10) == 0x10);
  assert(Align(0x1f, 0x10) == 0x20);
  assert(Align(0x8, 0x4) == 0x8);
  assert(Align(0x8, 0x8) == 0x8);
  assert(Align(0, 0x8) == 0);
}

template <typename T>
void TestMaxMin() {
  ScopedPass pass("Testing [Max/Min]<", NumericInfo<T>::name, ">");
  if (NumericInfo<T>::isSigned) {
    assert(Max((T)-1, (T)1) == (T)1);
    assert(Max((T)1, (T)-1) == (T)1);
    assert(Max((T)-1, (T)-2) == (T)-1);
    assert(Max((T)-2, (T)-1) == (T)-1);
    assert(Max((T)-1, (T)-1) == (T)-1);
    assert(Min((T)-1, (T)1) == (T)-1);
    assert(Min((T)1, (T)-1) == (T)-1);
    assert(Min((T)-1, (T)-2) == (T)-2);
    assert(Min((T)-2, (T)-1) == (T)-2);
    assert(Min((T)-1, (T)-1) == (T)-1);
  }
  assert(Max((T)1, (T)2) == (T)2);
  assert(Max((T)2, (T)1) == (T)2);
  assert(Max((T)2, (T)2) == (T)2);
  assert(Min((T)1, (T)2) == (T)1);
  assert(Min((T)2, (T)1) == (T)1);
  assert(Min((T)2, (T)2) == (T)2);
}
