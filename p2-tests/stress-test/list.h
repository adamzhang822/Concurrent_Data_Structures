#ifndef __LIST_H
#define __LIST_H

#include <pthread.h>
#include "spin.h"

// ***** Structs *****// 
typedef struct node { 
    void* element;
    int key;
    struct node *next;
} node_t;

typedef struct list {
    node_t *head;
    spinlock_t lock;
} list_t;

typedef struct list_p {
    node_t *head;
    pthread_mutex_t lock;
} list_p_t;

// ***** Member functions ***** //

void free_list(list_t *list);

void free_list_p(list_p_t *list);

void List_Init(list_t *list);

void List_Insert(list_t *list, void* element, unsigned int key);

void List_Delete(list_t *list, unsigned int key);

void *List_Lookup(list_t *list, unsigned int key);

void List_Init_p(list_p_t *list);

void List_Insert_p(list_p_t *list, void* element, unsigned int key);

void List_Delete_p(list_p_t *list, unsigned int key);

void *List_Lookup_p(list_p_t *list, unsigned int key);

#endif