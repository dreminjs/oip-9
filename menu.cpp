#include "menu.h"
#include "database.h"
#include "user_io.h"
#include "sort.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> menuItems = {
    "Добавить сотрудника в начало (pushFront)",    //  1
    "Добавить сотрудника в конец  (pushBack)",     //  2
    "Извлечь из начала            (popFront)",     //  3
    "Извлечь из конца             (popBack)",      //  4
    "Просмотр начала без удаления (front)",        //  5
    "Просмотр конца без удаления  (back)",         //  6
    "Вывести деку списком",                        //  7
    "Вывести деку таблицей",                       //  8
    "Очистить деку",                               //  9
    "Сохранить в файл (перезапись)",               // 10
    "Загрузить из файла",                          // 11
    "Сменить имя файла",                           // 12
    "Удалить файл БД",                             // 13
    "Сортировка вставками",                        // 14
    "Быстрая сортировка (Хоара)",                  // 15
    "Загрузить тестовые данные"                    // 16
};

void printMenu(const string& dbName)
{
    cout << "\n========== Дека сотрудников ==========";
    cout << "\nФайл: " << dbName << "\n";
    for (size_t i = 0; i < menuItems.size(); i++)
    {
        cout << i + 1 << " — " << menuItems[i] << "\n";
    }
    cout << "0 — Выход\n";
    cout << "Выбор: ";
}

int getMenuChoice(int& choice)
{
    if (!(cin >> choice) || choice < 0 || choice > static_cast<int>(menuItems.size()))
    {
        cout << "\nОшибка: выберите пункт от 0 до " << menuItems.size() << "!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        choice = -1;
        return -1;
    }
    return choice;
}

static bool askSortParams(SortField& field, bool& ascending)
{
    int fieldChoice = 0;
    cout << "\nВыберите поле сортировки:\n"
         << "  1 — Фамилия (строковое)\n"
         << "  2 — Стаж    (числовое)\n"
         << "Выбор: ";
    if (!(cin >> fieldChoice) || (fieldChoice != 1 && fieldChoice != 2)) {
        cout << "Неверный выбор поля!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    field = (fieldChoice == 1) ? FIELD_SURNAME : FIELD_EXPERIENCE;

    int orderChoice = 0;
    cout << "Порядок сортировки:\n"
         << "  1 — По возрастанию\n"
         << "  2 — По убыванию\n"
         << "Выбор: ";
    if (!(cin >> orderChoice) || (orderChoice != 1 && orderChoice != 2)) {
        cout << "Неверный выбор порядка!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    ascending = (orderChoice == 1);
    return true;
}

void handleMenuChoice(int choice, Deque& workers, string& dbName)
{
    Worker w;

    switch (choice)
    {
    case 1:
        if (inputWorker(w)) {
            pushFront(&workers, w);
            cout << "Сотрудник добавлен в начало деки.\n";
        }
        break;

    case 2:
        if (inputWorker(w)) {
            pushBack(&workers, w);
            cout << "Сотрудник добавлен в конец деки\n";
        }
        break;

    case 3:
        if (isEmpty(&workers)) {
            cout << "Дека пуста\n";
        } else {
            w = popFront(&workers);
            cout << "\nИзвлечён из начала:\n";
            printWorker(w);
        }
        break;

    case 4:
        if (isEmpty(&workers)) {
            cout << "Дека пуста — нечего извлекать.\n";
        } else {
            w = popBack(&workers);
            cout << "\nИзвлечён из конца:\n";
            printWorker(w);
        }
        break;

    case 5:
        if (isEmpty(&workers)) {
            cout << "Дека пуста.\n";
        } else {
            cout << "\nНачало деки (без удаления):\n";
            printWorker(front(&workers));
        }
        break;

    case 6:
        if (isEmpty(&workers)) {
            cout << "Дека пуста\n";
        } else {
            cout << "\nКонец деки (без удаления):\n";
            printWorker(back(&workers));
        }
        break;

    case 7:
        printDeque(&workers);
        break;

    case 8:
        printDequeTable(&workers);
        break;

    case 9:
        clear(&workers);
        break;

    case 10:
        save_DB(dbName, workers);
        cout << "Дека сохранена в файл «" << dbName << "».\n";
        break;

    case 11:
        load_DB(dbName, workers);
        cout << "Дека загружена из файла «" << dbName << "». Элементов: "
             << getSize(&workers) << "\n";
        break;

    case 12:
        cout << "Введите новое имя файла: ";
        cin >> dbName;
        break;

    case 13:
        if (remove(dbName.c_str()) == 0)
            cout << "Файл «" << dbName << "» удалён.\n";
        else
            cout << "Ошибка удаления файла.\n";
        break;

    case 14: {
        if (isEmpty(&workers)) {
            cout << "Дека пуста — нечего сортировать.\n";
            break;
        }
        SortField field;
        bool      ascending;
        if (!askSortParams(field, ascending)) break;

        cout << "\nДо сортировки:\n";
        printDequeTable(&workers);

        sortDequeInsertion(&workers, field, ascending);

        cout << "\nПосле сортировки вставками ("
             << (field == FIELD_SURNAME ? "фамилия" : "стаж") << ", "
             << (ascending ? "по возрастанию" : "по убыванию") << "):\n";
        printDequeTable(&workers);
        break;
    }
    case 15: {
        if (isEmpty(&workers)) {
            cout << "Дека пуста — нечего сортировать.\n";
            break;
        }
        SortField field;
        bool      ascending;
        if (!askSortParams(field, ascending)) break;

        cout << "\nДо сортировки:\n";
        printDequeTable(&workers);

        sortDequeQuick(&workers, field, ascending);

        cout << "\nПосле быстрой сортировки Хоара ("
             << (field == FIELD_SURNAME ? "фамилия" : "стаж") << ", "
             << (ascending ? "по возрастанию" : "по убыванию") << "):\n";
        printDequeTable(&workers);
        break;
    }

    case 16:
        loadSampleData(&workers);
        cout << "Текущая дека:\n";
        printDequeTable(&workers);
        break;

    case 0:
        break;
    }
}