#include <ansa/lock>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

class MyFancyLock : public Lock {
public:
  int yieldCount = 0;
  
protected:
  virtual void Yield() {
    ++yieldCount;
    Release();
  }
};

int main() {
  ScopedPass pass("Lock");
  MyFancyLock theLock;
  theLock.Seize();
  theLock.SeizeYielding();
  assert(theLock.yieldCount == 1);
  theLock.Release();
  theLock.Seize();
  theLock.Release();
  theLock.Seize();
  theLock.Release();
  return 0;
}
