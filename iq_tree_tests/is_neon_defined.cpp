#include <iostream>

int main(int argc, char** argv) {
  std::cout << "__ARM_NEON      is: ";
#ifdef __ARM_NEON
  std::cout << __ARM_NEON;
#else
  std::cout << "undefined.";
#endif
  std::cout << std::endl;
  std::cout << "ARM__NEON_FP is: ";
#ifdef __ARM_NEON_FP
  std::cout << __ARM_NEON_FP;
#else
  std::cout << "undefined.";
#endif
  std::cout << std::endl;
  return 0;
}
