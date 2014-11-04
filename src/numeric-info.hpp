#ifndef __ANSA_NUMERIC_INFO_HPP__
#define __ANSA_NUMERIC_INFO_HPP__

#include <cstddef>

namespace ansa {

template <typename T>
struct NumericInfo {
};

template <>
struct NumericInfo<signed char> {
  static constexpr size_t size = sizeof(signed char);
  static constexpr size_t bitCount = size * 8;
  static constexpr signed char min =
      (signed char)1 << (bitCount - 1);
  static constexpr signed char max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "signed char";
  typedef signed char SignedType;
  typedef unsigned char UnsignedType;
};

template <>
struct NumericInfo<unsigned char> {
  static constexpr size_t size = sizeof(unsigned char);
  static constexpr size_t bitCount = size * 8;
  static constexpr unsigned char max = ~(unsigned char)0;
  static constexpr unsigned char min = (unsigned char)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned char";
  typedef char SignedType;
  typedef unsigned char UnsignedType;
};

template <>
struct NumericInfo<char> {
  static constexpr bool isSigned = (char)-1 < (char)0;
  static constexpr size_t size = sizeof(char);
  static constexpr size_t bitCount = size * 8;
  static constexpr char max = isSigned ? NumericInfo<signed char>::max :
                              NumericInfo<unsigned char>::max;
  static constexpr char min = isSigned ? NumericInfo<signed char>::min :
                              NumericInfo<unsigned char>::min;
  static constexpr const char * name = "char";
  typedef signed char SignedType;
  typedef unsigned char UnsignedType;
};

template <>
struct NumericInfo<short> {
  static constexpr size_t size = sizeof(short);
  static constexpr size_t bitCount = size * 8;
  static constexpr short min =
      (short)1 << (bitCount - 1);
  static constexpr short max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "short";
  typedef short SignedType;
  typedef short UnsignedType;
};

template <>
struct NumericInfo<unsigned short> {
  static constexpr size_t size = sizeof(unsigned short);
  static constexpr size_t bitCount = size * 8;
  static constexpr unsigned short max = ~(unsigned short)0;
  static constexpr unsigned short min = (unsigned short)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned short";
  typedef short SignedType;
  typedef unsigned short UnsignedType;
};

template <>
struct NumericInfo<int> {
  static constexpr size_t size = sizeof(int);
  static constexpr size_t bitCount = size * 8;
  static constexpr int min =
      (int)1 << (bitCount - 1);
  static constexpr int max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "int";
  typedef int SignedType;
  typedef int UnsignedType;
};

template <>
struct NumericInfo<unsigned int> {
  static constexpr size_t size = sizeof(unsigned int);
  static constexpr size_t bitCount = size * 8;
  static constexpr unsigned int max = ~(unsigned int)0;
  static constexpr unsigned int min = (unsigned int)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned int";
  typedef int SignedType;
  typedef unsigned int UnsignedType;
};

template <>
struct NumericInfo<long> {
  static constexpr size_t size = sizeof(long);
  static constexpr size_t bitCount = size * 8;
  static constexpr long min =
      (long)1 << (bitCount - 1);
  static constexpr long max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "long";
  typedef long SignedType;
  typedef long UnsignedType;
};

template <>
struct NumericInfo<unsigned long> {
  static constexpr size_t size = sizeof(unsigned long);
  static constexpr size_t bitCount = size * 8;
  static constexpr unsigned long max = ~(unsigned long)0;
  static constexpr unsigned long min = (unsigned long)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned long";
  typedef long SignedType;
  typedef unsigned long UnsignedType;
};

template <>
struct NumericInfo<long long> {
  static constexpr size_t size = sizeof(long long);
  static constexpr size_t bitCount = size * 8;
  static constexpr long long min =
      (long long)1 << (bitCount - 1);
  static constexpr long long max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "long long";
  typedef long long SignedType;
  typedef long long UnsignedType;
};

template <>
struct NumericInfo<unsigned long long> {
  static constexpr size_t size = sizeof(unsigned long long);
  static constexpr size_t bitCount = size * 8;
  static constexpr unsigned long long max = ~(unsigned long long)0;
  static constexpr unsigned long long min = (unsigned long long)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned long long";
  typedef long long SignedType;
  typedef unsigned long long UnsignedType;
};

}

#endif
