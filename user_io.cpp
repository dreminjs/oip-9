#include "user_io.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

bool printError(const string &str) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << str;
    return false;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidName(const string& str) {
    if (str.empty()) return false;
    for (unsigned char c : str) {
        if (!isalpha(c) && c < 128) return false;
    }
    return true;
}

void addWorker(Worker*& arr, int& size) {
    Worker* temp = new Worker[size + 1];
    for (int i = 0; i < size; i++) temp[i] = arr[i];
    
    if (inputWorker(temp[size])) {
        delete[] arr;
        arr = temp;
        size++;
    } else {
        delete[] temp;
    }
}

bool inputWorker(Worker &w) {
    cout << "Введите фамилию: ";
    cin >> w.fio.surname;
    if (!isValidName(w.fio.surname)) {
        return printError(">>> Ошибка! Фамилия должна содержать только буквы");
    }
    
    cout << "Введите имя: ";
    cin >> w.fio.name;
    if (!isValidName(w.fio.name)) {
        return printError(">>> Ошибка! Некорректное имя");
    }

    cout << "Введите отчество: ";
    cin >> w.fio.patronymic;
    if (!isValidName(w.fio.patronymic)) {
        return printError(">>> Ошибка! Некорректное отчество");
    }

    cout << "Введите стаж (лет): ";
    if (!(cin >> w.experience) || w.experience < 0) {
        return printError(">>> Ошибка стажа!\n");
    }

    cout << "Введите номер отдела: ";
    if (!(cin >> w.department_number) || w.department_number <= 0) {
        return printError(">>> Ошибка отдела!\n");
    }

    cout << "Введите год приема: ";
    if (!(cin >> w.year) || w.year <= 1945 || w.year > 2026) {
        return printError(">>> Не корректный год!\n");
    }

    cout << "Введите месяц (1-12): ";
    if (!(cin >> w.month) || w.month < 0 || w.month > 12) {
        return printError(">>> Ошибка месяца!\n");
    }

    bool leapYear = (w.year % 4 == 0 && w.year % 100 != 0);
    int daysInMonth[] = {31, leapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[w.month - 1];

    cout << "Введите день (1-" << maxDay << "): ";
    if (!(cin >> w.day) || w.day < 1 || w.day > maxDay) {
        return printError(">>> Ошибка дня!\n");
    }

    cout << "Введите должность: ";
    cin.ignore(10000, '\n');
    if (!(getline(cin, w.job_title))) {
        return printError(">>> Некорректно веденна должность!\n");
    }

    return true;
}

void clear(Worker*& arr, int& size) {
    if (arr != nullptr) {
        delete[] arr;
        arr = nullptr;
    }
    size = 0;
}

void printTable(const Worker* arr, int size) {
    if (size == 0) {
        cout << "\n--- Список пуст ---\n";
        return;
    }
    
    int totalWidth = W_NUM + W_NAME + W_EXP + W_DEPT + W_DATE + W_JOB + 13;
    
    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;
    
    cout << "| " << setw(W_NUM)  << left  << "№"
         << " | " << setw(W_NAME) << left  << "ФИО"
         << " | " << setw(W_EXP)  << right << "Стаж"
         << " | " << setw(W_DEPT) << right << "Отдел"
         << " | " << setw(W_DATE) << left  << "Дата"
         << " | " << setw(W_JOB)  << left  << "Должность"
         << " |" << endl;
    
    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;
    
    for (int i = 0; i < size; i++) {
        string shortName = arr[i].fio.surname + " " + 
                           arr[i].fio.name[0] + "." + 
                           arr[i].fio.patronymic[0] + ".";
        
        ostringstream date;
        date << setw(2) << setfill('0') << arr[i].day << "."
             << setw(2) << setfill('0') << arr[i].month << "."
             << setw(4) << arr[i].year;
        
        cout << "| " << setw(W_NUM)  << right << i + 1
             << " | " << setw(W_NAME) << left  << shortName
             << " | " << setw(W_EXP)  << right << arr[i].experience
             << " | " << setw(W_DEPT) << right << arr[i].department_number
             << " | " << setw(W_DATE) << left  << date.str()
             << " | " << setw(W_JOB)  << left  << arr[i].job_title
             << " |" << endl;
    }
    
    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;
}

void printList(const Worker* arr, int size) {
    if (size == 0) {
        std::cout << "\n--- Список пуст ---\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        std::cout << "\n--- Сотрудник #" << (i + 1) << " ---\n";
        std::cout << "Фамилия: " << arr[i].fio.surname << "\n";
        std::cout << "Имя: " << arr[i].fio.name << "\n";
        std::cout << "Отчество: " << arr[i].fio.patronymic << "\n";
        std::cout << "Стаж: " << arr[i].experience << "\n";
        std::cout << "Номер отдела: " << arr[i].department_number << "\n";
        std::cout << "Дата приема: " << arr[i].day << "." << arr[i].month << "." << arr[i].year << "\n";
        std::cout << "Должность: " << arr[i].job_title << "\n";
    }
}

