#include <ansa/linked-list>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

struct SimpleLink {
  SimpleLink() : link(*this) {}
  LinkedList<SimpleLink>::Link link;
};

void TestPushPop();

int main() {
  TestPushPop();
  return 0;
}

void TestPushPop() {
  ScopedPass pass("LinkedList::[Pop/Add/Shift/AddFront]()");
  
  // just try some Add(), AddFront(), Pop(), and Shift() calls.
  SimpleLink one;
  SimpleLink two;
  SimpleLink three;
  LinkedList<SimpleLink> list;
  
  list.Add(&one.link);
  assert(list.Pop() == &one);
  assert(list.Pop() == NULL);
  
  list.Add(&one.link);
  list.Add(&two.link);
  list.AddFront(&three.link);
  assert(list.Pop() == &two);
  assert(list.Pop() == &one);
  assert(list.Pop() == &three);
  assert(list.Pop() == NULL);
  
  list.AddFront(&one.link);
  list.Add(&two.link);
  list.AddFront(&three.link);
  assert(list.Pop() == &two);
  assert(list.Pop() == &one);
  assert(list.Pop() == &three);
  assert(list.Pop() == NULL);
  
  list.Add(&one.link);
  list.Add(&two.link);
  list.AddFront(&three.link);
  assert(list.Shift() == &three);
  assert(list.Shift() == &one);
  assert(list.Shift() == &two);
  assert(list.Shift() == NULL);
}
