# ANSA

ANSA (short for <b>A</b>lex <b>N</b>ichol <b>S</b>tand <b>A</b>lone) is meant to be used as an alternative to the lofty Standard Template Library. It currently includes the following APIs:

 * Atomic type wrapper
 * A busy-wait lock mechanism based on an atomic ordered-lock algorithm
 * Functions that are usually provided by &lt;cstring&gt;
 * Integer arithmetic operations such as log<sub>2</sub>(x).
 * A rational arithmetic type
 * A Module class for dynamic dependency initialization
 * A simple base class that cannot be copied or re-assigned
 * A simple linked-list container

# Portability

ANSA is built for C++11, but does not utilize many of its features.

None of the ANSA APIs are reliant on dynamic memory allocation, the STL, exceptions, or any other advanced runtime APIs like RTTI. Instead, ANSA is made to be used as part of the implementation of such mechanisms. This makes ANSA perfect for OS kernels.

# TODO

 * Add Abs() function to the math library
 * Add a round(), floor(), and ceil() function to Rational
 * Support signed rationals
 * Implement Rational addition, multiplication, subtraction, etc.
