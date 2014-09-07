#include "scoped-pass.hpp"
#include <ansa/atomic-ptr>
#include <cassert>

using namespace ansa;

void TestOperations();

int main() {
  TestOperations();
  return 0;
}

void TestOperations() {
  ScopedPass pass("AtomicPtr<uint32_t> operations");
  
  uint32_t myBuffer[10];
  
  AtomicPtr<uint32_t> myPtr(myBuffer);
  for (int i = 0; i < 10; i++) {
    assert((myPtr++) == myBuffer + i);
  }
  for (int i = 0; i < 10; i++) {
    assert((--myPtr) == myBuffer + (9 - i));
  }
  
  assert(myPtr == myBuffer);
  myPtr += 3;
  assert(myPtr == &myBuffer[3]);
  myPtr -= 3;
  assert(myPtr == myBuffer);
  
  assert(++myPtr == &myBuffer[1]);
  assert(myPtr-- == &myBuffer[1]);
  assert(myPtr == myBuffer);
  
  assert((myPtr = &myBuffer[3]) == &myBuffer[3]);
  assert(myPtr == &myBuffer[3]);
}
