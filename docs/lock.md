# Abstract

ANSA provides a simple lock mechanism. This lock is more advanced than a regular spinlock which is not serialized. Instead, for example, if person A attempts to seize a locked lock and person B then attempts to seize it before person A gets it, person A will *always* get the lock first once it becomes free. This prevents starvation for highly contended locks.

## Basic locking

The Lock class has a `Seize()` method and a `Release()` method. A lock is not recursive, so calling `Seize()` twice from the same thread (for example, in nested functions) will result in deadlock. The `Seize()` method will only return once the caller owns the lock. The `Release()` method is atomic and does not wait for some other thread to obtain the lock.

## Yielding

Because ANSA assumes very little about the operating system and does not use scheduling APIs, it cannot automatically yield to other another thread if a lock is held. Instead, you must subclass the `Lock` class and implement the `Yield()` method. Then, to seize the lock using the `Yield()` function you overloaded, you must call `SeizeYielding()` on the lock.
