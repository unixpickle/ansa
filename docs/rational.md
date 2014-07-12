# Abstract

Occasionally, you may find yourself with no floating-point support. An example is in an OS kernel where enabling an instruction set like SSE would cause a performance hit. Without floating points, it is difficult to perform some forms of unit conversion.

Suppose, for example, that you know your hardware clock ticks 1,130,000,000 times per second. You may wish to convert a time from hardware clock ticks to microseconds at runtime. To do this, you *could* use the fraction formula:

    (tick count) * (microseconds per second) / (hardware ticks per second)

However, to do this accurately you would need to multiply *tick count* by *microseconds per second* before dividing by *hardware ticks per second*. In some cases, this is fine, but in others the product might overflow the 64-bit boundary and the resulting answer would be incorrect.

## Using a Rational<T>

You may create a Rational that wraps any unsigned integral type, but it is only really useful for the largest int type, `long long` (for smaller types, conversion is easy because you can temporarily cast to a larger type).

You may use `Rational<long long>` as follows to perform the conversion described as an example above:

    long long tickCount = // ... some way of reading hardware clock
    Rational<long long> rat(1000000, 1130000000);
    long long microCount = rat.ScaleInteger(tickCount);

## TODO: Optimization

In the future, I will use inline assembly to greatly improve the performance of `Rational<T>` on certain architectures. For now, it'll just be a little slow.
