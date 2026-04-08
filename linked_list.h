#include "worker.h"

struct Node
{
    Worker data;
    Node* prev;
    Node* next;
};

struct List
{
    Node* head;
    Node* tail;
    int size;
};