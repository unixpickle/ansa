# ANSA

ANSA (short for **A**lex **N**ichol **S**tand **A**lone) is meant to be used as an alternative to the lofty Standard Template Library. It currently includes the following APIs:

 * A busy-wait lock mechanism based on [anlock](http://github.com/unixpickle/anlock)
 * Atomic type wrapper
 * Functions that are usually provided by &lt;cstring&gt;
 * Integer arithmetic operations such as log<sub>2</sub>(x).
 * A rational arithmetic type
 * A Module class for dynamic dependency initialization

# Portable

ANSA is built for C++11, but does not utilize many of its features.

None of the ANSA APIs are reliant on dynamic memory allocation, the STL, exceptions, or any other advanced runtime APIs like RTTI. Instead, ANSA is made to be used as part of the implementation of such mechanisms. This makes ANSA perfect for OS kernels.
