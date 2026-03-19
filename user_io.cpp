#include "user_io.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>

bool printError(const std::string &str) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << str;
    return false;
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isValidName(const std::string& str) {
    if (str.empty()) return false;
    for (unsigned char c : str) {
        if (!std::isalpha(c) && c < 128) return false;
    }
    return true;
}

bool inputWorker(Worker &w) {
    std::cout << "Введите фамилию: ";
    std::cin >> w.fio.surname;
    if (!isValidName(w.fio.surname)) {
        std::cout << ">>> Ошибка! Фамилия должна содержать только буквы.\n";
        return printError(">>> Ошибка! Фамилия должна содержать только буквы");
    }

    std::cout << "Введите имя: ";
    std::cin >> w.fio.name;
    if (!isValidName(w.fio.name)) {
        return printError(">>> Ошибка! Некорректное имя");
    }

    std::cout << "Введите отчество: ";
    std::cin >> w.fio.patronymic;
    if (!isValidName(w.fio.patronymic)) {
        return printError(">>> Ошибка! Некорректное отчество");
    }

    std::cout << "Введите стаж (лет): ";
    if (!(std::cin >> w.experience) || w.experience < 0) {
        return printError(">>> Ошибка стажа!\n");
    }

    std::cout << "Введите номер отдела: ";
    if (!(std::cin >> w.department_number) || w.department_number <= 0) {
        return printError(">>> Ошибка отдела!\n");
    }

    std::cout << "Введите год приема: ";
    if (!(std::cin >> w.year) || w.year <= 1945 || w.year > 2026) {
        return printError(">>> Не корректный год!\n");
    }

    std::cout << "Введите месяц (1-12): ";
    if (!(std::cin >> w.month) || w.month < 0 || w.month > 12) {
        return printError(">>> Ошибка месяца!\n");
    }

    bool leapYear = (w.year % 4 == 0 && w.year % 100 != 0);
    int daysInMonth[] = {31, leapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[w.month - 1];

    std::cout << "Введите день (1-" << maxDay << "): ";
    if (!(std::cin >> w.day) || w.day < 1 || w.day > maxDay) {
        return printError(">>> Ошибка дня!\n");
    }

    std::cout << "Введите должность: ";
    std::cin.ignore(10000, '\n');
    if (!(std::getline(std::cin, w.job_title))) {
        return printError(">>> Некорректно веденна должность!\n");
    }

    return true;
}

void printTable(const Worker* arr, int size) {
    if (size == 0) {
        std::cout << "\n--- Список пуст ---\n";
        return;
    }
    std::cout << std::setfill('-') << std::setw(100) << "-" << std::setfill(' ') << std::endl;
    std::cout << "| " << std::setw(W_NUM)  << std::left  << "№"
              << " | " << std::setw(W_NAME) << std::left  << "ФИО"
              << " | " << std::setw(W_EXP)  << std::right << "Стаж"
              << " | " << std::setw(W_DEPT) << std::right << "Отдел"
              << " | " << std::setw(10)     << std::left  << "Дата"
              << " | " << std::setw(W_JOB)  << std::left  << "Должность"
              << " |" << std::endl;
    std::cout << std::setfill('-') << std::setw(100) << "-" << std::setfill(' ') << std::endl;

    for (int i = 0; i < size; i++) {
        std::string shortName = arr[i].fio.surname + " " + arr[i].fio.name[0] + "."
            + arr[i].fio.patronymic[0] + ".";

        std::ostringstream date;
        date << std::setw(2) << std::setfill('0') << arr[i].day << "."
             << std::setw(2) << std::setfill('0') << arr[i].month << "."
             << std::setw(4) << std::setfill('0') << arr[i].year;

        std::cout << std::setfill(' ');
        std::cout << "| " << std::setw(W_NUM)  << std::right << i + 1
                  << " | " << std::setw(W_NAME) << std::left  << shortName
                  << " | " << std::setw(W_EXP)  << std::right << arr[i].experience
                  << " | " << std::setw(W_DEPT) << std::right << arr[i].department_number
                  << " | " << std::setw(10)     << std::left  << date.str()
                  << " | " << std::setw(W_JOB)  << std::left  << arr[i].job_title
                  << " |" << std::endl;
    }
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

