#pragma once

#include <string>
using namespace std;
struct Fullname {
    string surname;
    string name;
    string patronymic;
};

struct Worker {
    Fullname fio;
    int experience;
    int department_number;
    string job_title;
    int day, month, year;
};

const int W_NUM = 4;
const int W_NAME = 25;
const int W_EXP = 8;
const int W_DEPT = 8;
const int W_JOB = 20;
const int W_DATE = 10;