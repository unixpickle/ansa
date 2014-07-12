// NOTE: this file is almost entirely computer generated

#include "numeric-info.hpp"

namespace ansa {

template<>
const char * NumericInfo<char>::name = "char";
template<>
char NumericInfo<char>::max = 
  ((char)1 << (sizeof(char) * 8 - 2))
  + (((char)1 << (sizeof(char) * 8 - 2)) - 1);
template<>
char NumericInfo<char>::min = (char)1 << (sizeof(char) * 8 - 1);
template<>
bool NumericInfo<char>::isSigned = true;

template<>
const char * NumericInfo<unsigned char>::name = "unsigned char";
template<>
unsigned char NumericInfo<unsigned char>::max =
  ~(unsigned char)0;
template<>
unsigned char NumericInfo<unsigned char>::min = 0;
template<>
bool NumericInfo<unsigned char>::isSigned = false;

template<>
const char * NumericInfo<short>::name = "short";
template<>
short NumericInfo<short>::max = 
  ((short)1 << (sizeof(short) * 8 - 2))
  + (((short)1 << (sizeof(short) * 8 - 2)) - 1);
template<>
short NumericInfo<short>::min = (short)1 << (sizeof(short) * 8 - 1);
template<>
bool NumericInfo<short>::isSigned = true;

template<>
const char * NumericInfo<unsigned short>::name = "unsigned short";
template<>
unsigned short NumericInfo<unsigned short>::max =
  ~(unsigned short)0;
template<>
unsigned short NumericInfo<unsigned short>::min = 0;
template<>
bool NumericInfo<unsigned short>::isSigned = false;

template<>
const char * NumericInfo<int>::name = "int";
template<>
int NumericInfo<int>::max = 
  ((int)1 << (sizeof(int) * 8 - 2))
  + (((int)1 << (sizeof(int) * 8 - 2)) - 1);
template<>
int NumericInfo<int>::min = (int)1 << (sizeof(int) * 8 - 1);
template<>
bool NumericInfo<int>::isSigned = true;

template<>
const char * NumericInfo<unsigned int>::name = "unsigned int";
template<>
unsigned int NumericInfo<unsigned int>::max =
  ~(unsigned int)0;
template<>
unsigned int NumericInfo<unsigned int>::min = 0;
template<>
bool NumericInfo<unsigned int>::isSigned = false;

template<>
const char * NumericInfo<long>::name = "long";
template<>
long NumericInfo<long>::max = 
  ((long)1 << (sizeof(long) * 8 - 2))
  + (((long)1 << (sizeof(long) * 8 - 2)) - 1);
template<>
long NumericInfo<long>::min = (long)1 << (sizeof(long) * 8 - 1);
template<>
bool NumericInfo<long>::isSigned = true;

template<>
const char * NumericInfo<unsigned long>::name = "unsigned long";
template<>
unsigned long NumericInfo<unsigned long>::max =
  ~(unsigned long)0;
template<>
unsigned long NumericInfo<unsigned long>::min = 0;
template<>
bool NumericInfo<unsigned long>::isSigned = false;

template<>
const char * NumericInfo<long long>::name = "long long";
template<>
long long NumericInfo<long long>::max = 
  ((long long)1 << (sizeof(long long) * 8 - 2))
  + (((long long)1 << (sizeof(long long) * 8 - 2)) - 1);
template<>
long long NumericInfo<long long>::min = (long long)1 << (sizeof(long long) * 8 - 1);
template<>
bool NumericInfo<long long>::isSigned = true;

template<>
const char * NumericInfo<unsigned long long>::name = "unsigned long long";
template<>
unsigned long long NumericInfo<unsigned long long>::max =
  ~(unsigned long long)0;
template<>
unsigned long long NumericInfo<unsigned long long>::min = 0;
template<>
bool NumericInfo<unsigned long long>::isSigned = false;

}
