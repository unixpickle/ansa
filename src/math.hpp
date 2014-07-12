#ifndef __ANSA_MATH_HPP__
#define __ANSA_MATH_HPP__

namespace ansa {

template <typename T>
int Log2Floor(T value) {
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
  int floored = Log2Floor(value);
  if (((T)1 << floored) != value) {
    return floored + 1;
  } else {
    return floored;
  }
}

}

#endif
