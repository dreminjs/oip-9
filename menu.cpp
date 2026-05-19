#include "menu.h"
#include "database.h"
#include "user_io.h"
#include "sort.h"
#include "search.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const char *menuItems[21] = {
    "Добавить сотрудника в начало (pushFront)", //  1
    "Добавить сотрудника в конец  (pushBack)",  //  2
    "Извлечь из начала            (popFront)",  //  3
    "Извлечь из конца             (popBack)",   //  4
    "Просмотр начала без удаления (front)",     //  5
    "Просмотр конца без удаления  (back)",      //  6
    "Вывести список",                           //  7
    "Вывести список таблицей",                  //  8
    "Очистить список",                          //  9
    "Сохранить в файл (перезапись)",            // 10
    "Загрузить из файла",                       // 11
    "Сменить имя файла",                        // 12
    "Удалить файл БД",                          // 13
    "Быстрая сортировка (Хоара)",               // 14
    "Загрузить тестовые данные",                // 15
    // Поиск
    "Линейный поиск по должности",     // 16
    "Линейный поиск по номеру отдела", // 17
    "Бинарный поиск по фамилии",       // 18
    // Фильтрация
    "Фильтр: совпадение начала фамилии",    // 19
    "Фильтр: подстрока в фамилии",          // 20
    "Фильтр: диапазон первой буквы фамилии" // 21
};

const int MENU_SIZE = sizeof(menuItems) / sizeof(menuItems[0]);

void printMenu(const string &dbName)
{
    cout << "\n========== Список сотрудников ==========";
    cout << "\nФайл: " << dbName << "\n";
    for (size_t i = 0; i < MENU_SIZE; i++)
    {
        if (i == 15)
            cout << "--- Поиск ---\n";
        if (i == 18)
            cout << "--- Фильтрация по фамилии ---\n";
        cout << i + 1 << " — " << menuItems[i] << "\n";
    }
    cout << "0 — Выход\n";
    cout << "Выбор: ";
}

int getMenuChoice(int &choice)
{
    if (!(cin >> choice) || choice < 0 || choice > static_cast<int>(MENU_SIZE))
    {
        cout << "\nОшибка: выберите пункт от 0 до " << MENU_SIZE << "!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        choice = -1;
        return -1;
    }
    return choice;
}

