#include <ansa/lock>
#include <cassert>
#include <vector>
#include <thread>
#include <unistd.h>
#include "scoped-pass.hpp"

using namespace ansa;

class MyFancyLock : public YieldingLock {
public:
  int yieldCount = 0;
  
protected:
  virtual void Yield() {
    ++yieldCount;
    Release();
  }
};

static OrderedLock sharedLock;
static int globalValue = 0;

void TestYielding();
void TestThreaded();
void IncrementValue(int idx);

int main() {
  TestYielding();
  TestThreaded();
  return 0;
}

void TestYielding() {
  ScopedPass pass("YieldingLock");
  MyFancyLock theLock;
  theLock.Seize();
  theLock.SeizeYielding();
  assert(theLock.yieldCount == 1);
  theLock.Release();
  theLock.Seize();
  theLock.Release();
  theLock.Seize();
  theLock.Release();
}

void TestThreaded() {
  ScopedPass pass("OrderedLock [should take a few seconds]");
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; ++i) {
    threads.push_back(std::thread(IncrementValue, i));
  }
  for (int i = 0; i < 10; ++i) {
    threads[i].join();
  }
  assert(globalValue == 10);
}

void IncrementValue(int idx) {
  usleep(idx * 100000);
  sharedLock.Seize();
  // make sure we're still sleeping with the lock held when the next thread
  // attempts to lock it
  usleep(200000);
  ++globalValue;
  assert(globalValue == idx + 1);
  sharedLock.Release();
}
