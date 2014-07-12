#ifndef __ANSA_MODULE_HPP__
#define __ANSA_MODULE_HPP__

#include "dep-list.hpp"
#include "atomic.hpp"

namespace ansa {

class Module {
public:
  Module();
  Module(const Module &) = delete;
  Module(Module &&) = delete;
  Module & operator=(const Module &) = delete;
  Module & operator=(Module &&) = delete;
  
  virtual void Load();
  virtual bool IsUninitialized();
  virtual bool IsInitialized();
  
protected:
  /**
   * Overload this method for module-specific initialization.
   */
  virtual void Initialize() {}
  
  /**
   * Return a list of dependencies. This method is pure virtual so that you do
   * not forget to add such a list.
   */
  virtual DepList GetDependencies() = 0;
  
  /**
   * Optionally, return dependencies that must be loaded right after this
   * Module before this Module's Load() returns and IsInitialized() becomes
   * true.
   */
  virtual DepList GetSuperDependencies();
  
private:
  Atomic<int> loadStartCount;
  Atomic<bool> doneInit;
};

}

#endif
