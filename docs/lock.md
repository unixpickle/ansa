# Abstract

ANSA provides a simple mutual-exclusion mechanism. The mechanism is more advanced than a regular spinlock which is not serialized.

## The *Lock* abstract class

The ***Lock*** class has a `Seize()` method and a `Release()` method. A lock is not recursive, so calling `Seize()` twice from the same thread (for example, in nested functions) will result in deadlock. The `Seize()` method will only return once the caller owns the lock. The `Release()` method is atomic and does not wait for some other thread to obtain the lock.

## *OrderedLock*

The ***OrderedLock*** class is a serialized spinlock. For example, if person A attempts to seize a locked *OrderedLock* and person B later attempts to seize it before person A has gotten it, person A will *always* get the lock first once it becomes free. This prevents "starvation" for highly contended locks.

## *YieldingLock*

Because ANSA assumes very little about the operating system and does not use scheduling APIs, it cannot automatically yield to other another thread if a lock is held. Instead, you must subclass the ***YieldingLock*** class and implement the `Yield()` method. When you `Seize()` a *YieldingLock*, it calls its `Yield()` method in a loop until it owns the lock.
