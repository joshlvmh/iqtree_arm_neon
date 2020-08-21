#include <iostream>
#include "arm_neon.h"

int main () {
#if defined(__aarch64__)
  std::cout << "defined" << "\n";
#else
  std::cout << "not defined" << "\n";
#endif
  unsigned int fpscr = __vfp_status(0,0);
  std::cout << fpscr << "\n";
  return 0;
}
