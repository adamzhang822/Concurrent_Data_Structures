#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "hash.h"
#include "list.h"
#include "spin.h"

void Hash_Init(hash_t *hash, int buckets) {
    list_t** hash_table = malloc(buckets * sizeof(list_t*));
    if(hash_table == NULL) {
        perror ("malloc");
        return;
    }
    hash->buckets_num = buckets;
    hash->lists = hash_table;
    for (int i = 0; i < buckets; i++) {
        hash->lists[i] = malloc(sizeof(list_t));
        List_Init(hash->lists[i]);
    }
    return;
}

void Hash_Init_p(hash_p_t *hash, int buckets) {
    list_p_t** hash_table = malloc(buckets * sizeof(list_p_t*));
    if(hash_table == NULL) {
        perror ("malloc");
        return;
    }
    hash->buckets_num = buckets;
    hash->lists = hash_table;
    for (int i = 0; i < buckets; i++) {
        hash->lists[i] = malloc(sizeof(list_p_t));
        List_Init_p(hash->lists[i]);
    }
    return;
}

void Hash_Free(hash_t *hash) {
    int n = hash->buckets_num;
    for (int i = 0; i < n; i++) {
        free_list(hash->lists[i]);
    }
    for(int i = 0; i < n; i++) {
        free(hash->lists[i]);
    }
    free(hash->lists);
    return;
}

void Hash_Free_p(hash_p_t *hash) {
    int n = hash->buckets_num;
    for (int i = 0; i < n; i++) {
        free_list_p(hash->lists[i]);
    }
    for (int i = 0; i < n; i++) {
        free(hash->lists[i]);
    }
    free(hash->lists);
    return;
}

void Hash_Insert(hash_t *hash, void *element, unsigned int key) {
    return List_Insert(hash->lists[key % hash->buckets_num], element, key);
}

void Hash_Delete(hash_t *hash, unsigned int key) {
    return List_Delete(hash->lists[key % hash->buckets_num], key);
}

void *Hash_Lookup(hash_t *hash, unsigned int key) {
    return List_Lookup(hash->lists[key % hash->buckets_num], key);
}

void Hash_Insert_p(hash_p_t *hash, void *element, unsigned int key) {
    return List_Insert_p(hash->lists[key % hash->buckets_num], element, key);
}

void Hash_Delete_p(hash_p_t *hash, unsigned int key) {
    return List_Delete_p(hash->lists[key % hash->buckets_num], key);
}

void *Hash_Lookup_p(hash_p_t *hash, unsigned int key) {
    return List_Lookup_p(hash->lists[key % hash->buckets_num], key);
}