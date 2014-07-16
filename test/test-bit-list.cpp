#include <ansa/bit-list>
#include "scoped-pass.hpp"

using namespace ansa;

void TestByteCount();
void TestAccess();
void TestConstructor();

int main() {
  TestByteCount();
  TestAccess();
  TestConstructor();
  return 0;
}

void TestByteCount() {
  ScopedPass pass("BitList<x>::ByteCount");
  
  assert(BitList<3>::ByteCount == 1);
  assert(BitList<0>::ByteCount == 0);
  assert(BitList<8>::ByteCount == 1);
  assert(BitList<9>::ByteCount == 2);
  assert(BitList<16>::ByteCount == 2);
  assert(BitList<17>::ByteCount == 3);
}

void TestAccess() {
  ScopedPass pass("BitList<x>::operator[]");
  
  BitList<16> myBits;
  myBits[0] = true;
  myBits[1] = false;
  assert(myBits[0] == true);
  assert(myBits[1] == false);
  for (size_t i = 0; i < 16; i++) {
    myBits[i] = false;
    assert(myBits[i] == false);
    myBits[i] = true;
    assert(myBits[i] == true);
  }
  
  myBits[2] = false;
  
  const BitList<16> & bitsRef = myBits;
  assert(bitsRef[0] == true);
  assert(bitsRef[1] == true);
  assert(bitsRef[2] == false);
}

void TestConstructor() {
  ScopedPass pass("BitList<x>::BitList(bool)");
  
  BitList<16> happyList(true);
  for (size_t i = 0; i < 16; i++) {
    assert(happyList[i] == true);
  }
  
  BitList<16> sadList(false);
  for (size_t i = 0; i < 16; i++) {
    assert(sadList[i] == false);
  }
}
