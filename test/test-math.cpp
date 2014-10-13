#include <ansa/math>
#include <ansa/numeric-info>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

template <typename T>
void RunAllTests();

template <typename T>
void RunSignedTests();

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

template <typename T>
void TestAddWraps();

int main() {
  RunAllTests<unsigned char>();
  RunAllTests<unsigned short>();
  RunAllTests<unsigned int>();
  RunAllTests<unsigned long>();
  RunAllTests<unsigned long long>();
  
  RunSignedTests<char>();
  RunSignedTests<short>();
  RunSignedTests<int>();
  RunSignedTests<long>();
  RunSignedTests<long long>();
  return 0;
}

template <typename T>
void RunAllTests() {
  TestLogFloor<T>();
  TestLogCeil<T>();
  TestBitScanRight<T>();
  TestAlignment<T>();
  TestMaxMin<T>();
  TestIsPowerOf2<T>();
  TestAddWraps<T>();
}

template <typename T>
void RunSignedTests() {
  TestMaxMin<T>();
  TestAddWraps<T>();
}

template <typename T>
void TestLogFloor() {
  ScopedPass pass("Log2Floor<", NumericInfo<T>::name, ">");
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
  ScopedPass pass("Log2Ceil<", NumericInfo<T>::name, ">");
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
  ScopedPass pass("BitScanRight<", NumericInfo<T>::name, ">");
  
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
  ScopedPass pass("[Align/Alignment]<", NumericInfo<T>::name, ">");
  
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
  ScopedPass pass("[Max/Min]<", NumericInfo<T>::name, ">");
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
  ScopedPass pass("IsPowerOf2<", NumericInfo<T>::name, ">");
  
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

template <typename T>
void TestAddWraps() {
  ScopedPass pass("AddWraps<", NumericInfo<T>::name, ">");
  
  assert(!AddWraps<T>(0, 0));
  assert(!AddWraps<T>(0, 1));
  assert(!AddWraps<T>(1, 0));
  assert(!AddWraps<T>(NumericInfo<T>::max, 0));
  assert(!AddWraps<T>(0, NumericInfo<T>::max));
  assert(!AddWraps<T>(1, NumericInfo<T>::max - 1));
  assert(!AddWraps<T>(NumericInfo<T>::max - 1, 1));
  assert(AddWraps<T>(1, NumericInfo<T>::max));
  assert(AddWraps<T>(NumericInfo<T>::max, 1));
  assert(AddWraps<T>(2, NumericInfo<T>::max - 1));
  assert(AddWraps<T>(NumericInfo<T>::max - 1, 2));
  assert(AddWraps<T>(NumericInfo<T>::max, NumericInfo<T>::max));
  
  if (NumericInfo<T>::isSigned) {
    assert(!AddWraps<T>(0, -1));
    assert(!AddWraps<T>(-1, 0));
    assert(!AddWraps<T>(1, -1));
    assert(!AddWraps<T>(-1, 1));
    assert(!AddWraps<T>(NumericInfo<T>::min, 0));
    assert(!AddWraps<T>(0, NumericInfo<T>::min));
    assert(!AddWraps<T>(NumericInfo<T>::min, NumericInfo<T>::max));
    assert(!AddWraps<T>(NumericInfo<T>::max, NumericInfo<T>::min));
    assert(!AddWraps<T>(NumericInfo<T>::min, 1));
    assert(!AddWraps<T>(1, NumericInfo<T>::min));
    assert(!AddWraps<T>(NumericInfo<T>::min + 1, -1));
    assert(!AddWraps<T>(-1, NumericInfo<T>::min + 1));
    assert(AddWraps<T>(NumericInfo<T>::min, -1));
    assert(AddWraps<T>(-1, NumericInfo<T>::min));
    assert(AddWraps<T>(NumericInfo<T>::min + 1, -2));
    assert(AddWraps<T>(-2, NumericInfo<T>::min + 1));
    assert(AddWraps<T>(NumericInfo<T>::min, NumericInfo<T>::min));
  }
}
