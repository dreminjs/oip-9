#pragma once

#include "linked_list.h"
#include "Worker.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ofstream new_DB(const string& filename);
bool remove_DB(const string& filename);
void save_DB(const string& filename, const List& list);
void append_DB(const string& filename, const List& arr);
void load_DB(const string& filename, List& arr);
