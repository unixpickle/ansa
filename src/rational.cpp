#include "rational.hpp"
#include "math.hpp"
#include <cassert>
#include <cstdint>

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
  // the optimizer should get the result of this if-statement at compile time
  if (sizeof(T) == 1) {
    uint16_t product = (uint16_t)numerator * (uint16_t)val;
    return (T)(product / (uint16_t)denominator);
  } else if (sizeof(T) == 2) {
    uint32_t product = (uint32_t)numerator * (uint32_t)val;
    return (T)(product / (uint32_t)denominator);
  } else if (sizeof(T) <= 4) {
    uint64_t product = (uint64_t)numerator * (uint64_t)val;
    return (T)(product / (uint64_t)denominator);
#if defined(__X86_64__) || defined(__amd64)
  } else if (sizeof(T) <= 8) {
    // do 128 bit division courtesy of Intel :)
    uint64_t result;
    __asm__("mulq %%rdx\n"
            "divq %%rcx"
            : "=a" (result)
            : "d" (val), "a" (numerator), "c" (denominator));
    return result;
#endif
  } else {
    // TODO: possibly add support for x64 assembly to speed things up
    int numRemoved = 0;
    T theNum = numerator;
    T theVal = val;
    T product = theNum * theVal;
    while (theNum > 1 && theVal > 1) {
      T bigger = theNum > theVal ? theNum : theVal;
      if (Log2Floor(product) < Log2Floor(bigger) + 1) {
        if (!(theNum % denominator)) {
          theNum >>= 1;
        } else if (!(theVal % denominator)) {
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
}

template class Rational<unsigned char>;
template class Rational<unsigned short>;
template class Rational<unsigned int>;
template class Rational<unsigned long>;
template class Rational<unsigned long long>;

}
