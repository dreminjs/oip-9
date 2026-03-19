#ifndef USER_IO_H
#define USER_IO_H

#include "worker.h"
#include <string>
using namespace std;

bool printError(const string& str);
void clearInput();
bool isValidName(const string& str);
bool inputWorker(Worker &w);
void printList(const Worker* arr, int size);
void printTable(const Worker* arr, int size);

#endif // USER_IO_H

