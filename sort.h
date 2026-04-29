#pragma once
#include "deque.h"
#include <string>

using namespace std;

enum SortField {
    FIELD_SURNAME    = 1,
    FIELD_EXPERIENCE = 2
};

Worker* dequeToArray(const Deque* d, int& size);

void arrayToDeque(Deque* d, const Worker* arr, int size);

int cmpWorkers(const Worker& a, const Worker& b, SortField field, bool ascending);

void insertionSort(Worker* arr, int size, SortField field, bool ascending);

int  hoarePartition(Worker* arr, int left, int right, SortField field, bool ascending);
void quickSort      (Worker* arr, int left, int right, SortField field, bool ascending);

void sortDequeInsertion(Deque* d, SortField field, bool ascending);
void sortDequeQuick    (Deque* d, SortField field, bool ascending);

void loadSampleData(Deque* d);