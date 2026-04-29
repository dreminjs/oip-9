#pragma once
#include "deque.h"
#include "worker.h"
#include <string>
using namespace std;

bool printError(const string& str);
void clearInput();
bool isValidName(const string& str);
bool inputWorker(Worker &w);
bool inputWorker(Worker &w);
void addWorker(Deque* list);
int visibleLen(const string& s);
string padRight(const string& s, int width);
string padLeft(const string& s, int width);