/* lab2.h */

#ifndef _LAB2_H
#define _LAB2_H

process producer(pid32 cons_pid, int32 n_items);
process consumer(int32 n_items);
bool8   isprime(int32 n);

#endif
