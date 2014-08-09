#include <ansa/linked-list>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

struct SimpleLink {
  SimpleLink() : link(*this) {}
  LinkedList<SimpleLink>::Link link;
};

void TestPushPop();
void TestRemove();
void TestAccess();

int main() {
  TestPushPop();
  TestRemove();
  TestAccess();
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

void TestRemove() {
  ScopedPass pass("LinkedList::[Remove]()");
  
  // just try some Add(), AddFront(), Pop(), and Shift() calls.
  SimpleLink one;
  SimpleLink two;
  SimpleLink three;
  LinkedList<SimpleLink> list;
  
  list.Add(&one.link);
  list.Remove(&one.link);
  assert(list.Pop() == NULL);
  
  list.Add(&one.link);
  list.Add(&two.link);
  list.Add(&three.link);
  list.Remove(&two.link);
  assert(list.Pop() == &three);
  assert(list.Pop() == &one);
  assert(list.Pop() == NULL);
  
  list.Add(&one.link);
  list.Add(&two.link);
  list.Remove(&one.link);
  assert(list.Pop() == &two);
  assert(list.Pop() == NULL);
  
  list.Add(&one.link);
  list.Add(&two.link);
  list.Remove(&two.link);
  assert(list.Pop() == &one);
  assert(list.Pop() == NULL);
}

void TestAccess() {
  ScopedPass pass("LinkedList::[GetStart/GetEnd/GetFirst/GetLast]()");
  
  // just try some Add(), AddFront(), Pop(), and Shift() calls.
  SimpleLink one;
  SimpleLink two;
  SimpleLink three;
  LinkedList<SimpleLink> list;
  
  list.Add(&one.link);
  list.Add(&two.link);
  list.Add(&three.link);
  
  LinkedList<SimpleLink>::Iterator iter = list.GetStart();
  LinkedList<SimpleLink>::Iterator fin = list.GetEnd();
  
  assert(iter != fin);
  assert(&*(iter++) == &one);
  assert(&*(iter++) == &two);
  assert(&*(iter++) == &three);
  assert(iter == fin);
  
  assert(list.GetFirst() == &one);
  assert(list.GetLast() == &three);
  
  list.Remove(&one.link);
  list.Remove(&two.link);
  assert(list.GetFirst() == &three);
  assert(list.GetLast() == &three);
  list.Remove(&three.link);
  assert(list.GetFirst() == NULL);
  assert(list.GetLast() == NULL);
}
