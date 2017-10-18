/* xsend.c - xsend */

#include <xinu.h>

/**
 *
 */
syscall xsend(
	     pid32         pid,            /* ID of recipient process      */
	     umsg32        msg,            /* Contents of message          */
	     bool8         high_prio       /* Priority of message          */
	     )
{
  intmask mask;                   /* Saved interrupt mask         */
  struct  procent *prptr;         /* Ptr to process's table entry */
  qid16   xqueue;                 /* Wait queue of the receiver   */

  mask = disable();
  if (isbadpid(pid)) {
    restore(mask);
    return SYSERR;
  }

  prptr  = &proctab[pid];
  xqueue = prptr->prxqueue;

  if (prptr->prxmsgcnt == NMSG) {
    // enter current process in the wait queue of pid process
    proctab[currpid].prstate = PR_XSEND;
    if (enqueue(currpid, xqueue) == SYSERR) {
      restore(mask);
      return SYSERR;
    }
    resched();    
  }

  if (high_prio == TRUE) prptr->prxmsgs[prptr->prxpriomsg++] = msg;
  else                   prptr->prxmsgs[prptr->prxnormmsg--] = msg;

  /* Inncrement the message count */
  prptr->prxmsgcnt++;          

  /* If recipient waiting or in timed-wait make it ready */
  if (prptr->prstate == PR_XRECV) {
    ready(pid);
  }
  
  restore(mask);         
  return OK;
}
