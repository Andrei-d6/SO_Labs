/**
  * SO, 2016
  * Lab #5
  *
  * Task #8, lin
  *
  * Endianess
  */
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

unsigned int power(int nr, int power)
{ 
  unsigned int res = 1;
  for (int i = 0; i < power; i++)
    res *= nr;

  return res;
}

int main(void)
{
	int i;
	unsigned int n = 0xDEADBEEF;
	unsigned char *w = (unsigned char *)&n;

	/* TODO - use w to show all bytes of n in order */
  printf("n=0x");

  for (i = 0; i < 4; i += 1) {
    printf("%x", w[i]);
  }
  printf("\n");

	return 0;
}

