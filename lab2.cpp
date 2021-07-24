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

int Member(int value, struct list_node_s* head_p) {
    struct list_node_s* curr_p = head_p;

    while (curr_p != NULL && curr_p->data < value) {
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        return 0;
    } else {
        return 1;
    }
}

int Insert(int value, struct list_node_s** head_pp) {
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
        return 1;
    } else { // Value already in list
        return 0;
    }
}

int Delete(int value, struct list_node_s** head_pp) {
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
        return 1;
    } else { // Value isn't in list
        return 0;
    }
}

int PrintLinkedList(struct list_node_s* head_p) {
    struct list_node_s* curr_p = head_p;
    while (curr_p->next != NULL) {
        cout << curr_p->next->data << "\n";
        curr_p = curr_p->next;
    }
}

int main(int argc, char* argv[]) {
//    struct list_node_s first;
//    struct list_node_s second;
//    first.data = 0;
//    second.data = 1;
//    first.next=&second;
//    second.next=NULL;
//    cout << Member(2,&first) << "\n";
//    cout << Insert(2,&first.next) << "\n";
//    cout << Delete(1,&first.next) << "\n";
    struct list_node_s head;
    head.next=NULL;
    for (int i = 0; i < 10; i++) {
        Insert(rand(),&head.next);
//        cout << Insert(i,&head.next) << "\n";
    }

//    for(int i = 0; i<50; i++)
//        printf(" %d ", rand());
    PrintLinkedList(&head);
//
//    Delete(1,&head.next);
//    Delete(2,&head.next);
//    Delete(1,&head.next);
//    Insert(100,&head.next);
//    Insert(2,&head.next);
//    PrintLinkedList(&head);
    return 0;
}

// cd "/home/thisal/Desktop/ConcurrentProgrammingLab1/" && g++ lab2.cpp -lpthread -o lab2 && "/home/thisal/Desktop/ConcurrentProgrammingLab1/"lab2