#ifndef __ANSA_MATH_HPP__
#define __ANSA_MATH_HPP__

#include <ansa/numeric-info>
#include <cassert>

namespace ansa {

template <typename T>
int Log2Floor(T value) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  assert(value != 0);
  if (sizeof(T) > sizeof(unsigned long)) {
    return NumericInfo<unsigned long long>::bitCount - __builtin_clzll(value)
        - 1;
  } else if (sizeof(T) > sizeof(unsigned int)) {
    return NumericInfo<unsigned long>::bitCount - __builtin_clzl(value) - 1;
  } else {
    return NumericInfo<unsigned int>::bitCount - __builtin_clz(value) - 1;
  }
};

template <typename T>
int Log2Ceil(T value) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  assert(value != 0);
  int floored = Log2Floor(value);
  if (((T)1 << floored) != value) {
    return floored + 1;
  } else {
    return floored;
  }
}

template <typename T>
inline bool IsAligned(T value, T alignment) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  return alignment < 2 ? true : (value % alignment) == 0;
}

template <typename T>
T Align(T value, T alignment) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  if (IsAligned(value, alignment)) {
    return value;
  } else {
    return value + (alignment - (value % alignment));
  }
}

template <typename T>
inline T Max(T one, T two) {
  return one > two ? one : two;
}

template <typename T>
inline T Min(T one, T two) {
  return one < two ? one : two;
}

template <typename T>
int BitScanRight(T value) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  if (value == 0) return NumericInfo<T>::bitCount;
  if (sizeof(T) > sizeof(unsigned long)) {
    return __builtin_ctzll(value);
  } else if (sizeof(T) > sizeof(unsigned int)) {
    return __builtin_ctzl(value);
  } else {
    return __builtin_ctz(value);
  }
}

template <typename T>
T Alignment(T value) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  assert(value != 0);
  return (T)1 << BitScanRight(value);
}

template <typename T>
bool IsPowerOf2(T value) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  if (value == 0) return true;
  return ((T)1 << BitScanRight(value)) == value;
}

}

#endif
