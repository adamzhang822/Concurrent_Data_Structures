#ifndef __HASH_H
#define __HASH_H

#include "list.h"

typedef struct hash {
    list_t **lists;
    int buckets_num;
} hash_t;

/*
typedef struct hash_p {
    list_p_t **lists;
    int buckets_num;
} hash_p_t;
*/

void Hash_Init(hash_t *hash, int buckets);

void Hash_Insert(hash_t *hash, void *element, unsigned int key);

void Hash_Free(hash_t *hash);

void Hash_Delete(hash_t *hash, unsigned int key);

void *Hash_Lookup(hash_t *hash, unsigned int key);

/*

void Hash_Init_p(hash_p_t *hash, int buckets);

void Hash_Insert_p(hash_p_t *hash, void *element, unsigned int key);

void Hash_Delete_p(hash_p_t *hash, unsigned int key);

void *Hash_Lookup_p(hash_p_t *hash, unsigned int key);

void Hash_Free_p(hash_p_t *hash);

*/

#endif