#ifndef WORKER_H
#define WORKER_H

#include <string>

struct Fullname {
    std::string surname;
    std::string name;
    std::string patronymic;
};

struct Worker {
    Fullname fio;
    int experience;
    int department_number;
    std::string job_title;
    int day, month, year;
};

const int W_NUM = 4;
const int W_NAME = 25;
const int W_EXP = 8;
const int W_DEPT = 8;
const int W_JOB = 20;

#endif