#include <iostream>
#include <windows.h>
#include "Database.h"
#include "user_io.h"
#include "menu.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Worker* workers = nullptr;
    int size = 0;
    string dbName = "database.txt";
    int choice;

    do {
        printMenu(dbName);
        getMenuChoice(choice);
        
        if (choice != -1) { 
            handleMenuChoice(choice, workers, size, dbName);
        }
        
    } while (choice != 0);

    clear(workers, size);
    return 0;
}