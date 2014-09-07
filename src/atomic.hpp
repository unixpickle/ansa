#ifndef __ANSA_ATOMIC_HPP__
#define __ANSA_ATOMIC_HPP__

namespace ansa {

template <typename T, int MemModel = __ATOMIC_SEQ_CST>
class Atomic {
protected:
  // By default, structure packing in the ABI should automatically align the
  // variable correctly.
  T value;
  
public:
  Atomic() : value(0) {}
  Atomic(T v) : value(v) {}
  
  Atomic(const Atomic<T> & a) = delete;
  Atomic & operator=(const Atomic &) = delete;
  
  inline T operator=(T v) {
    __atomic_store_n(&value, v, MemModel);
    return v;
  }
  
  inline T operator=(T v) volatile {
    __atomic_store_n(&value, v, MemModel);
    return v;
  }
  
  inline T operator+=(T v) {
    return __sync_add_and_fetch(&value, v);
  }
  
  inline T operator+=(T v) volatile {
    return __sync_add_and_fetch(&value, v);
  }
  
  inline T operator-=(T v) {
    return __sync_sub_and_fetch(&value, v);
  }
  
  inline T operator-=(T v) volatile {
    return __sync_sub_and_fetch(&value, v);
  }
  
  inline T operator--() {
    return __sync_sub_and_fetch(&value, 1);
  }
  
  inline T operator--() volatile {
    return __sync_sub_and_fetch(&value, 1);
  }
  
  inline T operator++() {
    return __sync_add_and_fetch(&value, 1);
  }
  
  inline T operator++() volatile {
    return __sync_add_and_fetch(&value, 1);
  }
  
  inline T operator--(int) {
    return __sync_fetch_and_sub(&value, 1);
  }
  
  inline T operator--(int) volatile {
    return __sync_fetch_and_sub(&value, 1);
  }
  
  inline T operator++(int) {
    return __sync_fetch_and_add(&value, 1);
  }
  
  inline T operator++(int) volatile {
    return __sync_fetch_and_add(&value, 1);
  }
  
  inline operator T() const {
    return __atomic_load_n(&value, MemModel);
  }
  
  inline operator T() const volatile {
    return __atomic_load_n(&value, MemModel);
  }
};

}

#endif
