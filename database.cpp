#include "database.h"
#include "user_io.h"

using namespace std;

ofstream new_DB(const string& filename) {

    ofstream ofs(filename, ios::out | ios::trunc);

    if (ofs.fail()) {

        cerr << ">>> Ошибка: Не удалось создать файл!" << endl;
    }

    return ofs;

}

bool remove_DB(const string& filename) {
    if (std::remove(filename.c_str()) == 0) {   
        return true;
    } else {
        printError(">>> Ошибка удаления");
        return false;
    }
}

void save_DB(const string& filename, const List& list) {
    ofstream ofs(filename, ios::out | ios::trunc);
    if (ofs.fail()) return;

    ofs << list.size << "\n";
    Node* curr = list.head;
    while (curr) {
        Worker& w = curr->data;
        ofs << w.fio.surname << " " << w.fio.name << " " << w.fio.patronymic << "\n";
        ofs << w.experience << " " << w.department_number << "\n";
        ofs << w.day << " " << w.month << " " << w.year << "\n";
        ofs << w.job_title << "\n";
        curr = curr->next;
    }
    ofs.close();
}

void append_DB(const string& filename, const List& list) {
    List fileData;
    initList(fileData);
    load_DB(filename, fileData); 

    Node* curr = list.head;
    while (curr != nullptr) {
        addLast(fileData, curr->data);
        curr = curr->next;
    }

    save_DB(filename, fileData);

    clearList(fileData);
}

void load_DB(const string& filename, List& list) { 
    ifstream ifs(filename);
    if (ifs.fail()) return;

    clearList(list); 
    int count;
    if (!(ifs >> count)) return;

    list.size = count;

    for (int i = 0; i < count; i++) {
        Worker w;
        ifs >> w.fio.surname >> w.fio.name >> w.fio.patronymic;
        ifs >> w.experience >> w.department_number;
        ifs >> w.day >> w.month >> w.year;
        ifs >> ws;
        getline(ifs, w.job_title);
        addLast(list, w);
    }
    ifs.close();
}