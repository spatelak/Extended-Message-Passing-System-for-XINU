/* prime.c - isprime */

#include <xinu.h>

/**
 *
 */
bool8 isprime(int32 n)
{
  int32 i;
  
  if (n <= 1) return FALSE;

  for (i = 2; i < n / 2; i++) {
    if (n % i == 0) return FALSE;
  }

  return TRUE;
}
