# Log2Floor()

The `Log2Floor()` function provides an efficient logarithm (base 2) routine for integer types.

**Examples:**

    Log2Floor(2) == 1
    Log2Floor(3) == 1
    Log2Floor(5) == 2

# Log2Ceil()

This is like `Log2Floor()`, but it rounds up instead of down

**Examples:**

    Log2Ceil(2) == 1
    Log2Ceil(3) == 2
    Log2Ceil(5) == 3

# Align()

The `Align()` function aligns a value by another value. The first argument is the value to align, and the second is the alignment. The result will be greater than the first argument and will be divisible by the second.

**Examples:**

    Align(14, 5) == 15
    Align(15, 6) == 18
    Align(8, 2) == 8

# Min()

Returns the smaller of the two arguments. This function works for any comparable type, not just integers.

**Examples:**

    Min(3, 2) == 2
    Min(-2, 0) == -2
    Min(-2, -2) == -2
    Min(-2, -3) == -3

# Max()

Returns the greater of the two arguments. This function works for any comparable type, not just integers.

**Examples:**

    Max(3, 2) == 3
    Max(-2, 0) == 0
    Max(-2, -2) == -2
    Max(-2, -3) == -2
