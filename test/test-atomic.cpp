#include "scoped-pass.hpp"
#include <ansa/atomic>
#include <cassert>

using namespace ansa;

void TestOperations();

int main() {
  TestOperations();
  
  // TODO: test atomicity using threads
  
  return 0;
}

void TestOperations() {
  ScopedPass pass("Atomic<int> operations");
  
  Atomic<int> myNumber(3);
  for (int i = 0; i < 10; i++) {
    assert((myNumber++) == i + 3);
  }
  for (int i = 0; i < 10; i++) {
    assert((--myNumber) == 13 - i - 1);
  }
  
  assert(myNumber == 3);
  myNumber += 3;
  assert(myNumber == 6);
  myNumber -= 3;
  assert(myNumber == 3);
  
  assert(++myNumber == 4);
  assert(myNumber-- == 4);
  assert(myNumber == 3);
}
