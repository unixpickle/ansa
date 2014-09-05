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
   * Like Seize(), but will periodically call Yield() on this lock.
   */
  virtual void SeizeYielding();
  
protected:
  /**
   * Currently does nothing. You must override this in your lock class if you
   * want to make it do something else.
   */
  virtual void Yield();
};

}

#endif
