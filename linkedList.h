#pragma once
#include "worker.h"
 
struct Node {
    Worker data;
    Node* next;
    Node* prev;
};
 
struct LinkedList {
    Node* head;
    Node* tail;
    int   size;
};

void init(LinkedList* d);
bool isEmpty(const LinkedList* d);
int  getSize(const LinkedList* d);
void pushFront(LinkedList* d, const Worker& w);
void pushBack (LinkedList* d, const Worker& w);
Worker popFront(LinkedList* d);
Worker popBack (LinkedList* d);
const Worker& front(const LinkedList* d);
const Worker& back (const LinkedList* d); 
void clear(LinkedList* d);
void printWorker    (const Worker& w);
void printLinkedList     (const LinkedList* d);
void printLinkedListTable(const LinkedList* list);
 