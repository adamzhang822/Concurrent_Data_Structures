#include <pthread.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "spin.h"
#include "counter.h"
#include "list.h"
#include "hash.h"

int MAX_COUNT = 1000000; // number of increments for COunter_Increment experiment
int MAX_THREADS = 20; // max number of threads 
int MAX_ITER = 10; // number of iterations per experiment to average over
int MAX_ITEM = 1e5; // number of items inserted for Insert experiments
int DEFAULT_BUCKETS_NUM = 100; // default number of buckets for hash table experiment

counter_t c;
//counter_p_t cp;
list_t ls;
//list_p_t ls_p;
hash_t hash;
//hash_p_t hash_p;

//global hash tables for hash table scale experiment
int num_buckets_scale[5] = {10, 100, 1000, 10000, 100000};

// *********************************************
// Helper functions
// *********************************************

void myPrint(char *msg)
{
    write(STDOUT_FILENO, msg, strlen(msg));
}

void Inits(){
    // initialization for lists done within simulation function for lists
    Counter_Init(&c,0);
    //Counter_Init_p(&cp,0);
    Hash_Init(&hash,DEFAULT_BUCKETS_NUM);
    //Hash_Init_p(&hash_p, DEFAULT_BUCKETS_NUM);

}

// *********************************************
// Simulation for Counter_Increment
// *********************************************

void *simCounter () {
    for (int i = 0; i < MAX_COUNT; i++) {
        Counter_Increment(&c);
    }
    return NULL;
}

void spinCounter (int num_threads) {
    pthread_t *workers = malloc(sizeof(pthread_t) * num_threads);
    for (int i = 0; i < num_threads; i++) {
        int rc = pthread_create(&workers[i], NULL, simCounter, NULL);
        if(rc){
            printf("pthread create failed! \n");
            exit(1);
        }
    }
    for(int i =0; i < num_threads; i++) {
        pthread_join(workers[i], NULL);
    }
    free(workers);
    return;
}

/*
void *simCounter_p () {
    for (int i = 0; i < MAX_COUNT; i++) {
        Counter_Increment_p(&cp);
    }
    return NULL;
}

void plockCounter (int num_threads) {
    pthread_t *workers = malloc(sizeof(pthread_t) * num_threads);
    for (int i = 0; i < num_threads; i++) {
        int rc = pthread_create(&workers[i], NULL, simCounter_p, NULL);
        if(rc){
            printf("pthread create failed! \n");
            exit(1);
        }
    }
    for(int i =0; i < num_threads; i++) {
        pthread_join(workers[i], NULL);
    }
    free(workers);
    return;
}
*/

void doSimCounter () {
    FILE* outputSpin;
    FILE* outputPlock;
    outputSpin = fopen("CounterIncrementSpin.txt", "w");
    outputPlock = fopen("CounterIncrementPlock.txt", "w");
    struct timeval t1;
    struct timeval t2;
    for (int num_threads = 0; num_threads < MAX_THREADS; num_threads++) {
        printf("in thread %d \n", num_threads);
        double totalSpin = 0.0;
        for (int i = 1; i <= MAX_ITER; i++) {
            gettimeofday(&t1, NULL);
            spinCounter(num_threads);
            gettimeofday(&t2,NULL);
            totalSpin += (t2.tv_sec - t1.tv_sec) + (1.0 / 1000000) *(t2.tv_usec - t1.tv_usec);
        }
        double averageSpin = totalSpin / MAX_ITER;
        fprintf(outputSpin, "%f\n",averageSpin);
    }

    /*
    for (int num_threads = 0; num_threads < MAX_THREADS; num_threads++) {
        printf("in thread %d \n", num_threads);
        double totalPlock = 0.0;
        for (int i = 1; i <= MAX_ITER; i++) {
            gettimeofday(&t1, NULL);
            plockCounter(num_threads);
            gettimeofday(&t2,NULL);
            totalPlock += (t2.tv_sec - t1.tv_sec) + (1.0 / 1000000) *(t2.tv_usec - t1.tv_usec);
        }
        double averagePlock = totalPlock / MAX_ITER;
        fprintf(outputPlock, "%f\n",averagePlock);
    }
    */

    return;
}

// *********************************************
// Simulation for List-Insertion
// *********************************************

