#include "user_io.h"
#include "linkedList.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;
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
    cin.clear();
    cin.ignore(10000, '\n');
    cout << str;
    return false;
}

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidName(const string &str) {
    if (str.empty()) return false;
    if (str.length() < 2 || str.length() > 50) return false;
    
    for (unsigned char c : str) {
        if (c < 128 && !isalpha(c)) return false;
    }
    return true;
}
void addWorker(LinkedList* list)
{
    Worker w;
    if (inputWorker(w))
    {
        pushBack(list, w); 
        cout << "Сотрудник успешно добавлен.\n";
    }
    else
    {
        cout << "Ошибка ввода данных.\n";
    }
}

bool inputWorker(Worker &w)
{
    cout << "Введите фамилию: ";
    getline(cin >> ws, w.fio.surname);
    if (w.fio.surname.empty() || !isValidName(w.fio.surname))
    {
        return printError(">>> Ошибка! Фамилия должна содержать только буквы");
    }

    cout << "Введите имя: ";
    getline(cin >> ws, w.fio.name);
    if (w.fio.name.empty() || !isValidName(w.fio.name))
    {
        return printError(">>> Ошибка! Некорректное имя");
    }

    cout << "Введите отчество: (Если у вас нет Отчества то просто -) ";
    getline(cin >> ws, w.fio.patronymic);

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

void clear(Worker *&arr, int &size)
{
    if (arr != nullptr)
    {
        delete[] arr;
        arr = nullptr;
    }
    size = 0;
}

void printTable(const LinkedList &list)
{
    if (list.size == 0)
    {
        cout << "\n--- Список пуст ---\n";
        return;
    }

    int totalWidth = W_NUM + W_NAME + W_EXP + W_DEPT + W_DATE + W_JOB + 13;

    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;

    cout << "| " << setw(W_NUM) << left << "№"
         << " | " << setw(W_NAME) << left << "ФИО"
         << " | " << setw(W_EXP) << right << "Стаж"
         << " | " << setw(W_DEPT) << right << "Отдел"
         << " | " << setw(W_DATE) << left << "Дата"
         << " | " << setw(W_JOB) << left << "Должность"
         << " |" << endl;

    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;

    Node *current = list.head;

    int i = 1;

    while (current)
    {
        Worker &w = current->data;

        string shortName = w.fio.surname + " " +
                           w.fio.name[0] + "." +
                           w.fio.patronymic[0] + ".";

        ostringstream date;
        date << setw(2) << setfill('0') << w.day << "."
             << setw(2) << setfill('0') << w.month << "."
             << setw(4) << w.year;

        cout << "| " << setw(W_NUM) << right << i
             << " | " << setw(W_NAME) << left << shortName
             << " | " << setw(W_EXP) << right << w.experience
             << " | " << setw(W_DEPT) << right << w.department_number
             << " | " << setw(W_DATE) << left << date.str()
             << " | " << setw(W_JOB) << left << w.job_title
             << " |" << endl;

        current = current->next;
        i++;
    }

    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;
}

void printList(LinkedList &list)
{
    if (list.size == 0)
    {
        cout << "\n--- Список пуст ---\n";
        return;
    }

    Node *current = list.head;

    int index = 1;

    while (current)
    {
        Worker& currentWorker = (current->data);
        cout << "\n--- Сотрудник #" << (index + 1) << " ---\n";
        cout << "Фамилия: " << currentWorker.fio.surname << "\n";
        cout << "Имя: " << currentWorker.fio.name << "\n";
        cout << "Отчество: " << currentWorker.fio.patronymic << "\n";
        cout << "Стаж: " << currentWorker.experience << "\n";
        cout << "Номер отдела: " << currentWorker.department_number << "\n";
        cout << "Дата приема: " << currentWorker.day << "." << currentWorker.month << "." << currentWorker.year << "\n";
        cout << "Должность: " << currentWorker.job_title << "\n";
        current = current->next;
        index++;
    }
}
