# Abstract

ANSA provides a simple mutual-exclusion mechanism. The mechanism is more advanced than a regular spinlock which is not serialized.

## The *Lock* abstract class

The ***Lock*** class has a `Seize()` method and a `Release()` method. A lock is not recursive, so calling `Seize()` twice from the same thread (for example, in nested functions) will result in deadlock. The `Seize()` method will only return once the caller owns the lock. The `Release()` method is atomic and does not wait for some other thread to obtain the lock.

## *OrderedLock*

The ***OrderedLock*** class is a serialized spinlock. For example, if person A attempts to seize a locked *OrderedLock* and person B later attempts to seize it before person A has gotten it, person A will *always* get the lock first once it becomes free. This prevents "starvation" for highly contended locks.

## *YieldingLock*

Because ANSA assumes very little about the operating system and does not use scheduling APIs, it cannot automatically yield to other another thread if a lock is held. Instead, you must subclass the ***YieldingLock*** class and implement the `Yield()` method. When you `Seize()` a *YieldingLock*, it calls its `Yield()` method in a loop until it owns the lock.

# Locking Algorithm

When I invented this locking algorithm, I originally implemented it in [anlock](https://github.com/unixpickle/anlock).

Here is a verbatim copy of what I wrote in anlock's README to describe the algorithm:

> The algorithm used by anlock is very straightforward.

> A lock is represented as a 64-bit integer. The lower 32-bits stores the number of threads currently attempting to use the lock (including the thread that currently owns the lock). The upper 32-bits gets incremented every time the lock is released, and may rap around back to zero if the lock is heavily used.
 
> When a thread wants to seize the lock, it uses an atomic fetch-and-add instruction to increment the lock's value and get the old value (let's call the old value x). As long as less than 2^32 threads are trying to seize the lock at once, the add part of this instruction will simply increment the lower 32-bits–i.e. the threads waiting field. Now for the fun part: the seizing thread creates a 32-bit integer out of the upper half of x, and adds to this value the lower 32-bits of x. Finally, the seizing thread loops, constantly reading the new value of the lock, waiting until the upper 32-bits is the sum it just calculated. When they are equal, the lock is owned by the current thread.

> The reason that this whole proceedure works is because of the nature of unlocking. When a thread wishes to release a lock, it uses an atomic addition to increment the value of the lock by 0xffffffff. This effectively subtracts one from the threads waiting field while adding one (because of carrying) to the threads completed field.