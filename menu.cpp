#include "menu.h"
#include "Database.h"
#include "user_io.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> menuItems = {
    "Добавить сотрудника",
    "Вывести списком (поле: значение)",
    "Вывести таблицу",
    "Сохранить в файл (перезапись)",
    "Дозапись в файл",
    "Загрузить из файла",
    "Сменить файл",
    "Удалить файл"
};

void printMenu(const string& dbName)
{
    cout << "\nФайл: " << dbName << "\n";
    cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
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

void handleMenuChoice(int choice, Worker*& workers, int& size, string& dbName)
{
    switch (choice) {
        
        case 1: 
            addWorker(workers, size); 
            break;
        case 2: 
            printList(workers, size); 
            break;
        case 3: 
            printTable(workers, size); 
            break;
        case 4: 
            save_DB(dbName, workers, size, false); 
            break;
        case 5: 
            append_DB(dbName, workers, size); 
            break;
        case 6: 
            size = load_DB(dbName, workers); 
            break;
        case 7: {
            cout << "Введите новое имя файла: ";
            cin >> dbName;
            break;
        }
        case 8: 
            remove_DB(dbName); 
            break;
        case 0: 
            break;
    }
}