void *simList() {
    for (int i = 0; i < MAX_ITEM; i++) {
        List_Insert(&ls, NULL, i);
    }
    return NULL;
}

/*
void *simList_p() {
    for (int i = 0; i < MAX_ITEM; i++) {
        List_Insert_p(&ls_p, NULL,i);
    }
}
*/

void spinList(int num_threads) {
    pthread_t *workers = malloc(sizeof(pthread_t) * num_threads);
    for (int i = 0; i < num_threads; i++) {
        int rc = pthread_create(&workers[i], NULL, simList, NULL);
        if(rc){
            printf("pthread create failed! \n");
            exit(1);
        }
    }

    for(int i = 0; i < num_threads; i++) {
        pthread_join(workers[i], NULL);
    }
    free(workers);
    return;
}

/*
void plockList(int num_threads) {
    pthread_t *workers = malloc(sizeof(pthread_t) * num_threads);
    for (int i = 0; i < num_threads; i++) {
        int rc = pthread_create(&workers[i], NULL, simList_p, NULL);
        if(rc){
            printf("pthread create failed! \n");
            exit(1);
        }
    }

    for(int i = 0; i < num_threads; i++) {
        pthread_join(workers[i], NULL);
    }
    free(workers);
    return;
}
*/

void doSimList() {
    myPrint("in sim list! \n");
    FILE* outputSpin;
    FILE* outputPlock;
    outputSpin = fopen("ListInsertionSpin.txt", "w");
    outputPlock = fopen("ListInsertionPlock.txt", "w");
    struct timeval t1;
    struct timeval t2;

    for (int num_threads = 0; num_threads < MAX_THREADS; num_threads++) {
        printf("in thread num %d \n", num_threads);
        double totalSpin = 0.0;
        for (int i = 1; i <= MAX_ITER; i++) {
            List_Init(&ls);
            gettimeofday(&t1, NULL);
            spinList(num_threads);
            gettimeofday(&t2, NULL);
            totalSpin += (t2.tv_sec - t1.tv_sec) + (1.0 / 1000000) *(t2.tv_usec - t1.tv_usec);
            free_list(&ls);
        }

        double averageSpin = totalSpin / MAX_ITER;
        fprintf(outputSpin, "%f\n", averageSpin);

        /*
        double totalPlock = 0.0;
        for (int i = 1; i <= MAX_ITER; i++) {
            printf("in thread num %d \n", num_threads);
            List_Init_p(&ls_p);
            gettimeofday(&t1, NULL);
            plockList(num_threads);
            gettimeofday(&t2, NULL);
            totalPlock += (t2.tv_sec - t1.tv_sec) + (1.0 / 1000000) *(t2.tv_usec - t1.tv_usec);
            free_list_p(&ls_p);
        }
        double averagePlock = totalPlock / MAX_ITER;
        fprintf(outputPlock, "%f\n", averagePlock);
        */
    }

    return;
}

// *********************************************
// Simulation for Hash-Table Insertion
// *********************************************

void *simHash(void* arg) {
    hash_t* hash_sim = (hash_t*)arg;
    for (int i = 0; i < MAX_ITEM; i++) {
        Hash_Insert(hash_sim, NULL, rand() % hash_sim->buckets_num);
    }
    return NULL;
}

/*
void *simHash_p(void* arg) {
    hash_p_t* hash_sim = (hash_p_t*)arg;
    for (int i = 0; i < MAX_ITEM; i++) {
        Hash_Insert_p(hash_sim, NULL, rand() % hash_sim->buckets_num);
    }
    return NULL;
}
*/

void spinHash(int num_threads, hash_t* hash_sim) {
    void* arg = (void*)hash_sim;
    pthread_t *workers = malloc(sizeof(pthread_t) * num_threads);
    for (int i = 0; i < num_threads; i++) {
        int rc = pthread_create(&workers[i], NULL, simHash, arg);
        if(rc){
            printf("pthread create failed! \n");
            exit(1);
        }
    }

    for(int i = 0; i < num_threads; i++) {
        pthread_join(workers[i], NULL);
    }
    free(workers);
    return;
}

