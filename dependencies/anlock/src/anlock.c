#include "anlock.h"
#include <assert.h>

static uint64_t read_value_atomically(uint64_t * ptr);

void anlock_initialize(anlock_t lock) {
  *lock = 0;
}

void anlock_lock(anlock_t lock) {
  anlock_lock_waiting(lock, (void *)0, (void (*)(void * d))0);
}

void anlock_lock_waiting(anlock_t lock, void * data, void (*fn)(void * d)) {
  assert(!((uintptr_t)lock & 7));
  uint64_t oldValue = __sync_fetch_and_add(lock, 1);
  uint32_t lower = (uint32_t)(oldValue & 0xffffffffL);
  if (!lower) return; // we have seized the lock first!
  
  uint32_t upper = (uint32_t)(oldValue >> 32L);
  uint32_t waitUntil = (uint32_t)(upper + lower);
  while (1) {
    uint64_t nowUpper = read_value_atomically(lock) >> 32L;
    if (nowUpper == (uint64_t)waitUntil) return;
    if (fn) fn(data);
#if defined(__X86_64__) || defined(__amd64)
    // clear the pipeline to increase lock performance
    __asm__ __volatile__("pause" : : : "memory");
#endif
  }
}

void anlock_unlock(anlock_t lock) {
  __sync_add_and_fetch(lock, 0xffffffff);
}

static uint64_t read_value_atomically(uint64_t * ptr) {
  // TODO: on intel, this will automatically be atomic
  return __sync_fetch_and_add(ptr, 0);
}
