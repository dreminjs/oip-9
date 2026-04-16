#pragma once
 
#include "deque.h"
#include <fstream>
#include <iostream>
#include <string>
 
using namespace std;
 
ofstream new_DB   (const string& filename);
bool     remove_DB(const string& filename);
void     save_DB  (const string& filename, const Deque& d);
void     append_DB(const string& filename, const Deque& d);
void     load_DB  (const string& filename, Deque& d);
 