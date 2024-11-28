
#ifndef SLEEPLOCK_H
#define SLEEPLOCK_H

#include "spinlock.h" // Asegúrate de incluir spinlock.h

struct sleeplock {
  uint locked;         // Is the lock held?
  struct spinlock lk;  // Spinlock protecting this sleep lock
  char *name;          // Name of lock.
  int pid;             // Process holding lock
};

#endif // SLEEPLOCK_H
