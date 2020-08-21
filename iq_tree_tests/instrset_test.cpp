#include <iostream>
#include "arm_neon.h"

#ifndef INSTRSET
#if defined ( __AVX512F__ ) || defined ( __AVX512__ )
#define INSTRSET 9
#elif defined ( __AVX2__ )
#define INSTRSET 8
#elif defined ( __AVX__ )
#define INSTRSET 7
#elif defined ( __SSE4_2__ ) || defined ( __ARM_NEON )
#define INSTRSET 6
#elif defined ( __SSE4_1__ )
#define INSTRSET 5
#elif defined ( __SSSE3__ )
#define INSTRSET 4
#elif defined ( __SSE3__ )
#define INSTRSET 3
#elif defined ( __SSE2__ ) || defined ( __x86_64__ )
#define INSTRSET 2
#elif defined ( __SSE__ )
#define INSTRSET 1
#elif defined ( _M_IX86_FP )
#define INSTRSET _M_IX86_FP
#else
#define INSTRSET 0
#endif
#endif

int main () {
  std::cout << INSTRSET << "\n";

  int a = 3;
  int b = a >> 1;

  std::cout << a << "\n";
  std::cout << b << "\n";

#if defined(__ARM_PCS_VFP)
  std::cout << "defined" << "\n";
#else
  std::cout << "not defined" << "\n";
#endif

  return 0;
}
