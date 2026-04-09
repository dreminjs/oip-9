#include "linked_list.h"
#include <iostream>

void initList(List &list)
{
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

void clearList(List &list)
{
    Node *current = list.head;
    while (current)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    list.head = list.tail = nullptr;
    list.size = 0;
}

Node *getNode(const List &list, int index)
{
    if (index < 0 || index >= list.size)
        return nullptr;
    Node *curr = list.head;
    for (int i = 0; i < index; i++)
        curr = curr->next;
    return curr;
}

void addFirst(List &list, const Worker &w)
{
    Node *newNode = new Node{w, list.head, nullptr};
    if (list.head)
        list.head->prev = newNode;
    else
        list.tail = newNode;
    list.head = newNode;
    list.size++;
}

void addLast(List &list, const Worker &w)
{
    Node *newNode = new Node{w, nullptr, list.tail};
    if (list.tail)
        list.tail->next = newNode;
    else
        list.head = newNode;
    list.tail = newNode;
    list.size++;
}

bool addBefore(List &list, int index, const Worker &w)
{
    if (index == 0)
    {
        addFirst(list, w);
        return true;
    }
    Node *curr = getNode(list, index);
    if (!curr)
        return false;

    Node *newNode = new Node{w, curr, curr->prev};
    curr->prev->next = newNode;
    curr->prev = newNode;
    list.size++;
    return true;
}

bool addAfter(List &list, int index, const Worker &w)
{
    if (index == list.size - 1)
    {
        addLast(list, w);
        return true;
    }
    Node *curr = getNode(list, index);
    if (!curr)
        return false;

    Node *newNode = new Node{w, curr->next, curr};
    curr->next->prev = newNode;
    curr->next = newNode;
    list.size++;
    return true;
}

bool removeAt(List &list, int index)
{
    Node *toDelete = getNode(list, index);
    if (!toDelete)
        return false;

    if (toDelete->prev)
        toDelete->prev->next = toDelete->next;
    else
        list.head = toDelete->next;

    if (toDelete->next)
        toDelete->next->prev = toDelete->prev;
    else
        list.tail = toDelete->prev;

    delete toDelete;
    list.size--;
    return true;
}

void swapNodes(List &list, int k, int g)
{
    if (k == g || k < 0 || g < 0 || k >= list.size || g >= list.size)
    {
        return;
    }

    Node *nodeK = getNode(list, k);
    Node *nodeG = getNode(list, g);

    if (k > g)
    {
        Node *tmp = nodeK;
        nodeK = nodeG;
        nodeG = tmp;
    }

    Node *pK = nodeK->prev;
    Node *nK = nodeK->next;
    Node *pG = nodeG->prev;
    Node *nG = nodeG->next;

    if (nodeK->next == nodeG)
    {
        nodeK->next = nG;
        nodeK->prev = nodeG;
        nodeG->next = nodeK;
        nodeG->prev = pK;
        if (pK)
            pK->next = nodeG;
        else
            list.head = nodeG;
        if (nG)
            nG->prev = nodeK;
        else
            list.tail = nodeK;
    }
    else
    {
        nodeK->next = nG;
        nodeK->prev = pG;
        nodeG->next = nK;
        nodeG->prev = pK;

        if (pK)
        {
            pK->next = nodeG;
        }
        else
        {

            list.head = nodeG;
        }
        if (nK)
        {

            nK->prev = nodeG;
        }
        if (pG)
        {

            pG->next = nodeK;
        }
        if (nG)
        {

            nG->prev = nodeK;
        }
        else {

            list.tail = nodeK;
        }
    }
}

bool removeByIndex(List& list, int index) {
    if (index < 0 || index >= list.size) {
        return false;
    }

    Node* toDelete = getNode(list, index); 
    if (!toDelete) return false;

    if (toDelete->prev != nullptr) {
        toDelete->prev->next = toDelete->next;
    } else {
        list.head = toDelete->next; 
    }

    if (toDelete->next != nullptr) {
        toDelete->next->prev = toDelete->prev;
    } else {
        list.tail = toDelete->prev; 
    }

    delete toDelete;
    list.size--;
    return true;
}