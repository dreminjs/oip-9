#pragma once
#include "worker.h"
 
struct Node {
    Worker data;
    Node* next;
    Node* prev;
 
    Node(const Worker& w) : data(w), 
    next(nullptr), 
    prev(nullptr) {}
};
 
struct Deque {
    Node* head;
    Node* tail;
    int   size;
};

void init(Deque* d);
bool isEmpty(const Deque* d);
int  getSize(const Deque* d);
void pushFront(Deque* d, const Worker& w);
void pushBack (Deque* d, const Worker& w);
Worker popFront(Deque* d);
Worker popBack (Deque* d);
const Worker& front(const Deque* d);
const Worker& back (const Deque* d); 
void clear(Deque* d);
void printWorker    (const Worker& w);
void printDeque     (const Deque* d);
void printDequeTable(const Deque* list);
 