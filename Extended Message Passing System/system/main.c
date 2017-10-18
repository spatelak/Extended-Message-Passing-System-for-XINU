/*  main.c  - main */

#include <stdlib.h>
#include <xinu.h>

process	main(void)
{

	/* Commented for your benefit..
	 * You can uncomment this while testing
	 * However, keep this commented while submission
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	*/
  srand(2);
  pid32 pid = create((void *) consumer, INITSTK, 25, "consumer", 1, 20);
  //resume(pid);
  //sleep(15);
  resume(create((void *) producer, INITSTK, 25, "producer1", 2, pid, 20));
  resume(create((void *) producer, INITSTK, 25, "producer2", 2, pid, 20));
  sleep(15);
  resume(pid);
  
  return OK;
	
}
