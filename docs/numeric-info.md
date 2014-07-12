# Abstract

C++ templates allows compile-time information to be stored about various types in the language. ANSA utilizes templates to provide your code with information on integral types.

For example, you may get the name of an integer type as a C-style string using `NumericInfo<someType>::name`. This may help you determine information about a type passed as a template argument to one of your own functions.

## Fields

The `NumericInfo<T>` class contains the following information about an integer type:

**The size of the type in both bytes and bits:**

    static const int size = sizeof(T);
    static const int bitCount = sizeof(T) * 8;

**The maximum and minimum values that the type may hold:**

    static T max;
    static T min;

**The human-readable name of the type:**

    static const char * name;

**Whether or not the type is signed:**

    static bool isSigned;

## Example uses

The ANSA tests use numeric info quite a bit. For example, the logarithm tests use it to print the human-readable name for a template parameter:

	template <typename T>
	void TestLogFloor() {
	  ScopedPass pass("Testing Log2Floor<", NumericInfo<T>::name, ">");
	  ...
	}
