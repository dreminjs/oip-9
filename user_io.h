#pragma once

#include "worker.h"
#include <string>
using namespace std;

bool printError(const string& str);
void clearInput();
bool isValidName(const string& str);
bool inputWorker(Worker &w);
void printList(const Worker* arr, int size);
void printTable(const Worker* arr, int size);
void clear(Worker*& arr, int& size);
bool inputWorker(Worker &w);
void addWorker(Worker*& arr, int& size);