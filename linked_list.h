#pragma once
#include "worker.h"

struct Node {
    Worker data;
    Node* next = nullptr;
    Node* prev = nullptr;
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
};

void initList(List& list);                          
void clearList(List& list);                         
void addFirst(List& list, const Worker& w);         
void addLast(List& list, const Worker& w);          
bool addBefore(List& list, int index, const Worker& w);
bool addAfter(List& list, int index, const Worker& w); 
bool removeAt(List& list, int index);                
void swapNodes(List& list, int k, int g);     
bool removeByIndex(List& list, int index);      
Node* getNode(const List& list, int index);          