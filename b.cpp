//Parallel program (based on Pthreads) with one mutex for the entire linked list
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <cstdlib>
using namespace std;

struct list_node_s {
    int data;
    struct  list_node_s* next;
};
struct list_node_s head;

pthread_mutex_t lock;

void* Member(void *my_value) {
    long value = (long)my_value;
    pthread_mutex_lock(&lock);
    struct list_node_s* head_p = &head;
    struct list_node_s* curr_p = head_p;

    while (curr_p != NULL && curr_p->data < value) {
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        cout << "Value " << value <<" is not a member.\n"<< endl;
    } else {
        cout << "Value " << value <<" is a member.\n"<< endl;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* Insert(void *my_value) {
    long value = (long)my_value;
    pthread_mutex_lock(&lock);
    struct list_node_s** head_pp = &head.next;
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        temp_p = (struct list_node_s *)malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL) { //New first node
            *head_pp = temp_p;
        } else {
            pred_p->next = temp_p;
        }
        cout << "Value " <<temp_p->data <<" inserted.\n"<< endl;
    } else { // Value already in list
        cout << "Value already in list\n" << endl;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* Delete(void *my_value) {
    long value = (long)my_value;
    pthread_mutex_lock(&lock);
    struct list_node_s** head_pp = &head.next;
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value) {
        if (pred_p == NULL) { // Deleting first node in list
            *head_pp = curr_p->next;
            free(curr_p);
        } else {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        cout << "Value " << value <<" is deleted.\n"<< endl;
    } else { // Value isn't in list
        cout << "Tried to delete Value " << value <<" but it is not in the list.\n"<< endl;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* PrintLinkedList() {
    pthread_mutex_lock(&lock);
    struct list_node_s* head_p = &head;
    struct list_node_s* curr_p = head_p;
    int length = 0;
    while (curr_p->next != NULL) {
        cout << curr_p->next->data << "\n";
        length++;
        curr_p = curr_p->next;
    }
    cout <<"Length of the Linked List: "<< length << "\n";
    pthread_mutex_unlock(&lock);
    return NULL;
}


void* PrintHello(void *threadid) {
    long tid;
    tid = (long)threadid;
    cout << "Hello World! Thread ID, " << tid << endl;
    pthread_exit(NULL);
}

#define NUM_THREADS 7
#define n 1000
#define m 10000
#define mMember 0.99
#define mIndex 0.005
#define mDelete 0.005

int main(int argc, char* argv[]) {

    int numberOfMemberOperations = m*mMember;
    int numberOfIndexOperations = m*mIndex;
    int numberOfDeleteOperations = m*mDelete;

    //generate n random numbers and add to an array
    long randomNumberArray[n];
    long randomNumber;
    int randomNumberCount=0;
    while (randomNumberCount<n ) {
        bool uniqueRandomNumber = true;
        randomNumber = rand();
        for( int i = 0; i < randomNumberCount; i++ ) {
            if (randomNumberArray[i] == randomNumber) {
                uniqueRandomNumber = false;
                break;
            }
        }
        if (uniqueRandomNumber) {
            randomNumberArray[randomNumberCount] = randomNumber;
            randomNumberCount++;
        }
    }


    pthread_t threads[NUM_THREADS];
    head.next=NULL;
    int rc;

    for( int i = 0; i < NUM_THREADS; i++ ) {
        cout << "main() : creating thread, " << i << endl;

        rc = pthread_create(&threads[i], NULL, Insert, (void*)i);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
        Insert((void*)i);
        Delete((void*)5);
        Member((void*)5);
    }

    for( int j = 0; j < NUM_THREADS; j++ ) {
        pthread_join(threads[j], NULL);
    }


    PrintLinkedList();


//    pthread_exit(NULL);
    pthread_mutex_destroy(&lock);
//    cout << &head.next->data << endl;
//    PrintLinkedList(&head);
//    int n = 1000;
//    int n_count = 0;
//    while (n_count<n) {
//        n_count+= Insert(rand(),&head.next);
//    }

}

// cd "/home/thisal/Desktop/ConcurrentProgrammingLab1/" && g++ b.cpp -lpthread -o b && "/home/thisal/Desktop/ConcurrentProgrammingLab1/"b