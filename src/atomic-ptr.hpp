#ifndef __ANSA_ATOMIC_PTR_HPP__
#define __ANSA_ATOMIC_PTR_HPP__

#include <cstdint>

namespace ansa {

template <class T, int MemModel = __ATOMIC_SEQ_CST>
class AtomicPtr {
protected:
  uintptr_t value;
  
public:  
  AtomicPtr() : value(0) {}
  AtomicPtr(T * v) : value((uintptr_t)v) {}
  
  AtomicPtr(const AtomicPtr<T> & a) = delete;
  AtomicPtr & operator=(const AtomicPtr &) = delete;
  
  inline T * operator=(T * v) {
    __atomic_store_n(&value, (uintptr_t)v, MemModel);
    return v;
  }
  
  inline T * operator=(T * v) volatile {
    __atomic_store_n(&value, (uintptr_t)v, MemModel);
    return v;
  }
  
  inline T * operator+=(size_t count) {
    return (T *)__sync_add_and_fetch(&value, (uintptr_t)(count * sizeof(T)));
  }
  
  inline T * operator+=(size_t count) volatile {
    return (T *)__sync_add_and_fetch(&value, (uintptr_t)(count * sizeof(T)));
  }
  
  inline T * operator-=(size_t count) {
    return (T *)__sync_sub_and_fetch(&value, (uintptr_t)(count * sizeof(T)));
  }
  
  inline T * operator-=(size_t count) volatile {
    return (T *)__sync_sub_and_fetch(&value, (uintptr_t)(count * sizeof(T)));
  }
  
  inline T * operator--() {
    return (T *)__sync_sub_and_fetch(&value, (uintptr_t)sizeof(T));
  }
  
  inline T * operator--() volatile {
    return (T *)__sync_sub_and_fetch(&value, (uintptr_t)sizeof(T));
  }
  
  inline T * operator++() {
    return (T *)__sync_add_and_fetch(&value, (uintptr_t)sizeof(T));
  }
  
  inline T * operator++() volatile {
    return (T *)__sync_add_and_fetch(&value, (uintptr_t)sizeof(T));
  }
  
  inline T * operator--(int) {
    return (T *)__sync_fetch_and_sub(&value, (uintptr_t)sizeof(T));
  }
  
  inline T * operator--(int) volatile {
    return (T *)__sync_fetch_and_sub(&value, (uintptr_t)sizeof(T));
  }
  
  inline T * operator++(int) {
    return (T *)__sync_fetch_and_add(&value, (uintptr_t)sizeof(T));
  }
  
  inline T * operator++(int) volatile {
    return (T *)__sync_fetch_and_add(&value, (uintptr_t)sizeof(T));
  }
  
  inline operator T *() const {
    return (T *)__atomic_load_n(&value, MemModel);
  }
  
  inline operator T() const volatile {
    return (T *)__atomic_load_n(&value, MemModel);
  }
};

}

#endif
