#include "scoped-pass.hpp"
#include <ansa/macros>

int main() {
  ScopedPass pass("ANSA_EVAL_ASSERT");
  int i = 0;
  ANSA_EVAL_ASSERT((++i) == 1);
  assert(i == 1);
  return 0;
}
