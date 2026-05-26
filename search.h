#pragma once
#include "linkedList.h"
#include "sort.h"
#include <string>

using namespace std;


string toLowerStr(const string& s);

string getFirstCharStr(const string& s);

Node** linearSearchByJob (LinkedList* d, const string& jobTitle, int& count);
Node** linearSearchByDept(LinkedList* d, int dept,               int& count);

Node* binarySearchBySurname(LinkedList* d, const string& surname, bool& isSorted);

Node** filterByPrefix(LinkedList* d, const string& prefix, int& count);

Node** filterBySubstring(LinkedList* d, const string& sub, int& count);

Node** filterByLetterRange(LinkedList* d,
                           const string& minLetter,
                           const string& maxLetter,
                           int& count);

void removeNode(LinkedList* d, Node* node);

void printFound(Node** found, int count);

void editOrDeleteFound(LinkedList* d, Node** found, int count);