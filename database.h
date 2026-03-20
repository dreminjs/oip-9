#pragma once

#include "Worker.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ofstream new_DB(const string& filename);
bool remove_DB(const string& filename);
void clear(Worker*& arr, int& size);
void save_DB(const string& filename, const Worker* arr, int size, bool append);
void append_DB(const string& filename, const Worker* arr, int size);
int load_DB(const string& filename, Worker*& arr);
