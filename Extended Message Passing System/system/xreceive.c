/* xreceive.c - xreceive */

#include <xinu.h>

/**
 *
 */
umsg32	xreceive(void)
{
  intmask mask;			/* Saved interrupt mask		*/
  struct  procent *prptr;	/* Ptr to process's table entry	*/
  umsg32  msg;			/* Message to return		*/
  qid16   xqueue;               /* Wait queue of the receiver   */
  
  mask   = disable();
  prptr  = &proctab[currpid];
  xqueue = prptr->prxqueue;
  if (prptr->prxmsgcnt == 0) {
    prptr->prstate = PR_XRECV;
    resched();		        /* Block until message arrives	*/
  }
  
  if (prptr->prxpriomsg > 0) msg = prptr->prxmsgs[--prptr->prxpriomsg];
  else                       msg = prptr->prxmsgs[++prptr->prxnormmsg];
	
  /* Decerement the message count */
  prptr->prxmsgcnt--;	       
  
  if (isempty(xqueue) == FALSE) {
    pid32 pid = dequeue(xqueue);
    if (pid == SYSERR) {
      restore(mask);
      return SYSERR;
    }
    ready(pid);
  }
   
  restore(mask);
  return msg;
}
