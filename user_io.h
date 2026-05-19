#pragma once
#include "linkedList.h"
#include "worker.h"
#include <string>
using namespace std;

bool printError(const string& str);
void clearInput();
bool isValidName(const string& str);
bool inputWorker(Worker &w);
bool inputWorker(Worker &w);
void addWorker(LinkedList* list);
int visibleLen(const string& s);
string padRight(const string& s, int width);
string padLeft(const string& s, int width);