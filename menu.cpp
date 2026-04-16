#include "menu.h"
#include "database.h"
#include "user_io.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> menuItems = {
    "Добавить сотрудника в начало (pushFront)",   
    "Добавить сотрудника в конец  (pushBack)",    
    "Извлечь из начала            (popFront)",    
    "Извлечь из конца             (popBack)",     
    "Просмотр начала без удаления (front)",       
    "Просмотр конца без удаления  (back)",        
    "Вывести деку списком",                       
    "Вывести деку таблицей",                      
    "Очистить деку",                              
    "Сохранить в файл (перезапись)",              
    "Загрузить из файла",                         
    "Сменить имя файла",                          
    "Удалить файл БД"                             
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

    case 0:
        break;
    }
}