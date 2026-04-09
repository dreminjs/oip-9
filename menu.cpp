#include "menu.h"
#include "Database.h"
#include "user_io.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> menuItems = {
    "Добавить сотрудника в конец",           
    "Добавить в начало",                     
    "Добавить ПЕРЕД элементом (по индексу)", 
    "Добавить ПОСЛЕ элемента (по индексу)",  
    "Удалить элемент (по индексу)",          
    "Переставить два элемента (связи)",      
    "Вывести списком (поле: значение)",      
    "Вывести таблицу",                       
    "Сохранить в файл (перезапись)",
    "Дозапись в файл",
    "Загрузить из файла",
    "Сменить имя файла",
    "Удалить файл БД"
};

void printMenu(const string& dbName)
{
    cout << "\n--- Работа со списком ---";
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
        return -1; 
    }
    return choice;
}

void handleMenuChoice(int choice, List &workers, string &dbName)
{
    int index, k, g;
    Worker w;

    switch (choice)
    {
    case 1:
        if (inputWorker(w)) addLast(workers, w);
        break;

    case 2: 
        if (inputWorker(w)) addFirst(workers, w);
        break;

    case 3: 
        cout << "Введите индекс: "; cin >> index;
        if (inputWorker(w)) {
            if (!addBefore(workers, index, w)) cout << "Ошибка: неверный индекс!\n";
        }
        break;

    case 4: 
        cout << "Введите индекс: "; cin >> index;
        if (inputWorker(w)) {
            if (!addAfter(workers, index, w)) cout << "Ошибка: неверный индекс!\n";
        }
        break;

    case 5: 
        cout << "Введите индекс для удаления: "; cin >> index;
        if (!removeByIndex(workers, index)) cout << "Ошибка: элемент не найден!\n";
        break;

    case 6: 
        cout << "Введите индексы k и g для обмена: ";
        cin >> k >> g;
        swapNodes(workers, k, g);
        break;

    case 7: 
        printList(workers);
        break;

    case 8: 
        printTable(workers);
        break;

    case 9:
        save_DB(dbName, workers);
        break;

    case 10:
        append_DB(dbName, workers);
        break;

    case 11:
        load_DB(dbName, workers);
        break;

    case 12:
        cout << "Введите новое имя файла: ";
        cin >> dbName;
        break;

    case 13:
        if (remove_DB(dbName)) cout << "Файл удален.\n";
        break;

    case 0:
        break;
    }
}