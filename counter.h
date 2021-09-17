#ifndef __COUNTER_H
#define __COUNTER_H

//#include <pthread.h>  
#include <stdio.h>
#include <stdlib.h>
#include "spin.h"


typedef struct counter {
    int value;
    spinlock_t lock;
} counter_t;

/*
typedef struct counter_p {
    int value;
    pthread_mutex_t lock;
} counter_p_t;
*/


void Counter_Init(counter_t *c, int value);

int Counter_GetValue(counter_t *c);

void Counter_Increment(counter_t *c);

void Counter_Decrement(counter_t *c);

/*

void Counter_Init_p(counter_p_t *c, int value);

int Counter_GetValue_p(counter_p_t *c);

void Counter_Increment_p(counter_p_t *c);

void Counter_Decrement_p(counter_p_t *c);
*/


#endif