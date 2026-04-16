#include "database.h"
#include <iostream>

using namespace std;


ofstream new_DB(const string& filename) {
    ofstream ofs(filename, ios::out | ios::trunc);
    if (ofs.fail()) {
        cerr << "Не удалось создать файл!\n";
    }
    return ofs;
}

bool remove_DB(const string& filename) {
    if (remove(filename.c_str()) == 0) {
        return true;
    } else {
        cerr << "Ошибка удаления файла\n";
        return false;
    }
}

void save_DB(const string& filename, const Deque& d) {
    ofstream ofs(filename, ios::out | ios::trunc);
    if (ofs.fail()) {
        cerr << "не удалось открыть файл для записи!\n";
        return;
    }

    ofs << d.size << "\n";

    Node* curr = d.head;
    while (curr) {
        const Worker& w = curr->data;
        ofs << w.fio.surname       << " "
            << w.fio.name          << " "
            << w.fio.patronymic    << "\n";
        ofs << w.experience        << " "
            << w.department_number << "\n";
        ofs << w.day   << " "
            << w.month << " "
            << w.year  << "\n";
        ofs << w.job_title << "\n";
        curr = curr->next;
    }

    ofs.close();
}

void append_DB(const string& filename, const Deque& d) {
    Deque fileData;
    init(&fileData);
    load_DB(filename, fileData);

    Node* curr = d.head;
    while (curr != nullptr) {
        pushBack(&fileData, curr->data);
        curr = curr->next;
    }

    save_DB(filename, fileData);

    while (!isEmpty(&fileData)) {
        popFront(&fileData);
    }
}

void load_DB(const string& filename, Deque& d) {
    ifstream ifs(filename);
    if (ifs.fail()) {
        cerr << "файл " << filename << " не найден\n";
        return;
    }

    while (!isEmpty(&d)) {
        popFront(&d);
    }

    int count = 0;
    if (!(ifs >> count) || count <= 0) {
        ifs.close();
        return;
    }

    for (int i = 0; i < count; i++) {
        Worker w;
        ifs >> w.fio.surname >> w.fio.name >> w.fio.patronymic;
        ifs >> w.experience  >> w.department_number;
        ifs >> w.day >> w.month >> w.year;
        ifs >> ws;                      
        getline(ifs, w.job_title);
        pushBack(&d, w);
    }

    ifs.close();
}