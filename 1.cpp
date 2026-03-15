#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <cstdio>
#include <cctype>

using namespace std;

const int W_NUM = 2;
const int W_NAME = 20;
const int W_EXP = 2;
const int W_DEPT = 2;
const int W_DATE = 10;
const int W_JOB = 25;

string makeCell(int width)
{
    return "+" + string(width + 2 , '-');
}
string centerCell(const string &text, int width)
{
    int visLen = 0;
    for (size_t i = 0; i < text.size(); )
    {
        visLen++;
        if ((unsigned char)text[i] >= 0x80) i += 2; 
        else i += 1;
    }

    int padding = (width > visLen) ? (width - visLen) : 0;
    int left = padding / 2;
    int right = padding - left;

    return "| " + string(left, ' ') + text + string(right, ' ') + " ";
}

struct Fullname
{
    string surname;
    string name;
    string patronymic;
};

struct Worker
{
    Fullname fio;
    int experience;
    int department_number;
    string job_title;
    int day, month, year;
};

bool printError(const string &str)
{
    cin.clear();
    cin.ignore(10000, '\n');
    cout << str;
    return false;
}

bool isValidName(const string &str)
{
    if (str.empty())
        return false;

    for (size_t i = 0; i < str.size();)
    {
        unsigned char c = str[i];
        if (c >= 'A' && c <= 'Z')
        {
            i += 1;
            continue;
        }
        if (c >= 'a' && c <= 'z')
        {
            i += 1;
            continue;
        }
        if (c == 0xD0 || c == 0xD1)
        {
            i += 2;
            continue;
        }
        return false;
    }
    return true;
}

bool inputWorker(Worker &w)
{
    cout << "Введите фамилию: ";
    cin >> w.fio.surname;
    if (!isValidName(w.fio.surname))
    {
        cout << ">>> Ошибка! Фамилия должна содержать только буквы.\n";
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
        return printError(">>> Ошибка отдела!\n");
    }

    cout << "Введите месяц (1-12): ";
    if (!(cin >> w.month) || w.month <= 1 || w.month > 12)
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
        return printError(">>> Некорректно введенеа должность!\n");
    }

    return true;
}
void printWorkerPlain(const Worker &w)
{
    cout << "ФИО: " << w.fio.surname << " " << w.fio.name << " " << w.fio.patronymic << endl;
    cout << "Стаж: " << w.experience << " лет" << endl;
    cout << "Номер отдела: " << w.department_number << endl;
    printf("Дата приема: %02d.%02d.%d\n", w.day, w.month, w.year);
    cout << "Должность: " << w.job_title << endl;
    cout << "---------------------------" << endl;
}

void printTable(const Worker *arr, const int &size)
{
    if (size == 0)
    {
        cout << "\nСписок пуст!\n";
        return;
    }

    string line = makeCell(W_NUM) + makeCell(W_NAME) + makeCell(W_EXP) + makeCell(W_DEPT) + makeCell(W_DATE) + makeCell(W_JOB) + "+";

    string header = centerCell("№", W_NUM) + centerCell("ФИО", W_NAME) + centerCell("Стаж", W_EXP) + centerCell("Отд.", W_DEPT) + centerCell("Дата", W_DATE) + centerCell("Должность", W_JOB) + "|";

    cout << "\n"
         << line << endl;
    cout << header << endl;
    cout << line << endl;

    for (int i = 0; i < size; i++)
    {
        string full_name = arr[i].fio.surname + " " + arr[i].fio.name[0] + "." + arr[i].fio.patronymic[0] + ".";
        printf("| %-*d | %-*.*s | %-*d | %-*d | %02d.%02d.%-4d | %-*.*s |\n",
               W_NUM, i + 1,
               W_NAME, W_NAME, full_name.c_str(),
               W_EXP, arr[i].experience,
               W_DEPT, arr[i].department_number,
               arr[i].day, arr[i].month, arr[i].year,
               W_JOB, W_JOB, arr[i].job_title.c_str());
    }
    cout << line << endl;
}

void addWorker(Worker *&arr, int &size)
{
    Worker *temp = new Worker[size + 1];
    for (size_t i = 0; i < size; i++)
    {

        temp[i] = arr[i];
    }

    cout << "\nВвод нового сотрудника:\n";
    if (inputWorker(temp[size]))
    {
        delete[] arr;
        arr = temp;
        size++;
        cout << "--- Запись успешно добавлена! ---\n";
    }
    else
    {
        delete[] temp;
    }
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int size = 0;              // текущий размер динамический массива
    Worker *workers = nullptr; // указатель на динамический массив

    int choice; ///
    do
    {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1 — Добавить сотрудника\n";
        cout << "2 — Вывести списком (поле: значение)\n";
        cout << "3 — Вывести таблицу\n";
        cout << "0 — Выход\n";
        cout << "Выбор: ";

        if (!(cin >> choice) || choice < 0 || choice > 3)
        {
            cout << "\nОшибка: выберите пункт от 0 до 3!\n";
            cin.clear();
            cin.ignore(10000, '\n');

            choice = -1;
            continue;
        }

        switch (choice)
        {
        case 1:
            addWorker(workers, size);
            break;
        case 2:
            for (int i = 0; i < size; i++)
            {
                cout << "\nЗапись №" << i + 1 << endl;
                printWorkerPlain(workers[i]);
            }
            break;
        case 3:
            printTable(workers, size);
            break;
        }
    } while (choice != 0);

    delete[] workers;
    return 0;
}