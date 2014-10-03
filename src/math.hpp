#ifndef __ANSA_MATH_HPP__
#define __ANSA_MATH_HPP__

#include <cassert>

namespace ansa {

template <typename T>
int Log2Floor(T value) {
  assert(value != 0);
  if (sizeof(T) > sizeof(unsigned long)) {
    return sizeof(unsigned long long) * 8 - __builtin_clzll(value) - 1;
  } else if (sizeof(T) > sizeof(unsigned int)) {
    return sizeof(unsigned long) * 8 - __builtin_clzl(value) - 1;
  } else {
    return sizeof(unsigned int) * 8 - __builtin_clz(value) - 1;
  }
};

template <typename T>
int Log2Ceil(T value) {
  assert(value != 0);
  int floored = Log2Floor(value);
  if (((T)1 << floored) != value) {
    return floored + 1;
  } else {
    return floored;
  }
}

template <typename T>
T Align(T value, T alignment) {
  if (value % alignment) {
    return value + (alignment - (value % alignment));
  }
  return value;
}

template <typename T>
inline T Max(T one, T two) {
  return one > two ? one : two;
}

template <typename T>
inline T Min(T one, T two) {
  return one < two ? one : two;
}

}

#endif
