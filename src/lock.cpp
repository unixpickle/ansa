#include "lock.hpp"

extern "C" {

#include "../dependencies/anlock/src/anlock.h"

}

namespace ansa {

void Lock::Seize() {
  anlock_lock(&lockValue);
}

void Lock::Release() {
  anlock_unlock(&lockValue);
}

void Lock::SeizeYielding() {
  anlock_lock_waiting(&lockValue, reinterpret_cast<void *>(this),
                      &Lock::CallYield);
}

void Lock::Yield() {  
}

void Lock::CallYield(void * lockPtr) {
  reinterpret_cast<Lock *>(lockPtr)->Yield();
}

}
