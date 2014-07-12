# Abstract

Many CPUs provide instructions for adding, subtracting, or even exchanging values atomically. The C++ Standard Template Library provides an `atomic<T>` wrapper that abstracts away this functionality. The ANSA atomic API uses a very similar tactic.

## Usage

You may declare an atomic variable like you would a regular variable. Here's an example of how you could declare an atomic `int`:

    Atomic<int> myNumber;

You can increment/decrement `myNumber` using the `++`/`--` prefix/postfix operators. Operators on an `Atomic<T>` will always return a value of type `T`, as you would expect. This means you can do things like the following:

    Atomic<int> myNumber = 3;
    while (--myNumber) {
        // ... something here ...
    }

Additionally, an atomic value supports the cast operator, so we could cast `myNumber` to an `int` with `(int)myNumber`.

## Volatile

I am not sure why you'd ever need to declare an `Atomic<T>` to be volatile, but I guess you can.
