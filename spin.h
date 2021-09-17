#ifndef __SPIN_H
#define __SPIN_H

typedef struct spinlock{
    int flag;
} spinlock_t;

// initialize the lock
void spinlock_init(spinlock_t *lock);

// acquire the spinlock
void spinlock_acquire(spinlock_t *lock);

// release the spinlock 
void spinlock_release(spinlock_t *lock);

#endif
