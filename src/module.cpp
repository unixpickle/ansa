#include "module.hpp"

namespace ansa {

Module::Module() : loadStartCount(0), doneInit(false) {
}

void Module::Load() {
  if (loadStartCount++) {
    return;
  }
  
  DepList deps(GetDependencies());
  for (int i = 0; i < deps.count; i++) {
    deps[i]->Load();
  }
  
  Initialize();
  
  deps = GetSuperDependencies();
  for (int i = 0; i < deps.count; i++) {
    deps[i]->Load();
  }
  
  doneInit = true;
}

bool Module::IsUninitialized() {
  return loadStartCount == 0;
}

bool Module::IsInitialized() {
  return doneInit;
}

DepList Module::GetSuperDependencies() {
  return DepList();
}

}
