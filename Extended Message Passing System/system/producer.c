/* producer.c - producer */

#include <stdlib.h>
#include <xinu.h>

/**
 *
 */
process producer(pid32 cons_pid, int32 n_items)
{
  int32 i;
  int   random;

  for (i = 0; i < n_items; i++) {
    random = rand() % 1024;
    xsend(cons_pid, random, isprime(random));
  }
  
  return OK;
}
