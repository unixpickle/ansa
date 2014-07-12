#ifndef __ANSA_NUMERIC_INFO_HPP__
#define __ANSA_NUMERIC_INFO_HPP__

namespace ansa {

template <typename T>
struct NumericInfo {
  static const int size = sizeof(T);
  static const int bitCount = sizeof(T) * 8;
  
  static T max;
  static T min;
  static const char * name;
  static bool isSigned;
};

template<>
const char * NumericInfo<char>::name;
template<>
char NumericInfo<char>::min;
template<>
char NumericInfo<char>::max;
template<>
bool NumericInfo<char>::isSigned;

template<>
const char * NumericInfo<unsigned char>::name;
template<>
unsigned char NumericInfo<unsigned char>::min;
template<>
unsigned char NumericInfo<unsigned char>::max;
template<>
bool NumericInfo<unsigned char>::isSigned;

template<>
const char * NumericInfo<short>::name;
template<>
short NumericInfo<short>::min;
template<>
short NumericInfo<short>::max;
template<>
bool NumericInfo<short>::isSigned;

template<>
const char * NumericInfo<unsigned short>::name;
template<>
unsigned short NumericInfo<unsigned short>::min;
template<>
unsigned short NumericInfo<unsigned short>::max;
template<>
bool NumericInfo<unsigned short>::isSigned;

template<>
const char * NumericInfo<int>::name;
template<>
int NumericInfo<int>::min;
template<>
int NumericInfo<int>::max;
template<>
bool NumericInfo<int>::isSigned;

template<>
const char * NumericInfo<unsigned int>::name;
template<>
unsigned int NumericInfo<unsigned int>::min;
template<>
unsigned int NumericInfo<unsigned int>::max;
template<>
bool NumericInfo<unsigned int>::isSigned;

template<>
const char * NumericInfo<long>::name;
template<>
long NumericInfo<long>::min;
template<>
long NumericInfo<long>::max;
template<>
bool NumericInfo<long>::isSigned;

template<>
const char * NumericInfo<unsigned long>::name;
template<>
unsigned long NumericInfo<unsigned long>::min;
template<>
unsigned long NumericInfo<unsigned long>::max;
template<>
bool NumericInfo<unsigned long>::isSigned;

template<>
const char * NumericInfo<long long>::name;
template<>
long long NumericInfo<long long>::min;
template<>
long long NumericInfo<long long>::max;
template<>
bool NumericInfo<long long>::isSigned;

template<>
const char * NumericInfo<unsigned long long>::name;
template<>
unsigned long long NumericInfo<unsigned long long>::min;
template<>
unsigned long long NumericInfo<unsigned long long>::max;
template<>
bool NumericInfo<unsigned long long>::isSigned;

}

#endif
