#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>

// Global variable:
int i = 2;
#define NUM_THREADS 5

void* foo(void* p){
    // Print value received as argument:
    printf("Thread");
    printf("%i\n", * (int*)p);

    // Return reference to global variable:
//    pthread_exit(&i);
    pthread_exit(NULL);
}

int main(void){
    // Declare variable for thread's ID:
    pthread_t threads[NUM_THREADS]; //    pthread_t is the object and threads is a array




    for (int k = 0; k < NUM_THREADS; k++) {
        printf("main() : creating thread, %i\n", k);
        pthread_create(&threads[k], NULL, foo, &k);
    }

    for (int m = 0; m < NUM_THREADS; m++) {
//        int* ptr;

        // Wait for foo() and retrieve value in ptr;
//        pthread_join(id, (void**)&ptr);
        pthread_join(threads[m], NULL);
        printf("Main\n");
//        printf("%i\n", *ptr);
    }


}