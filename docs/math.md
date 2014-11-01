# Log2Floor()

The `Log2Floor()` function provides an efficient logarithm (base 2) routine for unsigned integer types.

**Examples:**

    Log2Floor<unsigned int>(2) == 1
    Log2Floor<unsigned int>(3) == 1
    Log2Floor<unsigned int>(5) == 2

# Log2Ceil()

This is like `Log2Floor()`, but it rounds up instead of down.

**Examples:**

    Log2Ceil<unsigned int>(2) == 1
    Log2Ceil<unsigned int>(3) == 2
    Log2Ceil<unsigned int>(5) == 3

# IsAligned()

The `IsAligned()` function checks if its first argument is divisible by its second argument. If and only if the first argument is *not* divisible by the second argument, the function returns `false`.

Neither argument needs to be a power of two. The second argument may not be zero.

**Examples**:

    IsAligned<unsigned int>(0x10, 0x8) == true
    IsAligned<unsigned int>(0x8, 0x10) == false
    IsAligned<unsigned int>(0x20, 3) == false

# IsAligned2()

Like `IsAligned()`, except that the second argument must be a power of two. This allows for faster bitwise operations on some processors.

**Examples**:

    IsAligned2<unsigned int>(0x10, 0x8) == true
    IsAligned2<unsigned int>(0x8, 0x10) == false
    IsAligned2<unsigned int>(0x100, 0x80) == true
    IsAligned2<unsigned int>(0x128, 0x8) == true
    IsAligned2<unsigned int>(0x128, 0x4) == true
    IsAligned2<unsigned int>(0x128, 0x10) == false

# Align()

The `Align()` function aligns a value by another value. The first argument is the value to align, and the second is the alignment. The result will be greater than the first argument and will be divisible by the second.

Neither argument needs to be a power of two. The second argument may not be zero.

**Examples:**

    Align<unsigned int>(14, 5) == 15
    Align<unsigned int>(15, 6) == 18
    Align<unsigned int>(8, 2) == 8

# Align2()

Like `Align()`, except the second argument must be a power of two.

**Examples:**

    Align2<unsigned int>(14, 4) == 16
    Align2<unsigned int>(0x21, 0x10) == 0x30
    Align2<unsigned int>(0x10, 4) == 0x10

# BitScanRight()

Takes a numerical argument and performs a bitscan from the least significant digit upward. Returns the index of the first non-zero bit. If you pass in zero, `BitScanRight()` will return the total number of bits that can be stored in the type of the argument.

**Examples:**

    BitScanRight<uint8_t>(0) == 8;
    BitScanRight<uint16_t>(0) == 16;
    BitScanRight<unsigned int>(3) == 0;
    BitScanRight<unsigned int>(2) == 1;
    BitScanRight<unsigned int>(4) == 2;

# Alignment()

Computes the alignment of the given argument. The argument may not be zero. The resulting alignment is always a power of two.

**Examples:**

    Alignment(0x100) == 0x100
    Alignment(0x110) == 0x10
    Alignment(17) == 0
    Alignment(18) == 2
    Alignment(0xff00) == 0x100

# IsPowerOf2()

This function's purpose should be pretty obvious. The only interesting thing is that passing zero results in a return value of `true`. The input argument must be positive (since, obviously, imaginary values cannot be returned).

**Examples:**

    IsPowerOf2(0) == true
    IsPowerOf2(1) == true
    IsPowerOf2(3) == false
    IsPowerOf2(4) == true

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

# AddWraps()

This function helps you guard your code against integer wrap-around exploits. Supposed you have two integers `a` and `b` which you'd like to add together, but you don't want the sum to wrap around. In this case, you can check `AddWraps<int>(a, b)`. When the arguments are *signed*, `AddWraps` checks for both negative and positive wraparound.

**Examples:**

    AddWraps<uint8_t>(0xff, 0) == false
    AddWraps<uint8_t>(0xff, 0x1) == true
    AddWraps<uint8_t>(0xff, 0xff) == true
    AddWraps<int8_t>(-0x10, -0x10) == false
    AddWraps<int8_t>(-0x80, -1) == true
    AddWraps<int8_t>(-0x80, -0x80) == true

# MulWraps()

This function is used like `AddWraps()`. It checks if a multiplication operation would result in integer wrap-around.

It should be noted that, for `MulWraps<int>()`, the expression `INT_MIN * -1` is considered to wrap-around, since `-INT_MIN` does not exist. This applies to the equivalent scenario for any signed type.

**Examples:**

    MulWraps<uint8_t>(-0x10, 2) == false
    MulWraps<uint8_t>(-2, -2) == false
    MulWraps<uint8_t>(-0x80, -1) == true
    MulWraps<uint8_t>(0x10, 0x10) == true
    MulWraps<uint8_t>(0x10, 0x8) == false
    MulWraps<sint8_t>(0x10, 0x8) == true

# RoundUpDiv()

This function performs integer division, but it rounds the opposite way that C-style integer division does.  In general, C-style division truncates (e.g. "5/2=2", "-5/2=-2").

One thing to note: by default, `RoundUpDiv()` will round *down* for negative division. If you pass `false` for the third, optional argument, it will round up.

**Examples:**

    RoundUpDiv<int>(4, 2) == 2
    RoundUpDiv<int>(5, 2) == 3
    RoundUpDiv<int>(5, -2) == -3
    RoundUpDiv<int>(5, -2, false) == -2
    RoundUpDiv<int>(-4, 2, false) == -2
