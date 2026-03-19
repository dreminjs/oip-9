#ifndef DATABASE_H
#define DATABASE_H

#include "Worker.h"
#include <fstream>
#include <iostream>
#include <string>

std::ofstream new_DB(const std::string& filename);
bool remove_DB(const std::string& filename);
void clear(Worker*& arr, int& size);
void save_DB(const std::string& filename, const Worker* arr, int size, bool append);
void append_DB(const std::string& filename, const Worker* arr, int size);
int load_DB(const std::string& filename, Worker*& arr);

#endif