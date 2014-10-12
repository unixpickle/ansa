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
void TestBitScanRight();

template <typename T>
void TestAlignment();

template <typename T>
void TestMaxMin();

template <typename T>
void TestIsPowerOf2();

int main() {
  TestLogFloor<unsigned char>();
  TestLogCeil<unsigned char>();
  TestBitScanRight<unsigned char>();
  TestAlignment<unsigned char>();
  TestMaxMin<unsigned char>();
  TestIsPowerOf2<unsigned char>();
  
  TestLogFloor<unsigned short>();
  TestLogCeil<unsigned short>();
  TestBitScanRight<unsigned short>();
  TestAlignment<unsigned short>();
  TestMaxMin<unsigned short>();
  TestIsPowerOf2<unsigned short>();
  
  TestLogFloor<unsigned int>();
  TestLogCeil<unsigned int>();
  TestBitScanRight<unsigned int>();
  TestAlignment<unsigned int>();
  TestMaxMin<unsigned int>();
  TestIsPowerOf2<unsigned int>();
  
  TestLogFloor<unsigned long>();
  TestLogCeil<unsigned long>();
  TestBitScanRight<unsigned long>();
  TestAlignment<unsigned long>();
  TestMaxMin<unsigned long>();
  TestIsPowerOf2<unsigned long>();
  
  TestLogFloor<unsigned long long>();
  TestLogCeil<unsigned long long>();
  TestBitScanRight<unsigned long long>();
  TestAlignment<unsigned long long>();
  TestMaxMin<unsigned long long>();
  TestIsPowerOf2<unsigned long long>();
  
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
    assert(Log2Floor<T>((T)1 << i) == i);
    if (i < bitCount - 1) {
      assert(Log2Floor<T>(((T)1 << (i + 1)) - 1) == i);
    } else {
      assert(Log2Floor<T>(((T)1 << i) + 1) == i);
    }
  }
}

template <typename T>
void TestLogCeil() {
  ScopedPass pass("Testing Log2Ceil<", NumericInfo<T>::name, ">");
  int bitCount = NumericInfo<T>::bitCount;
  
  for (int i = 0; i < bitCount; i++) {
    assert(Log2Ceil<T>((T)1 << i) == i);
    if (i < bitCount - 1 && i > 0) {
      assert(Log2Ceil<T>(((T)1 << (i + 1)) - 1) == i + 1);
    } else {
      assert(Log2Ceil<T>(((T)1 << i) + 1) == i + 1);
    }
  }
}

template <typename T>
void TestBitScanRight() {
  ScopedPass pass("Testing BitScanRight<", NumericInfo<T>::name, ">");
  
  assert(BitScanRight<T>((T)2) == (T)1);
  assert(BitScanRight<T>((T)4) == (T)2);
  const int bitCount = NumericInfo<T>::bitCount;
  for (int i = 0; i < bitCount; ++i) {
    assert(BitScanRight<T>((T)1 << i) == i);
  }
  assert(BitScanRight<T>((T)0) == bitCount);
}

template <typename T>
void TestAlignment() {
  ScopedPass pass("Testing [Align/Alignment]<",
                  NumericInfo<T>::name, ">");
  
  int bitCount = NumericInfo<T>::bitCount;
  
  // The Align() function depends on IsAligned(), so we test IsAligned() first.
  assert(IsAligned<T>((T)3, (T)1));
  assert(IsAligned<T>((T)6, (T)3));
  assert(IsAligned<T>((T)6, (T)2));
  assert(IsAligned<T>((T)6, (T)0));
  assert(IsAligned<T>((T)1 << (bitCount - 1), (T)1 << (bitCount - 2)));
  assert(!IsAligned<T>((T)6, (T)5));
  assert(!IsAligned<T>((T)0x10, (T)0x20));
  assert(!IsAligned<T>((T)1 << (bitCount - 2), (T)1 << (bitCount - 1)));
  
  // Make sure that Align() works properly
  assert(Align<T>((T)3, (T)10) == (T)10);
  assert(Align<T>((T)15, (T)0x10) == (T)0x10);
  assert(Align<T>((T)0x1f, (T)0x10) == (T)0x20);
  assert(Align<T>((T)0x8, (T)0x4) == (T)0x8);
  assert(Align<T>((T)0x8, (T)0x8) == (T)0x8);
  assert(Align<T>((T)0, (T)0x8) == (T)0);
  
  // Check some Alignment() cases
  assert(Alignment<T>((T)0x10) == (T)0x10);
  assert(Alignment<T>((T)0x18) == (T)0x8);
  assert(Alignment<T>((T)3) == (T)1);
  for (int i = 0; i < bitCount; ++i) {
    assert(Alignment<T>((T)1 << i) == (T)1 << i);
  }
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

template <typename T>
void TestIsPowerOf2() {
  ScopedPass pass("Testing IsPowerOf2<", NumericInfo<T>::name, ">");
  
  assert(IsPowerOf2<T>((T)0));
  int bitCount = NumericInfo<T>::bitCount;
  for (int i = 0; i < bitCount; ++i) {
    assert(IsPowerOf2<T>((T)1 << i));
    
    // 2 - 1 = 1 which is still a power of two
    if (i > 1) {
      assert(!IsPowerOf2<T>(((T)1 << i) - 1));
    }
    
    // 1 + 1 = 2 which is still a power of two
    if (i > 0 && i + 1 < bitCount) {
      assert(!IsPowerOf2<T>(((T)1 << i) + 1));
    }
  }
}
