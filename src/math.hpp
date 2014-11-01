#ifndef __ANSA_MATH_HPP__
#define __ANSA_MATH_HPP__

#include <ansa/numeric-info>
#include <ansa/enable-if>
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
  assert(alignment != 0);
  return (value % alignment) == 0;
}

template <typename T>
inline bool IsAligned2(T value, T alignment) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  assert(alignment != 0);
  return (value & (alignment - 1)) == 0;
}

template <typename T>
T Align(T value, T alignment) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  assert(alignment != 0);
  T misalignment = value % alignment;
  if (!misalignment) {
    return value;
  } else {
    return value + (alignment - misalignment);
  }
}

template <typename T>
T Align2(T value, T alignment) {
  static_assert(!NumericInfo<T>::isSigned, "Unsupported input type");
  T misalignment = value & (alignment - 1);
  if (!misalignment) {
    return value;
  } else {
    return value + (alignment - misalignment);
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

template <typename T>
typename EnableIf<NumericInfo<T>::isSigned, bool>::type AddWraps(T v1, T v2) {
  if (v1 < 0) {
    return (T)(v2 + v1) >= v2;
  } else if (v2 < 0) {
    return (T)(v1 + v2) >= v1;
  }
  return (T)(v1 + v2) < v1;
}

template <typename T>
typename EnableIf<!NumericInfo<T>::isSigned, bool>::type AddWraps(T v1, T v2) {
  return (T)(v1 + v2) < v1;
}

template <typename T>
typename EnableIf<NumericInfo<T>::isSigned, bool>::type MulWraps(T v1, T v2) {
  if (!v1 || !v2) return false;
  // If it's -1 and the minimum value for type T, sometimes we could get a
  // machine exception since negative numbers go one lower than positive
  // numbers.
  if (v2 == -1) {
    return v1 == NumericInfo<T>::min;
  } else if (v1 == -1) {
    return v2 == NumericInfo<T>::min;
  }
  return ((T)(v1 * v2) / v2) != v1;
}

template <typename T>
typename EnableIf<!NumericInfo<T>::isSigned, bool>::type MulWraps(T v1, T v2) {
  if (!v1 || !v2) return false;
  return ((T)(v1 * v2) / v2) != v1;
}

template <typename T>
typename EnableIf<NumericInfo<T>::isSigned, T>::type
RoundUpDiv(T value1, T value2, bool roundDownNegative = true) {
  assert(value2 != 0);
  
  // Min/-1 results in an undefined number.
  assert(!(value1 == NumericInfo<T>::min && value2 == -1));
  
  if (value1 < 0 && value2 < 0) {
    if (value1 % value2) {
      return (value1 / value2) + 1;
    } else {
      return value1 / value2;
    }
  } else if (value1 < 0 || value2 < 0) {
    if (value1 % value2 && roundDownNegative) {
      return (value1 / value2) - 1;
    } else {
      return value1 / value2;
    }
  } else if (value1 % value2) {
    return (value1 / value2) + 1;
  } else {
    return value1 / value2;
  }
}

template <typename T>
typename EnableIf<!NumericInfo<T>::isSigned, T>::type
RoundUpDiv(T value1, T value2) {
  assert(value2 != 0);
  if (value1 % value2) {
    return (value1 / value2) + 1;
  } else {
    return value1 / value2;
  }
}

template <typename T>
typename EnableIf<!NumericInfo<T>::isSigned, T>::type
RoundUpDiv(T value1, T value2, bool) {
  // Ignore the roundDownNegative argument
  assert(value2 != 0);
  if (value1 % value2) {
    return (value1 / value2) + 1;
  } else {
    return value1 / value2;
  }
}

}

#endif
