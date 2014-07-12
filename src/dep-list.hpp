#ifndef __ANSA_DEP_LIST_HPP__
#define __ANSA_DEP_LIST_HPP__

#include <cassert>

namespace ansa {

class Module;

/**
 * A "dynamic length" dependency list. This makes it easier to return values
 * from Module overloads.
 */
struct DepList {
  static const int MaxDeps = 0x10;
  
  Module * modules[MaxDeps];
  int count = 0;
  
  template <typename... Args>
  DepList(Args... args) : count(0) {
    SetArgs(args...);
  }
  
  DepList(const DepList & list) {
    *this = list;
  }
  
  DepList & operator=(const DepList & list) {
    count = list.count;
    for (int i = 0; i < count; i++) {
      modules[i] = list.modules[i];
    }
    return *this;
  }
  
  Module *& operator[](int idx) {
    return modules[idx];
  }
  
private:
  template <typename T, typename... Args>
  void SetArgs(T anArg, Args... args) {
    assert(count < MaxDeps);
    modules[count++] = anArg;
    SetArgs(args...);
  }
  
  void SetArgs() {
  }
};

}

#endif
