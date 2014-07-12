#include <ansa/rational>
#include <ansa/numeric-info>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

void TestConstructorsAndCopy();

template <typename T>
void TestScaleUnderflow();

template <typename T>
void TestScaleOverflow();

int main() {
  TestConstructorsAndCopy();
  TestScaleUnderflow<unsigned char>();
  TestScaleUnderflow<unsigned short>();
  TestScaleUnderflow<unsigned int>();
  TestScaleUnderflow<unsigned long>();
  TestScaleUnderflow<unsigned long long>();
  TestScaleOverflow<unsigned char>();
  TestScaleOverflow<unsigned short>();
  TestScaleOverflow<unsigned int>();
  TestScaleOverflow<unsigned long>();
  TestScaleOverflow<unsigned long long>();
  return 0;
}

void TestConstructorsAndCopy() {
  ScopedPass pass("Rational::[Rational/operator=]()");
  
  Rational<unsigned int> rat;
  assert(rat.GetNumerator() == 0);
  assert(rat.GetDenominator() == 1);
  
  Rational<unsigned int> rat1(7);
  assert(rat1.GetNumerator() == 7);
  assert(rat1.GetDenominator() == 1);
  
  Rational<unsigned int> rat2(7, 2);
  assert(rat2.GetNumerator() == 7);
  assert(rat2.GetDenominator() == 2);
  
  rat = rat2;
  assert(rat.GetNumerator() == 7);
  assert(rat.GetDenominator() == 2);
}

template <typename T>
void TestScaleUnderflow() {
  ScopedPass pass("Rational<", NumericInfo<T>::name, ">::ScaleInteger"
                  " [underflow]");
  Rational<T> rat(5, 7);
  assert(rat.ScaleInteger(7) == 5);
  assert(rat.ScaleInteger(14) == 10);
  assert(rat.ScaleInteger(21) == 15);
  
  rat = Rational<T>(0, 4);
  assert(rat.ScaleInteger(10) == 0);
  assert(rat.ScaleInteger(3) == 0);
}

template <typename T>
void TestScaleOverflow() {
  ScopedPass pass("Rational<", NumericInfo<T>::name, ">ScaleInteger"
                  " [overflow]");
  Rational<T> rat(2, 2);
  T result = rat.ScaleInteger(NumericInfo<T>::max);
  assert(result >= NumericInfo<T>::max - 4);
  
  rat = Rational<T>(2, 3);
  result = rat.ScaleInteger(NumericInfo<T>::max);
  T answer = (NumericInfo<T>::max / 3) * 2;
  assert(result >= answer - 2 && result <= answer + 2);
}
