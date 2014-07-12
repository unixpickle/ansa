#include "rational.hpp"
#include "math.hpp"

namespace ansa {

template <typename T>
Rational<T>::Rational() : numerator(0), denominator(1) {
}

template <typename T>
Rational<T>::Rational(T _numerator) : numerator(_numerator), denominator(1) {
}

template <typename T>
Rational<T>::Rational(T _numerator, T _denominator)
  : numerator(_numerator), denominator(_denominator) {
}

template <typename T>
Rational<T>::Rational(const Rational<T> & rat)
  : numerator(rat.numerator), denominator(rat.denominator) {
}

template <typename T>
Rational<T> & Rational<T>::operator=(const Rational<T> & rat) {
  numerator = rat.numerator;
  denominator = rat.denominator;
  return *this;
}

template <typename T>
T Rational<T>::ScaleInteger(T number) {
  // TODO: this is probably pretty slow and not the most accurate
  
  int logNum = Log2Ceil(num);
  int logVal = Log2Ceil(val);
  int numRemoved = 0;
  T theNum = num;
  T theVal = val;
  while (logNum + logVal >= NumBits) {
    numRemoved++;
    if (theNum > theVal) {
      theNum >>= 1;
      logNum = Log2Ceil(theNum);
    } else {
      theVal >>= 1;
      logVal = Log2Ceil(theVal);
    }
  }
  return ((theNum * theVal) / denom) * ((T)1 << numRemoved);
}

template class Rational<unsigned char>;
template class Rational<unsigned short>;
template class Rational<unsigned int>;
template class Rational<unsigned long>;
template class Rational<unsigned long long>;

}
