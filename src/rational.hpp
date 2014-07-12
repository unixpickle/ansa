#ifndef __ANSA_RATIONAL_HPP__
#define __ANSA_RATIONAL_HPP__

#include "numeric-info.hpp"

namespace ansa {

template <typename T>
class Rational {
public:
  static const int NumBits = sizeof(T) * 8;
  
  Rational();
  Rational(T numerator);
  Rational(T numerator, T denominator);
  Rational(const Rational<T> & rat);
  
  Rational & operator=(const Rational<T> & rat);
  
  T ScaleInteger(T number);
  
private:
  T numerator;
  T denominator;
};

extern template class Rational<unsigned char>;
extern template class Rational<unsigned short>;
extern template class Rational<unsigned int>;
extern template class Rational<unsigned long>;
extern template class Rational<unsigned long long>;

}

#endif
