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

template <typename T>
void TestMulWraps();

template <typename T>
void TestSubWraps();

template <typename T>
void TestRoundUpDiv();

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
  TestMulWraps<T>();
  TestSubWraps<T>();
  TestRoundUpDiv<T>();
}

template <typename T>
void RunSignedTests() {
  TestMaxMin<T>();
  TestAddWraps<T>();
  TestMulWraps<T>();
  TestSubWraps<T>();
  TestRoundUpDiv<T>();
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
  
  // Test IsAligned()
  assert(IsAligned<T>((T)3, (T)1));
  assert(IsAligned<T>((T)6, (T)3));
  assert(IsAligned<T>((T)6, (T)2));
  assert(IsAligned<T>((T)1 << (bitCount - 1), (T)1 << (bitCount - 2)));
  assert(!IsAligned<T>((T)6, (T)5));
  assert(!IsAligned<T>((T)0x10, (T)0x20));
  assert(!IsAligned<T>((T)1 << (bitCount - 2), (T)1 << (bitCount - 1)));
  
  // Test Align()
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
  
  // Test IsAligned2()
  assert(IsAligned2<T>((T)0x10, (T)2));
  assert(!IsAligned2<T>((T)0x10, (T)0x20));
  assert(IsAligned2<T>((T)0x28, (T)4));
  assert(IsAligned2<T>((T)0x28, (T)8));
  assert(!IsAligned2<T>((T)0x28, (T)0x10));
  
  // Test Align2()
  assert(Align2<T>((T)0x14, 0x10) == 0x20);
  assert(Align2<T>((T)0x2c, 0x4) == 0x2c);
  assert(Align2<T>((T)0x2c, 0x8) == 0x30);
  assert(Align2<T>((T)0, 0x10) == 0);
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

template <typename T>
void TestMulWraps() {
  ScopedPass pass("MulWraps<", NumericInfo<T>::name, ">");
  
  assert(!MulWraps<T>(0, NumericInfo<T>::max));
  assert(!MulWraps<T>(NumericInfo<T>::max, 0));
  assert(!MulWraps<T>(1, NumericInfo<T>::max));
  assert(!MulWraps<T>(NumericInfo<T>::max, 1));
  assert(MulWraps<T>(2, NumericInfo<T>::max));
  assert(MulWraps<T>(NumericInfo<T>::max, 2));
  assert(MulWraps<T>(NumericInfo<T>::max, NumericInfo<T>::max));
  assert(MulWraps<T>(NumericInfo<T>::max - 1, 2));
  assert(MulWraps<T>(2, NumericInfo<T>::max - 1));
  for (T i = 2; i < 10; ++i) {
    assert(MulWraps<T>(i, NumericInfo<T>::max - i));
    assert(MulWraps<T>(NumericInfo<T>::max - i, i));
  }
  // Sanity checks
  assert(MulWraps<T>(11, NumericInfo<T>::max / 10));
  assert(MulWraps<T>(NumericInfo<T>::max / 10, 11));
  assert(!MulWraps<T>(10, NumericInfo<T>::max / 10));
  assert(!MulWraps<T>(NumericInfo<T>::max / 10, 10));
  
  if (NumericInfo<T>::isSigned) {
    // Some random sanity checks
    assert(!MulWraps<T>(-0x10, -2));
    assert(!MulWraps<T>(-2, -0x10));
    assert(!MulWraps<T>(-5, -5));
    
    assert(!MulWraps<T>(0, NumericInfo<T>::min));
    assert(!MulWraps<T>(NumericInfo<T>::min, 0));
    assert(!MulWraps<T>(1, NumericInfo<T>::min));
    assert(!MulWraps<T>(NumericInfo<T>::min, 1));
    assert(MulWraps<T>(-1, NumericInfo<T>::min));
    assert(MulWraps<T>(NumericInfo<T>::min, -1));
    assert(MulWraps<T>(2, NumericInfo<T>::min));
    assert(MulWraps<T>(NumericInfo<T>::min, 2));
    assert(MulWraps<T>(NumericInfo<T>::min, NumericInfo<T>::min));
    assert(MulWraps<T>(NumericInfo<T>::min + 1, 2));
    assert(MulWraps<T>(2, NumericInfo<T>::min + 1));
    for (T i = 2; i < 10; ++i) {
      // Positive i
      assert(MulWraps<T>(i, NumericInfo<T>::min + i));
      assert(MulWraps<T>(NumericInfo<T>::min + i, i));
      assert(MulWraps<T>(i, NumericInfo<T>::min));
      assert(MulWraps<T>(NumericInfo<T>::min, i));
      // Negative i
      assert(MulWraps<T>(-i, NumericInfo<T>::min + i));
      assert(MulWraps<T>(NumericInfo<T>::min + i, -i));
      assert(MulWraps<T>(-i, NumericInfo<T>::min));
      assert(MulWraps<T>(NumericInfo<T>::min, -i));
    }
    // Sanity checks
    assert(MulWraps<T>(NumericInfo<T>::min / 10, 11));
    assert(MulWraps<T>(11, NumericInfo<T>::min / 10));
    assert(MulWraps<T>(NumericInfo<T>::min / 10, -11));
    assert(MulWraps<T>(-11, NumericInfo<T>::min / 10));
    
    assert(!MulWraps<T>(NumericInfo<T>::min / 10, 10));
    assert(!MulWraps<T>(10, NumericInfo<T>::min / 10));
    assert(!MulWraps<T>(NumericInfo<T>::min / 10, -10));
    assert(!MulWraps<T>(-10, NumericInfo<T>::min / 10));
  }
}

template <typename T>
void TestSubWraps() {
  ScopedPass pass("SubWraps<", NumericInfo<T>::name, ">");
  
  assert(!SubWraps<T>(10, 2));
  assert(!SubWraps<T>(10, 0));
  assert(!SubWraps<T>(10, 10));
  assert(!SubWraps<T>(NumericInfo<T>::max, NumericInfo<T>::max));
  assert(!SubWraps<T>(NumericInfo<T>::min, NumericInfo<T>::min));
  
  if (NumericInfo<T>::isSigned) {
    // Subtracting zero
    assert(!SubWraps<T>(1, 0));
    assert(!SubWraps<T>(NumericInfo<T>::min, 0));
    assert(!SubWraps<T>(NumericInfo<T>::max, 0));
    // Subtracting the maximum value
    assert(!SubWraps<T>(0, NumericInfo<T>::max));
    assert(!SubWraps<T>(-1, NumericInfo<T>::max));
    assert(SubWraps<T>(-2, NumericInfo<T>::max));
    assert(SubWraps<T>(-3, NumericInfo<T>::max));
    // Subtracting the minimum value
    assert(SubWraps<T>(0, NumericInfo<T>::min));
    assert(SubWraps<T>(1, NumericInfo<T>::min));
    assert(!SubWraps<T>(-1, NumericInfo<T>::min));
    assert(SubWraps<T>(NumericInfo<T>::max, NumericInfo<T>::min));
    // Subtracting from the maximum value
    assert(SubWraps<T>(NumericInfo<T>::max, -1));
    assert(!SubWraps<T>(NumericInfo<T>::max, 1));
    assert(!SubWraps<T>(NumericInfo<T>::max, NumericInfo<T>::max));
    // Subtracting from the minimum value
    assert(!SubWraps<T>(NumericInfo<T>::min, -2));
    assert(!SubWraps<T>(NumericInfo<T>::min, -1));
    assert(SubWraps<T>(NumericInfo<T>::min, 1));
    assert(SubWraps<T>(NumericInfo<T>::min, 2));
  } else {
    assert(SubWraps<T>(10, 11));
    assert(SubWraps<T>(NumericInfo<T>::max - 1, NumericInfo<T>::max));
    assert(!SubWraps<T>(NumericInfo<T>::max, NumericInfo<T>::max - 1));
  }
}

template <typename T>
void TestRoundUpDiv() {
  ScopedPass pass("RoundUpDiv<", NumericInfo<T>::name, ">");
  
  assert(RoundUpDiv<T>(4, 2) == 2);
  assert(RoundUpDiv<T>(5, 1) == 5);
  assert(RoundUpDiv<T>(5, 2) == 3);
  assert(RoundUpDiv<T>(5, 3) == 2);
  assert(RoundUpDiv<T>(5, 5) == 1);
  assert(RoundUpDiv<T>(5, 6) == 1);
  assert(RoundUpDiv<T>(NumericInfo<T>::max, 2) == NumericInfo<T>::max / 2 + 1);
  
  if (NumericInfo<T>::isSigned) {
    // Trivial negative case
    assert(RoundUpDiv<T>(-4, -2) == 2);
    assert(RoundUpDiv<T>(-4, 2) == -2);
    assert(RoundUpDiv<T>(4, -2) == -2);
    
    // Negative / negative
    assert(RoundUpDiv<T>(-5, -1) == 5);
    assert(RoundUpDiv<T>(-5, -2) == 3);
    assert(RoundUpDiv<T>(-5, -3) == 2);
    assert(RoundUpDiv<T>(-5, -5) == 1);
    assert(RoundUpDiv<T>(-5, -6) == 1);
    
    // Negative / positive and positive / negative
    for (int i = 0; i < 2; ++i) {
      int p1 = i ? 1 : -1;
      int p2 = -p1;
      assert(RoundUpDiv<T>(p1 * 5, p2 * 1) == -5);
      assert(RoundUpDiv<T>(p1 * 5, p2 * 2) == -3);
      assert(RoundUpDiv<T>(p1 * 5, p2 * 3) == -2);
      assert(RoundUpDiv<T>(p1 * 5, p2 * 5) == -1);
      assert(RoundUpDiv<T>(p1 * 5, p2 * 6) == -1);
    }
    
    // Same tests as above, but with roundDownNegative = false.
    
    assert(RoundUpDiv<T>(-4, -2, false) == 2);
    assert(RoundUpDiv<T>(-4, 2, false) == -2);
    assert(RoundUpDiv<T>(4, -2, false) == -2);
    
    assert(RoundUpDiv<T>(-5, -1, false) == 5);
    assert(RoundUpDiv<T>(-5, -2, false) == 3);
    assert(RoundUpDiv<T>(-5, -3, false) == 2);
    assert(RoundUpDiv<T>(-5, -5, false) == 1);
    assert(RoundUpDiv<T>(-5, -6, false) == 1);
    
    for (int i = 0; i < 2; ++i) {
      int p1 = i ? 1 : -1;
      int p2 = -p1;
      assert(RoundUpDiv<T>(p1 * 5, p2 * 1, false) == -5);
      assert(RoundUpDiv<T>(p1 * 5, p2 * 2, false) == -2);
      assert(RoundUpDiv<T>(p1 * 5, p2 * 3, false) == -1);
      assert(RoundUpDiv<T>(p1 * 5, p2 * 5, false) == -1);
      assert(RoundUpDiv<T>(p1 * 5, p2 * 6, false) == 0);
    }
    
    // Basic min/2 case
    assert(RoundUpDiv<T>(NumericInfo<T>::min, 2) == NumericInfo<T>::min / 2);
  }
}
