#include <stdlib.h>
#include <stdio.h>
//#include <pthread.h>
#include "counter.h"
#include "spin.h"

void Counter_Init(counter_t *c, int value) {
    c->value = value;
    spinlock_init(&c->lock);
}

int Counter_GetValue(counter_t *c) {
    spinlock_acquire(&c->lock);
    int val = c->value;
    spinlock_release(&c->lock);
    return val;
}

void Counter_Increment(counter_t *c) {
    spinlock_acquire(&c->lock);
    c->value++;
    spinlock_release(&c->lock);
    return;
}

void Counter_Decrement(counter_t *c) {
    spinlock_acquire(&c->lock);
    c->value--;
    spinlock_release(&c->lock);
    return;
}

/*
void Counter_Init_p(counter_p_t *c, int value) {
    c->value = value;
    pthread_mutex_init(&c->lock, NULL);

}

int Counter_GetValue_p(counter_p_t *c) {
    pthread_mutex_lock(&c->lock);
    int val = c->value;
    pthread_mutex_unlock(&c->lock);
    return val;
}

void Counter_Increment_p(counter_p_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
    return;
}

void Counter_Decrement_p(counter_p_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
    return;
}
*/

