#include "lock.hpp"

namespace ansa {

#if __ANSA_LOCK_SIZE__ == 64
typedef uint64_t LockInt;
typedef uint32_t LockHalfInt;
static const uint64_t LowerMask = 0xffffffff;
static const int HalfShift = 32;
#elif __ANSA_LOCK_SIZE__ == 32
typedef uint32_t LockInt;
typedef uint16_t LockHalfInt;
static const uint32_t LowerMask = 0xffff;
static const int HalfShift = 16;
#else
#error Unknown lock size value
#endif

void OrderedLock::Seize() {
  LockInt oldValue = lockValue++;
  LockHalfInt lower = (LockHalfInt)(oldValue & LowerMask);
  if (!lower) return; // we have seized the lock
  
  LockHalfInt upper = (LockHalfInt)(oldValue >> HalfShift);
  LockHalfInt waitUntil = (LockHalfInt)(upper + lower);
  while (1) {
    LockHalfInt currentUpper = (LockHalfInt)(lockValue >> HalfShift);
    if (currentUpper == waitUntil) return;
#if defined(__X86_64__) || defined(__amd64)
    // clear the pipeline to increase lock performance
    __asm__ __volatile__("pause" : : : "memory");
#endif
  }
}

void OrderedLock::Release() {
  lockValue += LowerMask;
}

void YieldingLock::Seize() {
  LockInt oldValue = lockValue++;
  LockHalfInt lower = (LockHalfInt)(oldValue & LowerMask);
  if (!lower) return; // we have seized the lock
  
  LockHalfInt upper = (LockHalfInt)(oldValue >> HalfShift);
  LockHalfInt waitUntil = (LockHalfInt)(upper + lower);
  while (1) {
    LockHalfInt currentUpper = (LockHalfInt)(lockValue >> HalfShift);
    if (currentUpper == waitUntil) return;
    Yield();
  }
}

void YieldingLock::Yield() {
}

}
