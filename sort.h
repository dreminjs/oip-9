#pragma once
#include "linkedList.h"
#include <string>

using namespace std;

enum SortField {
    FIELD_SURNAME    = 1,
    FIELD_EXPERIENCE = 2
};

Worker* dequeToArray(const LinkedList* d, int& size);

void arrayToDeque(LinkedList* d, const Worker* arr, int size);

int cmpWorkers(const Worker& a, const Worker& b, SortField field, bool ascending);

void insertionSort(Worker* arr, int size, SortField field, bool ascending);

int  hoarePartition(Worker* arr, int left, int right, SortField field, bool ascending);
void quickSort      (Worker* arr, int left, int right, SortField field, bool ascending);

void sortDequeInsertion(LinkedList* d, SortField field, bool ascending);
void sortDequeQuick    (LinkedList* d, SortField field, bool ascending);

void loadSampleData(LinkedList* d);