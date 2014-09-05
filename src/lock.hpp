#ifndef __ANSA_LOCK_HPP__
#define __ANSA_LOCK_HPP__

#include <ansa/atomic>
#include <cstdint>

#ifndef __ANSA_LOCK_SIZE__
#define __ANSA_LOCK_SIZE__ 64
#endif

namespace ansa {

/**
 * An abstract lock interface.
 */
class Lock {
public:
  /**
   * Seize the lock. Waits until no other threads of execution have own the
   */
  virtual void Seize() = 0;
  
  /**
   * Release the lock atomically.
   */
  virtual void Release() = 0;
};

class OrderedLock : public Lock {
public:
  /**
   * Seize the lock by busy-waiting.
   */
  virtual void Seize();
  
  /**
   * Release the lock atomically.
   */
  virtual void Release();
  
protected:
#if __ANSA_LOCK_SIZE__ == 64
  Atomic<uint64_t> lockValue;
#elif __ANSA_LOCK_SIZE__ == 32
  Atomic<uint32_t> lockValue;
#else
#error Unknown lock size value
#endif
};

class YieldingLock : public OrderedLock {
public:
  /**
   * Like the Seize() method of the superclass, but calls Yield() periodically.
   */
  virtual void Seize();
protected:
  /**
   * Currently does nothing. You must override this in your lock class if you
   * want to make it do something else.
   */
  virtual void Yield();
};

/**
 * An easy way to seize a lock for the entirety of a function scope.
 */
class ScopedLock {
public:
  inline ScopedLock(Lock & l) : lock(l) {
    lock.Seize();
  }
  
  inline ~ScopedLock() {
    lock.Release();
  }
  
private:
  Lock & lock;
};

}

#endif
