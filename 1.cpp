#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <cstdio>
#include <cctype>

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

bool isValidName(string str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isalpha((unsigned char)c) && (unsigned char)c < 128) {
             if (isdigit(c) || ispunct(c)) return false;
        }
    }
    return true;
}

bool isValidDate(int d, int m, int y) {
    if (y < 1900 || y > 2100) return false;
    struct tm t = {0};
    t.tm_mday = d;
    t.tm_mon = m - 1; 
    t.tm_year = y - 1900; 
    t.tm_isdst = -1;
    struct tm copy = t;
    if (mktime(&copy) == -1) return false;
    return (copy.tm_mday == t.tm_mday && copy.tm_mon == t.tm_mon && copy.tm_year == t.tm_year);
}

bool inputWorker(Worker &w) {
    cout << "Введите фамилию: ";
    cin >> w.fio.surname;
    cout << "Введите имя: ";
    cin >> w.fio.name;
    cout << "Введите отчество: ";
    cin >> w.fio.patronymic;

    if (!isValidName(w.fio.surname) || !isValidName(w.fio.name) || !isValidName(w.fio.patronymic)) {
        cout << ">>> Ошибка! ФИО должно содержать только буквы.\n";
        return false;
    }

    cout << "Введите стаж (лет): ";
    if (!(cin >> w.experience) || w.experience < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << ">>> Ошибка стажа!\n";
        return false;
    }

    cout << "Введите номер отдела: ";
    if (!(cin >> w.department_number) || w.department_number <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << ">>> Ошибка отдела!\n";
        return false;
    }

    cout << "Введите дату приема (ДЕНЬ МЕСЯЦ ГОД): ";
    if (!(cin >> w.day >> w.month >> w.year) || !isValidDate(w.day, w.month, w.year)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << ">>> Ошибка даты!\n";
        return false;
    }

    cin.ignore(10000, '\n');
    cout << "Введите должность: ";
    getline(cin, w.job_title);
    return true;
}

void printWorkerPlain(const Worker &w) {
    cout << "ФИО: " << w.fio.surname << " " << w.fio.name << " " << w.fio.patronymic << endl;
    cout << "Стаж: " << w.experience << " лет" << endl;
    cout << "Номер отдела: " << w.department_number << endl;
    printf("Дата приема: %02d.%02d.%d\n", w.day, w.month, w.year);
    cout << "Должность: " << w.job_title << endl;
    cout << "---------------------------" << endl;
}

void printTable(Worker *arr, int size) {
    if (size == 0) {
        cout << "\nСписок пуст!\n";
        return;
    }
    string line = "+----+--------------------------------+----+----+------------+-----------------------+";
    cout << "\n" << line << endl;
    cout << "| №  |              ФИО               |Стаж|Отд.|    Дата    |       Должность       |" << endl;
    cout << line << endl;

    for (int i = 0; i < size; i++) {
        string full_name = arr[i].fio.surname + " " + arr[i].fio.name[0] + "." + arr[i].fio.patronymic[0] + ".";
        printf("| %-2d | %-30.30s | %-2d | %-2d | %02d.%02d.%-4d | %-21.21s |\n", 
               i + 1, full_name.c_str(), arr[i].experience, arr[i].department_number, 
               arr[i].day, arr[i].month, arr[i].year, arr[i].job_title.c_str());
    }
    cout << line << endl;
}

void addWorker(Worker *&arr, int &size) {
    Worker *temp = new Worker[size + 1];
    for (int i = 0; i < size; i++) temp[i] = arr[i];

    cout << "\nВвод нового сотрудника:\n";
    if (inputWorker(temp[size])) {
        delete[] arr;
        arr = temp;
        size++;
        cout << "--- Запись успешно добавлена! ---\n";
    } else {
        delete[] temp;
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int size = 0;
    Worker *workers = new Worker[0]; 

    int choice;
    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1 — Добавить сотрудника\n";
        cout << "2 — Вывести списком (поле: значение)\n";
        cout << "3 — Вывести таблицу\n";
        cout << "0 — Выход\n";
        cout << "Выбор: ";

        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: addWorker(workers, size); break;
            case 2: 
                for(int i=0; i<size; i++) {
                    cout << "\nЗапись №" << i+1 << endl;
                    printWorkerPlain(workers[i]);
                }
                break;
            case 3: printTable(workers, size); break;
        }
    } while (choice != 0);

    delete[] workers;
    return 0;
}