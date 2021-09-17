#include <stdlib.h>
#include <stdio.h>
//#include <pthread.h>
#include "list.h"
#include "spin.h"



void free_list(list_t *list) {
    node_t* current = list->head;
    while (current != NULL) {
        node_t* temp = current->next;
        free(current);
        current = temp;
    }
    list->head = NULL;
    return;
}

/*
void free_list_p(list_p_t *list){
    node_t* current = list->head;
    while(current != NULL) {
        node_t* temp = current->next;
        free(current);
        current = temp;
    }
    list->head = NULL;
    return;
}
*/

void List_Init(list_t *list) {
    list->head = NULL;
    spinlock_init(&list->lock);
}

/*
void List_Init_p(list_p_t *list) {
    list->head = NULL;
    pthread_mutex_init(&list->lock, NULL);
}
*/

void List_Insert(list_t *list, void *element, unsigned int key) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if(new == NULL) {
        perror("malloc");
        return;
    }
    new->element = element;
    new->key = key;

    //just lock critical section
    spinlock_acquire(&list->lock);
    new->next = list->head;
    list->head = new;
    spinlock_release(&list->lock);

    return;
}

/*
void List_Insert_p(list_p_t *list, void *element, unsigned int key) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if(new == NULL) {
        perror("malloc");
        return;
    }
    new->element = element;
    new->key = key;

    //just lock critical section
    pthread_mutex_lock(&list->lock);
    new->next = list->head;
    list->head = new;
    pthread_mutex_unlock(&list->lock);

    return;
}
*/

void List_Delete(list_t *list, unsigned int key) {
    spinlock_acquire(&list->lock);

    node_t* ptr = list->head;
    node_t* trail = list->head;
    if (ptr == NULL) {
        spinlock_release(&list->lock);
        return; // nothing to delete when the list is empty
    }

    if (ptr->key == key) {
        node_t* temp = ptr;
        list->head = ptr->next;
        free(temp);
    }else{
        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (ptr->key == key) {
                node_t *temp = ptr;
                trail->next = ptr->next;
                free(temp);
                break;
            }
            trail = trail->next;
        }
    }

    spinlock_release(&list->lock);
    return;
}

/*
void List_Delete_p(list_p_t *list, unsigned int key) {
    pthread_mutex_lock(&list->lock);

    node_t* ptr = list->head;
    node_t* trail = list->head;
    if (ptr == NULL) {
        pthread_mutex_unlock(&list->lock);
        return; // nothing to delete when the list is empty
    }

    if (ptr->key == key) {
        node_t* temp = ptr;
        list->head = ptr->next;
        free(temp);
    }else{
        while (ptr->next != NULL) {
            ptr = ptr->next;
            if (ptr->key == key) {
                node_t *temp = ptr;
                trail->next = ptr->next;
                free(temp);
                break;
            }
            trail = trail->next;
        }
    }

    pthread_mutex_unlock(&list->lock);
    return;
}
*/

void *List_Lookup(list_t *list, unsigned int key) {

    spinlock_acquire(&list->lock);
    node_t *ptr = list->head;
    while (ptr != NULL) {
        if (ptr->key == key) {
            spinlock_release(&list->lock);
            return ptr->element;
        }
        ptr = ptr->next;
    }
    spinlock_release(&list->lock);
    
    return NULL;
}

/*
void *List_Lookup_p(list_p_t *list, unsigned int key) {

    pthread_mutex_lock(&list->lock);
    node_t *ptr = list->head;
    while (ptr != NULL) {
        if (ptr->key == key) {
            pthread_mutex_unlock(&list->lock);
            return ptr->element;
        }
        ptr = ptr->next;
    }
    pthread_mutex_unlock(&list->lock);
    
    return NULL;
}
*/


