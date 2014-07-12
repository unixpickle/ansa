#ifndef __ANSA_NUMERIC_INFO_HPP__
#define __ANSA_NUMERIC_INFO_HPP__

namespace ansa {

template <typename T>
struct NumericInfo {
  static const int size = sizeof(T);
  static const int bitCount = sizeof(T) * 8;
  
  static const char * name;
  static bool isSigned;
};

template<>
const char * NumericInfo<char>::name = "char";
template<>
bool NumericInfo<char>::isSigned = true;

template<>
const char * NumericInfo<unsigned char>::name = "unsigned char";
template<>
bool NumericInfo<unsigned char>::isSigned = false;

template<>
const char * NumericInfo<short>::name = "short";
template<>
bool NumericInfo<short>::isSigned = true;

template<>
const char * NumericInfo<unsigned short>::name = "unsigned short";
template<>
bool NumericInfo<unsigned short>::isSigned = false;

template<>
const char * NumericInfo<int>::name = "int";
template<>
bool NumericInfo<int>::isSigned = true;

template<>
const char * NumericInfo<unsigned int>::name = "unsigned int";
template<>
bool NumericInfo<unsigned int>::isSigned = false;

template<>
const char * NumericInfo<long>::name = "long";
template<>
bool NumericInfo<long>::isSigned = true;

template<>
const char * NumericInfo<unsigned long>::name = "unsigned long";
template<>
bool NumericInfo<unsigned long>::isSigned = false;

template<>
const char * NumericInfo<long long>::name = "long long";
template<>
bool NumericInfo<long long>::isSigned = true;

template<>
const char * NumericInfo<unsigned long long>::name = "unsigned long long";
template<>
bool NumericInfo<unsigned long long>::isSigned = false;

}

#endif
