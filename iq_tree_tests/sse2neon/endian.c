#include <stdio.h>

int main ()
{
  unsigned int x = 0x76543210;
  char* c = (char*) &x;

  if (*c == 0x10)
  {
    printf("little \n");
  }
  else
  {
    printf("big \n");
  }
  return 0;
}
