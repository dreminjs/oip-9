#pragma once
#include "deque.h"
#include <string>

using namespace std;

void printMenu(const string& dbName);

int getMenuChoice(int& choice);

void handleMenuChoice(int choice, Deque& workers, string& dbName);
