#ifndef __ANSA_BIT_LIST_HPP__
#define __ANSA_BIT_LIST_HPP__

#include <cstddef>
#include <cassert>

namespace ansa {

template <size_t BitCount>
class BitList {
public:
  static const size_t ByteCount = BitCount / 8 + (BitCount % 8 != 0 ? 1 : 0);
  
  class Reference {
  public:
    operator bool() const {
      return ((*ptr) & (1 << offset)) != 0;
    }
    
    Reference & operator=(bool value) {
      if (value) {
        *ptr |= 1 << offset;
      } else {
        *ptr &= ~((unsigned char)(1 << offset));
      }
      return *this;
    }
    
  protected:
    friend class BitList;
    
    Reference(unsigned char * a, unsigned char b)
      : ptr(a), offset(b) {
    }
    
    unsigned char * ptr;
    unsigned char offset;
  };
  
  BitList() {
  }
  
  BitList(bool setValue) {
    for (size_t i = 0; i < ByteCount; i++) {
      list[i] = setValue ? 0xff : 0;
    }
  }
  
  bool operator[](size_t idx) const {
    assert(idx < BitCount);
    size_t byteIndex = idx / 8;
    size_t bitIndex = idx % 8;
    return (list[byteIndex] & (1 << bitIndex)) != 0;
  }
  
  Reference operator[](size_t idx) {
    assert(idx < BitCount);
    size_t byteIndex = idx / 8;
    size_t bitIndex = idx % 8;
    return Reference(&list[byteIndex], bitIndex);
  }
  
private:
  unsigned char list[ByteCount];
};

}

#endif
