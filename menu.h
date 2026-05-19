#pragma once
#include "linkedList.h"
#include <string>

using namespace std;

void printMenu(const string& dbName);

int getMenuChoice(int& choice);

void handleMenuChoice(int choice, LinkedList& workers, string& dbName);
