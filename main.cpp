#include <iostream>
#include <windows.h>
#include "linkedList.h"
#include "database.h"
#include "user_io.h"
#include "menu.h"
 
using namespace std;
 
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
 
    LinkedList workers;
    init(&workers);
    string dbName = "database.txt";
    int choice;
 
    do {
        printMenu(dbName);
        getMenuChoice(choice);
 
        if (choice != -1) {
            handleMenuChoice(choice, workers, dbName);
        }
 
    } while (choice != 0);
 
    clear(&workers);
    return 0;
}
 