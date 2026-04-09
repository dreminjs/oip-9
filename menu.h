#pragma once
#include "linked_list.h"
#include <string>

using namespace std;

void printMenu(const string& dbName);

int getMenuChoice(int& choice);

void handleMenuChoice(int choice, List& workers, string& dbName);
