#ifndef __ANSA_CSTRING_HPP__
#define __ANSA_CSTRING_HPP__

#include <cstddef>

namespace ansa {

size_t Strlen(const char * str);
void * Memset(void * ptr, char value, size_t size);
void Bzero(void * ptr, size_t size);
void Memcpy(void * dest, const void * src, size_t size);
int Memcmp(const void * ptr1, const void * ptr2, size_t len);

}

#endif
