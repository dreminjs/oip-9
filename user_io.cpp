#include "user_io.h"
#include "deque.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>

int visibleLen(const string& s)
{
    int len = 0;
    int i   = 0;
    while (i < (int)s.size())
    {
        unsigned char c = s[i];
        if (c < 0x80)
        {
            i   += 1;   
            len += 1;   
        }
        else if (c < 0xE0)
        {
            i   += 2;   
            len += 1;   
        }
        else if (c < 0xF0)
        {
            i   += 3;   
            len += 1;   
        }
        else
        {
            i   += 4;   
            len += 2;   
        }
    }
    return len;
}

string padRight(const string& s, int width)
{
    int pad = width - visibleLen(s);
    return s + string(max(pad, 0), ' ');
}

string padLeft(const string& s, int width)
{
    int pad = width - visibleLen(s);
    return string(max(pad, 0), ' ') + s;
}

bool printError(const string &str)
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << str;
    return false;
}

void clearInput()
{
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidName(const string &str)
{
    if (str.empty())
        return false;
    for (unsigned char c : str)
    {
        if (!isalpha(c) && c < 128)
            return false;
    }
    return true;
}

void addWorker(Deque* list)
{
    Worker w;
    if (inputWorker(w))
    {
        pushBack(list, w); 
        std::cout << "Сотрудник успешно добавлен.\n";
    }
    else
    {
        std::cout << "Ошибка ввода данных.\n";
    }
}

bool inputWorker(Worker &w)
{
    cout << "Введите фамилию: ";
    cin >> w.fio.surname;
    if (!isValidName(w.fio.surname))
    {
        return printError(">>> Ошибка! Фамилия должна содержать только буквы");
    }

    cout << "Введите имя: ";
    cin >> w.fio.name;
    if (!isValidName(w.fio.name))
    {
        return printError(">>> Ошибка! Некорректное имя");
    }

    cout << "Введите отчество: ";
    cin >> w.fio.patronymic;
    if (!isValidName(w.fio.patronymic))
    {
        return printError(">>> Ошибка! Некорректное отчество");
    }

    cout << "Введите стаж (лет): ";
    if (!(cin >> w.experience) || w.experience < 0)
    {
        return printError(">>> Ошибка стажа!\n");
    }

    cout << "Введите номер отдела: ";
    if (!(cin >> w.department_number) || w.department_number <= 0)
    {
        return printError(">>> Ошибка отдела!\n");
    }

    cout << "Введите год приема: ";
    if (!(cin >> w.year) || w.year <= 1945 || w.year > 2026)
    {
        return printError(">>> Не корректный год!\n");
    }

    cout << "Введите месяц (1-12): ";
    if (!(cin >> w.month) || w.month < 0 || w.month > 12)
    {
        return printError(">>> Ошибка месяца!\n");
    }

    bool leapYear = (w.year % 4 == 0 && w.year % 100 != 0);
    int daysInMonth[] = {31, leapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[w.month - 1];

    cout << "Введите день (1-" << maxDay << "): ";
    if (!(cin >> w.day) || w.day < 1 || w.day > maxDay)
    {
        return printError(">>> Ошибка дня!\n");
    }

    cout << "Введите должность: ";
    cin.ignore(10000, '\n');
    if (!(getline(cin, w.job_title)))
    {
        return printError(">>> Некорректно веденна должность!\n");
    }

    return true;
}

