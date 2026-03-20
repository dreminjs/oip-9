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

void save_DB(const string& filename, const Worker* arr, int size, bool append) {
    ios::openmode mode = ios::out | (append ? ios::app : ios::trunc);

    ofstream ofs(filename, mode);
    if (ofs.fail()) {
        cerr << ">>> Ошибка при открытии для записи!\n";
        return;
    }

    if (!append) ofs << size << "\n";

    for (int i = 0; i < size; i++) {
        ofs << arr[i].fio.surname << " " << arr[i].fio.name << " " << arr[i].fio.patronymic << "\n";
        ofs << arr[i].experience << " " << arr[i].department_number << "\n";
        ofs << arr[i].day << " " << arr[i].month << " " << arr[i].year << "\n";
        ofs << arr[i].job_title << "\n";
    }
    ofs.close();
}

void append_DB(const string& filename, const Worker* arr, int size) {
    Worker* existing = nullptr;
    int existingSize = load_DB(filename, existing);

    int totalSize = existingSize + size;
    Worker* combined = (totalSize > 0) ? new Worker[totalSize] : nullptr;

    for (int i = 0; i < existingSize; i++) combined[i] = existing[i];
    for (int i = 0; i < size; i++) combined[existingSize + i] = arr[i];

    save_DB(filename, combined, totalSize, true);

    clear(existing, existingSize);
    delete[] combined;
}

int load_DB(const string& filename, Worker*& arr) {
    ifstream ifs(filename);
    if (ifs.fail()) return 0;

    int newSize;
    if (!(ifs >> newSize)) return 0;

    delete[] arr;
    arr = new Worker[newSize];

    for (int i = 0; i < newSize; i++) {
        ifs >> arr[i].fio.surname >> arr[i].fio.name >> arr[i].fio.patronymic;
        ifs >> arr[i].experience >> arr[i].department_number;
        ifs >> arr[i].day >> arr[i].month >> arr[i].year;
        ifs >> ws;
        getline(ifs, arr[i].job_title);
    }
    ifs.close();
    return newSize;
}