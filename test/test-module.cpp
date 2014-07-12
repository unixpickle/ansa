#include <ansa/module>
#include <cassert>
#include "scoped-pass.hpp"

using namespace ansa;

static int globalCounter = 0;

class MyModule : public Module {
public:
  DepList regDeps;
  DepList superDeps;
  int place;
  
protected:
  virtual void Initialize() {
    place = globalCounter++;
  }
  
  virtual DepList GetDependencies() {
    return regDeps;
  }
  
  virtual DepList GetSuperDependencies() {
    return superDeps;
  }
};

void TestDepList();
void TestAllFeatures();

int main() {
  TestDepList();
  TestAllFeatures();
  return 0;
}

void TestDepList() {
  ScopedPass pass("DepList");
  
  Module * m = NULL;
  
  assert(DepList(m, m, m, m).count == 4);
  assert(DepList().count == 0);
  DepList myList(m);
  assert(myList.count == 1);
  myList = DepList(m, m);
  assert(myList.count == 2);
}

void TestAllFeatures() {
  ScopedPass pass("Module");
  
  MyModule rootModule;
  MyModule subModule;
  MyModule subModuleSuper;
  MyModule subModuleSuperDep;
  
  rootModule.regDeps = DepList(&subModule);
  subModule.superDeps = DepList(&subModuleSuper);
  subModuleSuper.regDeps = DepList(&subModuleSuperDep);
  
  rootModule.Load();
  
  assert(subModule.place == 0);
  assert(subModuleSuperDep.place == 1);
  assert(subModuleSuper.place == 2);
  assert(rootModule.place == 3);
}
