#include "rational.hpp"
#include "math.hpp"
#include <cassert>

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
T Rational<T>::ScaleInteger(T val) const {
  assert(denominator != 0);
  int numRemoved = 0;
  T theNum = numerator;
  T theVal = val;
  T product = theNum * theVal;
  while (theNum > 1 && theVal > 1) {
    T bigger = theNum > theVal ? theNum : theVal;
    if (Log2Floor(product) < Log2Floor(bigger) + 1) {
      if (!(theNum & 1)) {
        theNum >>= 1;
      } else if (!(theVal & 1)) {
        theVal >>= 1;
      } else if (theNum > theVal) {
        theNum >>= 1;
      } else {
        theVal >>= 1;
      }
      ++numRemoved;
      product = theNum * theVal;
    } else break;
  }
  return (product / denominator) * ((T)1 << numRemoved);
}

template class Rational<unsigned char>;
template class Rational<unsigned short>;
template class Rational<unsigned int>;
template class Rational<unsigned long>;
template class Rational<unsigned long long>;

}