static bool askSortParams(SortField &field, bool &ascending)
{
    int fieldChoice = 0;
    cout << "\nВыберите поле сортировки:\n"
         << "  1 — Фамилия (строковое)\n"
         << "  2 — Стаж    (числовое)\n"
         << "Выбор: ";
    if (!(cin >> fieldChoice) || (fieldChoice != 1 && fieldChoice != 2))
    {
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
    if (!(cin >> orderChoice) || (orderChoice != 1 && orderChoice != 2))
    {
        cout << "Неверный выбор порядка!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    ascending = (orderChoice == 1);
    return true;
}

static void offerEditDelete(LinkedList &workers, Node **found, int count,
                            bool &sortedBySurname)
{
    if (!found || count == 0)
        return;

    cout << "\nРедактировать или удалить найденные элементы? (1 — Да, 0 — Нет): ";
    int ans = 0;
    if (!(cin >> ans) || ans != 1)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    editOrDeleteFound(&workers, found, count);
    sortedBySurname = false;
}

void handleMenuChoice(int choice, LinkedList &workers, string &dbName)
{
    Worker w;

    static bool sortedBySurname = false;

    switch (choice)
    {

    case 1:
        if (inputWorker(w))
        {
            pushFront(&workers, w);
            sortedBySurname = false;
            cout << "Сотрудник добавлен в начало списка.\n";
        }
        break;

    case 2:
        if (inputWorker(w))
        {
            pushBack(&workers, w);
            sortedBySurname = false;
            cout << "Сотрудник добавлен в конец списка\n";
        }
        break;

    case 3:
        if (isEmpty(&workers))
        {
            cout << "Список пуст\n";
        }
        else
        {
            w = popFront(&workers);
            sortedBySurname = false;
            cout << "\nИзвлечён из начала:\n";
            printWorker(w);
        }
        break;

    case 4:
        if (isEmpty(&workers))
        {
            cout << "Список пуст — нечего извлекать.\n";
        }
        else
        {
            w = popBack(&workers);
            sortedBySurname = false;
            cout << "\nИзвлечён из конца:\n";
            printWorker(w);
        }
        break;

    case 5:
        if (isEmpty(&workers))
            cout << "Список пуста.\n";
        else
        {
            cout << "\nНачало списка (без удаления):\n";
            printWorker(front(&workers));
        }
        break;

    case 6:
        if (isEmpty(&workers))
            cout << "Список пуста\n";
        else
        {
            cout << "\nКонец списка (без удаления):\n";
            printWorker(back(&workers));
        }
        break;

    case 7:
        printLinkedList(&workers);
        break;
    case 8:
        printLinkedListTable(&workers);
        break;

    case 9:
        clear(&workers);
        sortedBySurname = false;
        break;

    case 10:
        save_DB(dbName, workers);
        cout << "Список сохранен в файл «" << dbName << "».\n";
        break;

    case 11:
        load_DB(dbName, workers);
        sortedBySurname = false;
        cout << "Список загружен из файла «" << dbName << "». Элементов: "
             << getSize(&workers) << "\n";
        break;

    case 12:
    {
        string newName;
        cout << "Введите новое имя файла: ";
        cin >> newName;

        if (rename(dbName.c_str(), newName.c_str()) == 0)
        {
            dbName = newName;
            cout << "Файл переименован в «" << dbName << "».\n";
        }
        else
        {
            cout << "Ошибка переименования. Возможно, старый файл не существует.\n";
        }
        break;
    }

    case 13:
        if (remove(dbName.c_str()) == 0)
            cout << "Файл «" << dbName << "» удалён.\n";
        else
            cout << "Ошибка удаления файла.\n";
        break;
    case 14:
    {
        if (isEmpty(&workers))
        {
            cout << "Список пуста — нечего сортировать.\n";
            break;
        }
        SortField field;
        bool ascending;
        if (!askSortParams(field, ascending))
            break;

        cout << "\nДо сортировки:\n";
        printLinkedListTable(&workers);

        sortDequeQuick(&workers, field, ascending);

        sortedBySurname = (field == FIELD_SURNAME && ascending);

        cout << "\nПосле быстрой сортировки Хоара ("
             << (field == FIELD_SURNAME ? "фамилия" : "стаж") << ", "
             << (ascending ? "по возрастанию" : "по убыванию") << "):\n";
        printLinkedListTable(&workers);
        break;
    }

    case 15:
        loadSampleData(&workers);
        sortedBySurname = false;
        cout << "Текущий Список:\n";
        printLinkedListTable(&workers);
        break;

    case 16:
    {
        if (isEmpty(&workers))
        {
            cout << "Список пуст.\n";
            break;
        }

        cout << "Введите должность для поиска: ";
        cin.ignore(10000, '\n');
        string jobTitle;
        getline(cin, jobTitle);

        int count = 0;
        Node **found = linearSearchByJob(&workers, jobTitle, count);

        if (!found)
        {
            cout << "  >>> Сотрудников с должностью «" << jobTitle << "» не найдено.\n";
            break;
        }

        printFound(found, count);
        offerEditDelete(workers, found, count, sortedBySurname);
        delete[] found;
        break;
    }

    case 17:
    {
        if (isEmpty(&workers))
        {
            cout << "Список пуст.\n";
            break;
        }

        cout << "Введите номер отдела для поиска: ";
        int dept;
        if (!(cin >> dept) || dept <= 0)
        {
            cout << "  Некорректный номер отдела.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }

        int count = 0;
        Node **found = linearSearchByDept(&workers, dept, count);

        if (!found)
        {
            cout << "  >>> Сотрудников из отдела №" << dept << " не найдено.\n";
            break;
        }

        printFound(found, count);
        offerEditDelete(workers, found, count, sortedBySurname);
        delete[] found;
        break;
    }

    case 18:
    {
        if (isEmpty(&workers))
        {
            cout << "Список пуст.\n";
            break;
        }

        cout << "Состояние сортировки по фамилии: "
             << (sortedBySurname ? "отсортирована" : "не отсортирована") << "\n";
        cout << "Введите фамилию для поиска: ";
        string surname;
        cin >> surname;

        Node *found = binarySearchBySurname(&workers, surname, sortedBySurname);

        if (!found)
        {
            cout << "  >>> Сотрудник с фамилией «" << surname << "» не найден.\n";
            break;
        }

        cout << "\n  Найден:\n";
        printWorker(found->data);

        Node *arr[1] = {found};
        offerEditDelete(workers, arr, 1, sortedBySurname);
        break;
    }

    case 19:
    {
        if (isEmpty(&workers))
        {
            cout << "Список пуст.\n";
            break;
        }

        cout << "Введите начало фамилии: ";
        string prefix;
        cin >> prefix;

        int count = 0;
        Node **found = filterByPrefix(&workers, prefix, count);

        if (!found)
        {
            cout << "  >>> Фамилий, начинающихся на «" << prefix << "», не найдено.\n";
            break;
        }

        printFound(found, count);
        offerEditDelete(workers, found, count, sortedBySurname);
        delete[] found;
        break;
    }
    case 20:
    {
        if (isEmpty(&workers))
        {
            cout << "Список пуст.\n";
            break;
        }

        cout << "Введите подстроку для поиска в фамилии: ";
        string sub;
        cin >> sub;

        int count = 0;
        Node **found = filterBySubstring(&workers, sub, count);

        if (!found)
        {
            cout << "  >>> Фамилий, содержащих «" << sub << "», не найдено.\n";
            break;
        }

        printFound(found, count);
        offerEditDelete(workers, found, count, sortedBySurname);
        delete[] found;
        break;
    }
    case 21:
    {
        if (isEmpty(&workers))
        {
            cout << "Список пуст.\n";
            break;
        }

        cout << "\nВведите диапазон первой буквы фамилии.\n"
             << "Введите «-» для отсутствия соответствующей границы.\n";

        cout << "Минимальная буква (включительно): ";
        string minL, maxL;
        cin >> minL;
        if (minL == "-")
            minL = "";

        cout << "Максимальная буква (включительно): ";
        cin >> maxL;
        if (maxL == "-")
            maxL = "";

        if (minL.empty() && maxL.empty())
        {
            cout << "  Обе границы не заданы — поиск не выполнен.\n";
            break;
        }

        cout << "  Диапазон: ";
        if (!minL.empty())
            cout << "от «" << minL << "» ";
        if (!maxL.empty())
            cout << "до «" << maxL << "»";
        cout << "\n";

        int count = 0;
        Node **found = filterByLetterRange(&workers, minL, maxL, count);

        if (!found)
        {
            cout << "  >>> Фамилий в заданном диапазоне не найдено.\n";
            break;
        }

        printFound(found, count);
        offerEditDelete(workers, found, count, sortedBySurname);
        delete[] found;
        break;
    }

    case 0:
        break;

    default:
        cout << "Неизвестный пункт меню.\n";
        break;
    }
}