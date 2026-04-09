#include <iostream>
#include <windows.h>
#include "Database.h"
#include "user_io.h"
#include "menu.h"
#include "linked_list.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    List workers;
    string dbName = "database.txt";
    int choice;

    do {
        printMenu(dbName);
        getMenuChoice(choice);
        
        if (choice != -1) { 
            handleMenuChoice(choice, workers, dbName);
        }
        
    } while (choice != 0);

    clearList(workers);
    return 0;
}