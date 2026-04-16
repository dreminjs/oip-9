#pragma once
#include "deque.h"
#include "worker.h"
#include <string>
using namespace std;

bool printError(const string& str);
void clearInput();
bool isValidName(const string& str);
bool inputWorker(Worker &w);
void printList(const Deque& list);
void printTable(const Deque& arr);
bool inputWorker(Worker &w);
void addWorker(Deque* list);