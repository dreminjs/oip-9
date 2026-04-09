#pragma once
#include "linked_list.h"
#include "worker.h"
#include <string>
using namespace std;

bool printError(const string& str);
void clearInput();
bool isValidName(const string& str);
bool inputWorker(Worker &w);
void printList(const List& list);
void printTable(const List& arr);
bool inputWorker(Worker &w);
void addWorker(List& list);