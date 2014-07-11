#include "atomic.hpp"

namespace ansa {

template <typename T>
Atomic<T>::Atomic() : value(0) {
}

template <typename T>  
Atomic<T>::Atomic(const Atomic<T> & a) : value((T)a) {
  value = (T)a;
}

template <typename T>
Atomic<T>::Atomic(T v) : value(v) {
}

template <typename T>
T Atomic<T>::operator=(T v) {
  __atomic_store_n(&value, v, __ATOMIC_SEQ_CST);
  return v;
}

template <typename T>
T Atomic<T>::operator=(T v) volatile {
  __atomic_store_n(&value, v, __ATOMIC_SEQ_CST);
  return v;
}

template <typename T>
T Atomic<T>::operator+=(T v) {
  return __sync_add_and_fetch(&value, v);
}

template <typename T>
T Atomic<T>::operator+=(T v) volatile {
  return __sync_add_and_fetch(&value, v);
}

template <typename T>
T Atomic<T>::operator-=(T v) {
  return __sync_sub_and_fetch(&value, v);
}

template <typename T>
T Atomic<T>::operator-=(T v) volatile {
  return __sync_sub_and_fetch(&value, v);
}

template <typename T>
T Atomic<T>::operator--() {
  return __sync_sub_and_fetch(&value, 1);
}

template <typename T>
T Atomic<T>::operator--() volatile {
  return __sync_sub_and_fetch(&value, 1);
}

template <typename T>
T Atomic<T>::operator++() {
  return __sync_add_and_fetch(&value, 1);
}

template <typename T>
T Atomic<T>::operator++() volatile {
  return __sync_add_and_fetch(&value, 1);
}

template <typename T>
T Atomic<T>::operator--(int) {
  return __sync_fetch_and_sub(&value, 1);
}

template <typename T>
T Atomic<T>::operator--(int) volatile {
  return __sync_fetch_and_sub(&value, 1);
}

template <typename T>
T Atomic<T>::operator++(int) {
  return __sync_fetch_and_add(&value, 1);
}

template <typename T>
T Atomic<T>::operator++(int) volatile {
  return __sync_fetch_and_add(&value, 1);
}

template <typename T>
Atomic<T>::operator T() const {
  return __atomic_load_n(&value, __ATOMIC_SEQ_CST);
}

template <typename T>
Atomic<T>::operator T() const volatile {
  return __atomic_load_n(&value, __ATOMIC_SEQ_CST);
}

template class Atomic<unsigned char>;
template class Atomic<char>;
template class Atomic<unsigned short>;
template class Atomic<short>;
template class Atomic<unsigned int>;
template class Atomic<int>;
template class Atomic<unsigned long>;
template class Atomic<long>;
template class Atomic<unsigned long long>;
template class Atomic<long long>;

}
