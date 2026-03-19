#include <iostream>
#include <windows.h>
#include "Database.h"
#include "user_io.h"

using namespace std;

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

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Worker* workers = nullptr;
    int size = 0;
    string dbName = "database.txt";
    int choice;

    do {
        cout << "\nФайл: " << dbName << "\n";
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1 — Добавить сотрудника\n";
        cout << "2 — Вывести списком (поле: значение)\n";
        cout << "3 — Вывести таблицу\n";
        cout << "4 — Сохранить в файл (перезапись)\n";
        cout << "5 — Дозапись в файл\n";
        cout << "6 — Загрузить из файла\n";
        cout << "7 — Сменить файл\n";
        cout << "8 — Удалить файл\n";
        cout << "0 — Выход\n";
        cout << "Выбор: ";

        if (!(cin >> choice) || choice < 0 || choice > 8)
        {
            cout << "\nОшибка: выберите пункт от 0 до 8!\n";
            cin.clear();
            cin.ignore(10000, '\n');

            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: addWorker(workers, size); break;
            case 2: printList(workers, size); break;
            case 3: printTable(workers, size); break;
            case 4: save_DB(dbName, workers, size, false); break;
            case 5: append_DB(dbName, workers, size); break;
            case 6: size = load_DB(dbName, workers); break;
            case 7: {
                cout << "Введите новое имя файла: ";
                cin >> dbName;
                break;
            }
            case 8: remove_DB(dbName); break;
            case 0: break;
        }
    } while (choice != 0);

    clear(workers, size);
    return 0;
}
