/* consumer.c - consumer */

#include <xinu.h>

/**
 *
 */
process consumer(int32 n_items)
{
  int32  i;
  umsg32 msg;
  
  for (i = 0; i < n_items; i++) {
    msg = xreceive();
    kprintf("i = %d, message = %u\n", i, msg);
  }

  return OK;
}