/*
void plockHash(int num_threads, hash_p_t* hash_sim) {
    void* arg = (void*)hash_sim;
    pthread_t *workers = malloc(sizeof(pthread_t) * num_threads);
    for (int i = 0; i < num_threads; i++) {
        int rc = pthread_create(&workers[i], NULL, simHash_p, arg);
        if(rc){
            printf("pthread create failed! \n");
            exit(1);
        }
    }

    for(int i = 0; i < num_threads; i++) {
        pthread_join(workers[i], NULL);
    }
    free(workers);
    return;
}
*/


void doSimHash() {
    FILE* output = fopen("HashInsertSpin.txt","w");
    struct timeval t1;
    struct timeval t2;
    
    for (int num_threads = 0; num_threads < MAX_THREADS; num_threads++) {
        printf("in thread num %d \n", num_threads);
        double totalSpin = 0.0;
        for (int i = 1; i <= MAX_ITER; i++) {
            gettimeofday(&t1, NULL);
            spinHash(num_threads, &hash);
            gettimeofday(&t2, NULL);
            totalSpin += (t2.tv_sec - t1.tv_sec) + (1.0 / 1000000) *(t2.tv_usec - t1.tv_usec);
        }
        double averageSpin = totalSpin / MAX_ITER;
        //printf("%f \n", averageSpin);
        fprintf(output, "%f\n", averageSpin);
    }
    return;
}

/*
void doSimHash_p() {
    FILE* output = fopen("HashInsertPlock.txt", "w");
    struct timeval t1;
    struct timeval t2;
    
    for (int num_threads = 0; num_threads < MAX_THREADS; num_threads++) {
        printf("in thread num %d \n", num_threads);
        double totalPlock = 0.0;
        for (int i = 1; i <= MAX_ITER; i++) {
            gettimeofday(&t1, NULL);
            plockHash(num_threads, &hash_p);
            gettimeofday(&t2, NULL);
            totalPlock += (t2.tv_sec - t1.tv_sec) + (1.0 / 1000000) *(t2.tv_usec - t1.tv_usec);
        }
        double averagePlock = totalPlock / MAX_ITER;
        fprintf(output, "%f\n",averagePlock);
        
    }
    return;
}
*/


void doSimHashScale() {
    FILE* output = fopen("HashScaleSpin.txt", "w");
    struct timeval t1;
    struct timeval t2;
    for (int bucket_size_index = 0; bucket_size_index < 5; bucket_size_index++) {
        printf("for bucket size: %d", num_buckets_scale[bucket_size_index]);
        Hash_Init(&hash, num_buckets_scale[bucket_size_index]);
        double totalSpin = 0.0;
        for (int i = 0; i < MAX_ITER; i++) {
            gettimeofday(&t1, NULL);
            spinHash(20, &hash);
            gettimeofday(&t2, NULL);            
            totalSpin += (t2.tv_sec - t1.tv_sec) + (1.0 / 1000000) *(t2.tv_usec - t1.tv_usec);
        }
        double averageSpin = totalSpin / MAX_ITER;
        fprintf(output, "%f\n", averageSpin);
        Hash_Free(&hash);
    }
    return;
}

/*
void doSimHashScale_p() {
    FILE* output = fopen("HashScalePlock.txt", "w");
    struct timeval t1;
    struct timeval t2;
    for (int bucket_size_index = 0; bucket_size_index < 5; bucket_size_index++) {
        Hash_Init_p(&hash_p, num_buckets_scale[bucket_size_index]);
        double totalPlock = 0.0;
        for (int i = 0; i < MAX_ITER; i++) {
            gettimeofday(&t1, NULL);
            plockHash(20, &hash_p);
            gettimeofday(&t2, NULL);            
            totalPlock += (t2.tv_sec - t1.tv_sec) + (1.0 / 1000000) *(t2.tv_usec - t1.tv_usec);
        }
        double averagePlock = totalPlock / MAX_ITER;
        fprintf(output, "%f\n", averagePlock);
        Hash_Free_p(&hash_p);
    }
    return;
}
*/

// *********************************************
// Get simulation outputs 
// *********************************************

 int main(int argc, char* argv[]) {
    srand(3);
    Inits();
    myPrint("doing simCounter! \n");
    doSimCounter();
    myPrint("doing simList! \n");
    doSimList();
    myPrint("doing sim Hash! \n");
    doSimHash();
    //doSimHash_p();
    myPrint("doing sim Hash scale! \n");
    doSimHashScale();
    //doSimHashScale_p();
    return 0;
}