# ANSA

ANSA (short for **A**lex **N**ichol **S**tand **A**lone) is meant to be used as an alternative to the lofty Standard Template Library. I plan to implement the following APIs:

 * A busy-wait lock mechanism based on [anlock](http://github.com/unixpickle/anlock)
 * Simple atomic type wrapper
 * Functions that are usually provided by &lt;cstring&gt;
 * Integer arithmetic operations such as log2(int).
 * A rational arithmetic type
 * A Module class for dynamic dependency initialization

# Restrictions

None of the ANSA APIs are reliant on dynamic memory allocation, the STL, exceptions, or any other advanced runtime APIs like RTTI. Instead, ANSA is made to work as part of an implementation of such mechanisms. This makes ANSA perfect for OS kernels.
