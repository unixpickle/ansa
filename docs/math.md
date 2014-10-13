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

**Examples**:

    IsAligned<unsigned int>(0x10, 0x8) == true
    IsAligned<unsigned int>(0x8, 0x10) == false
    IsAligned<unsigned int>(0x20, 3) == false

# Align()

The `Align()` function aligns a value by another value. The first argument is the value to align, and the second is the alignment. The result will be greater than the first argument and will be divisible by the second.

**Examples:**

    Align<unsigned int>(14, 5) == 15
    Align<unsigned int>(15, 6) == 18
    Align<unsigned int>(8, 2) == 8

# BitScanRight()

Takes a numerical argument and performs a bitscan from the least significant digit upward. Returns the index of the first non-zero bit. If you pass in zero, `BitScanRight()` will return the total number of bits that can be stored in the type of the argument.

**Examples:**

    BitScanRight<uint8_t>(0) == 8;
    BitScanRight<uint16_t>(0) == 16;
    BitScanRight<unsigned int>(3) == 0;
    BitScanRight<unsigned int>(2) == 1;
    BitScanRight<unsigned int>(4) == 2;

# Alignment()

Computes the alignment of the given argument. The argument may not be zero.

**Examples:**

    Alignment<unsigned int>(0x100) == 0x100
    Alignment<unsigned int>(0x110) == 0x10
    Alignment<unsigned int>(17) == 0
    Alignment<unsigned int>(18) == 2
    Alignment<unsigned int>(0xff00) == 0x100

# IsPowerOf2()

What this function does should be pretty obvious. Passing zero results in a return value of `true`.

**Examples:**

    IsPowerOf2<unsigned int>(0) == true
    IsPowerOf2<unsigned int>(1) == true
    IsPowerOf2<unsigned int>(3) == false
    IsPowerOf2<unsigned int>(4) == true

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

    AddWraps<unsigned char>(0xff, 0) == false
    AddWraps<unsigned char>(0xff, 0x1) == true
    AddWraps<unsigned char>(0xff, 0xff) == true
    AddWraps<char>(-0x10, -0x10) == false
    AddWraps<char>(-0x80, -1) == true
    AddWraps<char>(-0x80, -0x80) == true
