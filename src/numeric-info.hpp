#ifndef __ANSA_NUMERIC_INFO_HPP__
#define __ANSA_NUMERIC_INFO_HPP__

namespace ansa {

template <typename T>
struct NumericInfo {
};

template <>
struct NumericInfo<char> {
  static constexpr int size = sizeof(char);
  static constexpr int bitCount = size * 8;
  static constexpr char min =
      (char)1 << (bitCount - 1);
  static constexpr char max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "char";
};
  
template <>
struct NumericInfo<unsigned char> {
  static constexpr int size = sizeof(unsigned char);
  static constexpr int bitCount = size * 8;
  static constexpr unsigned char max = ~(unsigned char)0;
  static constexpr unsigned char min = (unsigned char)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned char";
};
  
template <>
struct NumericInfo<short> {
  static constexpr int size = sizeof(short);
  static constexpr int bitCount = size * 8;
  static constexpr short min =
      (short)1 << (bitCount - 1);
  static constexpr short max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "short";
};
  
template <>
struct NumericInfo<unsigned short> {
  static constexpr int size = sizeof(unsigned short);
  static constexpr int bitCount = size * 8;
  static constexpr unsigned short max = ~(unsigned short)0;
  static constexpr unsigned short min = (unsigned short)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned short";
};
  
template <>
struct NumericInfo<int> {
  static constexpr int size = sizeof(int);
  static constexpr int bitCount = size * 8;
  static constexpr int min =
      (int)1 << (bitCount - 1);
  static constexpr int max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "int";
};
  
template <>
struct NumericInfo<unsigned int> {
  static constexpr int size = sizeof(unsigned int);
  static constexpr int bitCount = size * 8;
  static constexpr unsigned int max = ~(unsigned int)0;
  static constexpr unsigned int min = (unsigned int)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned int";
};
  
template <>
struct NumericInfo<long> {
  static constexpr int size = sizeof(long);
  static constexpr int bitCount = size * 8;
  static constexpr long min =
      (long)1 << (bitCount - 1);
  static constexpr long max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "long";
};
  
template <>
struct NumericInfo<unsigned long> {
  static constexpr int size = sizeof(unsigned long);
  static constexpr int bitCount = size * 8;
  static constexpr unsigned long max = ~(unsigned long)0;
  static constexpr unsigned long min = (unsigned long)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned long";
};
  
template <>
struct NumericInfo<long long> {
  static constexpr int size = sizeof(long long);
  static constexpr int bitCount = size * 8;
  static constexpr long long min =
      (long long)1 << (bitCount - 1);
  static constexpr long long max = -(min + 1);
  static constexpr bool isSigned = true;
  static constexpr const char * name = "long long";
};
  
template <>
struct NumericInfo<unsigned long long> {
  static constexpr int size = sizeof(unsigned long long);
  static constexpr int bitCount = size * 8;
  static constexpr unsigned long long max = ~(unsigned long long)0;
  static constexpr unsigned long long min = (unsigned long long)0;
  static constexpr bool isSigned = false;
  static constexpr const char * name = "unsigned long long";
};

}

#endif
