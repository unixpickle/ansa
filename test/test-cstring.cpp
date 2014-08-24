#include <ansa/cstring>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

void TestStrlen();
void TestMemset();
void TestBzero();
void TestMemcpy();
void TestMemcmp();
void TestMemmove();

int main() {
  TestStrlen();
  TestMemset();
  TestBzero();
  TestMemcpy();
  TestMemcmp();
  TestMemmove();
  return 0;
}

void TestStrlen() {
  ScopedPass pass("Strlen()");
  
  assert(Strlen("hey there") == 9);
  assert(Strlen("") == 0);
}

void TestMemset() {
  ScopedPass pass("Memset()");
  
  char myBuffer[10] {};
  Memset((void *)myBuffer, 3, 5);
  Memset((void *)(myBuffer + 5), 7, 5);
  
  assert(myBuffer[0] == 3);
  assert(myBuffer[1] == 3);
  assert(myBuffer[2] == 3);
  assert(myBuffer[3] == 3);
  assert(myBuffer[4] == 3);
  assert(myBuffer[5] == 7);
  assert(myBuffer[6] == 7);
  assert(myBuffer[7] == 7);
  assert(myBuffer[8] == 7);
  assert(myBuffer[9] == 7);
}

void TestBzero() {
  ScopedPass pass("Bzero()");
  
  char myBuffer[3] = {1, 2, 3};
  Bzero((void *)myBuffer, 2);
  assert(myBuffer[0] == 0);
  assert(myBuffer[1] == 0);
  assert(myBuffer[2] == 3);
}

void TestMemcpy() {
  ScopedPass pass("Memcpy()");
  
  char myBuffer[3] = {1, 2, 3};
  char myOther[3] = {3, 1, 2};
  
  Memcpy((void *)myBuffer, (void *)myOther, 2);
  assert(myBuffer[0] == 3);
  assert(myBuffer[1] == 1);
  assert(myBuffer[2] == 3);
  assert(myOther[0] == 3);
  assert(myOther[1] == 1);
  assert(myOther[2] == 2);
}

void TestMemcmp() {
  ScopedPass pass("Memcmp()");
  
  char buff1[5] = {1, 2, 3, 4, 5};
  char buff2[5] = {1, 2, 3, 4, 5};
  assert(Memcmp((void *)buff1, (void *)buff2, 5) == 0);
  buff1[3] = (char)200;
  assert(Memcmp((void *)buff1, (void *)buff2, 5) == 1);
  buff2[3] = (char)201;
  assert(Memcmp((void *)buff1, (void *)buff2, 5) == -1);
}

void TestMemmove() {
  ScopedPass pass("Memmove()");
  
  char buffer[6] = {1, 2, 3, 4, 5, 6};
  Memmove((void *)(buffer + 3), (void *)buffer, 3);
  assert(Memcmp((void *)buffer, (void *)"\x01\x02\x03\x01\x02\x03", 6) == 0);
  
  buffer[3] = 4;
  buffer[4] = 5;
  buffer[5] = 6;
  Memmove((void *)buffer, (void *)(buffer + 3), 3);
  assert(Memcmp((void *)buffer, (void *)"\x04\x05\x06\x04\x05\x06", 6) == 0);
  
  buffer[0] = 1;
  buffer[1] = 2;
  buffer[2] = 3;
  Memmove((void *)buffer, (void *)buffer, 6);
  assert(Memcmp((void *)buffer, (void *)"\x01\x02\x03\x04\x05\x06", 6) == 0);
}
