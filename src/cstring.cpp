#include "cstring.hpp"

namespace ansa {

size_t Strlen(const char * str) {
  size_t size = 0;
  while (str[size]) {
    size++;
  }
  return size;
}

void * Memset(void * ptr, char value, size_t size) {
  char * dest = (char *)ptr;
  while (size--) {
    *(dest++) = value;
  }
  return ptr;
}

void Bzero(void * ptr, size_t size) {
  // TODO: here, optimize this using larger chunks and maybe rep stosq on x64.
  Memset(ptr, 0, size);
}

void Memcpy(void * _dest, const void * _src, size_t size) {
  char * dest = (char *)_dest;
  const char * src = (char *)_src;
  for (size_t i = 0; i < size; i++) {
    dest[i] = src[i];
  }
}

int Memcmp(const void * ptr1, const void * ptr2, size_t len) {
  for (size_t i = 0; i < len; i++) {
    unsigned char b1 = *((unsigned char *)ptr1 + i);
    unsigned char b2 = *((unsigned char *)ptr2 + i);
    if (b1 > b2) return 1;
    else if (b1 < b2) return -1;
  }
  return 0;
}

}
