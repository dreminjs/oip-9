#pragma once
 
#include "linkedList.h"
#include <fstream>
#include <iostream>
#include <string>
 
using namespace std;
 
ofstream new_DB   (const string& filename);
bool     remove_DB(const string& filename);
void     save_DB  (const string& filename, const LinkedList& d);
void     append_DB(const string& filename, const LinkedList& d);
void     load_DB  (const string& filename, LinkedList& d);
 