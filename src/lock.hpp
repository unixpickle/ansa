#ifndef __ANSA_LOCK_HPP__
#define __ANSA_LOCK_HPP__

#include <ansa/macros>
#include <cstdint>

namespace ansa {

class Lock {
public:
  /**
   * Seize the lock by busy-waiting.
   */
  virtual void Seize();
  
  /**
   * Release the lock atomically.
   */
  virtual void Release();
  
  /**
   * Like Seize(), but will periodically call Yield() on this lock.
   */
  virtual void SeizeYielding();
  
protected:
  /**
   * Currently does nothing. You must override this in your lock class if you
   * want to make it do something else.
   */
  virtual void Yield();
  
  /**
   * Casts lockPtr to a Lock * and calls Yield() on it.
   */
  static void CallYield(void * lockPtr);
  
private:
  uint64_t lockValue ANSA_ALIGNED(8) = 0;
};

}

#endif
