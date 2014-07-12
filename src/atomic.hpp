#ifndef __ANSA_ATOMIC_HPP__
#define __ANSA_ATOMIC_HPP__

#include <ansa/macros>

namespace ansa {

template <typename T>
class Atomic {
protected:
  T value ANSA_ALIGNED(8);
  
public:
  Atomic();
  Atomic(const Atomic<T> & a);
  Atomic(T v);
  
  T operator=(T v);
  T operator=(T v) volatile;
  
  T operator+=(T v);
  T operator+=(T v) volatile;
  T operator-=(T v);
  T operator-=(T v) volatile;
  
  T operator--();
  T operator--() volatile;
  T operator++();
  T operator++() volatile;
  
  T operator--(int);
  T operator--(int) volatile;
  T operator++(int);
  T operator++(int) volatile;
  
  operator T() const;
  operator T() const volatile;
};

extern template class Atomic<bool>;
extern template class Atomic<unsigned char>;
extern template class Atomic<char>;
extern template class Atomic<unsigned short>;
extern template class Atomic<short>;
extern template class Atomic<unsigned int>;
extern template class Atomic<int>;
extern template class Atomic<unsigned long>;
extern template class Atomic<long>;
extern template class Atomic<unsigned long long>;
extern template class Atomic<long long>;

}

#endif
