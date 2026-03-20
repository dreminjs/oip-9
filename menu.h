#pragma once

#include <string>

using namespace std;

void printMenu(const std::string& dbName);

int getMenuChoice(int& choice);

void handleMenuChoice(int choice, class Worker*& workers, int& size, std::string& dbName);
