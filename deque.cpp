#include "deque.h"
#include "user_io.h"
#include "worker.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

void init(Deque* d) {
    if (!d) return;
    d->head = nullptr;
    d->tail = nullptr;
    d->size = 0;
}

bool isEmpty(const Deque* d) {
    return !d || d->size == 0 || d->head == nullptr;
}

int getSize(const Deque* d) {
    return d ? d->size : 0;
}


void pushFront(Deque* d, const Worker& w) {
    if (!d) return;

    Node* newNode = new Node(w);

    if (isEmpty(d)) {
        d->head = d->tail = newNode;
    } else {
        newNode->next  = d->head;
        d->head->prev  = newNode;
        d->head        = newNode;
    }
    d->size++;
}

void pushBack(Deque* d, const Worker& w) {
    if (!d) return;

    Node* newNode = new Node(w);

    if (isEmpty(d)) {
        d->head = d->tail = newNode;
    } else {
        newNode->prev  = d->tail;
        d->tail->next  = newNode;
        d->tail        = newNode;
    }
    d->size++;
}

Worker popFront(Deque* d) {
    if (!d || isEmpty(d)) {
        cerr << " дека пуста!\n";
        return Worker{};
    }

    Node*  temp  = d->head;
    Worker value = temp->data;

    d->head = d->head->next;

    if ((*d).head) {
        d->head->prev = nullptr;
    } else {
        d->tail = nullptr;         
    }

    delete temp;
    d->size--;
    return value;
}

Worker popBack(Deque* d) {
    if (!d || isEmpty(d)) {
        cerr << "Дека пустая\n";
        return Worker{};
    }

    Node*  temp  = d->tail;
    Worker value = temp->data;

    d->tail = d->tail->prev;

    if (d->tail) {
        d->tail->next = nullptr;
    } else {
        d->head = nullptr;        
    }

    delete temp;
    d->size--;
    return value;
}


const Worker& front(const Deque* d) {
    if (!d || isEmpty(d)) {
        cerr << "дека пуста!\n";
        static Worker dummy{};
        return dummy;
    }
    return d->head->data;
}

const Worker& back(const Deque* d) {
    if (!d || isEmpty(d)) {
        cerr << "дека пуста!\n";
        static Worker dummy{};
        return dummy;
    }
    return d->tail->data;
}


void clear(Deque* d) {
    if (!d) return;

    if (isEmpty(d)) {
        cout << "Дека уже пуста\n";
        return;
    }

    cout << "\nОчистка деки Извлечённые элементы:\n";
    while (!isEmpty(d)) {
        Worker w = popFront(d);
        printWorker(w);
    }
    cout << "Дека очищена\n";
}

void printWorker(const Worker& w) {
    cout << "-----------------------------\n";
    cout << "ФИО:      " << w.fio.surname << " "
                         << w.fio.name    << " "
                         << w.fio.patronymic << "\n";
    cout << "Должность: " << w.job_title << "\n";
    cout << "Стаж:      " << w.experience << " лет\n";
    cout << "Отдел:     " << w.department_number << "\n";
    cout << "Дата:      " << setfill('0')
                          << setw(2) << w.day   << "."
                          << setw(2) << w.month << "."
                          << setw(4) << w.year  << "\n";
    cout << "-----------------------------\n";
}

void printDeque(const Deque* d) {
    if (!d || isEmpty(d)) {
        cout << "Дека пуста.\n";
        return;
    }

    cout << "\n Размер деки: " << d->size << "\n";
    Node* current = d->head;
    int   index   = 0;
    while (current) {
        string pos;
        if (index == 0 && d->size == 1) pos = " [Голова / Хвост]";
        else if (index == 0)            pos = " [Голова]";
        else if (!current->next)        pos = " [Хвост]";
        else                            pos = "";

        cout << "\n#" << index << pos << "\n";
        printWorker(current->data);
        current = current->next;
        index++;
    }
    cout << "============================\n";
}

void printDequeTable(const Deque* list)
{
    if ((*list).size == 0)
    {
        cout << "\n--- Список пуст ---\n";
        return;
    }

    int totalWidth = W_NUM + W_NAME + W_EXP + W_DEPT + W_DATE + W_JOB + 19;
    string sep(totalWidth, '-');

    cout << sep << endl;

    cout << "| " << padLeft ("№",          W_NUM)
         << " | " << padRight("ФИО",        W_NAME)
         << " | " << padLeft ("Стаж",       W_EXP)
         << " | " << padLeft ("Отдел",      W_DEPT)
         << " | " << padRight("Дата",       W_DATE)
         << " | " << padRight("Должность",  W_JOB)
         << " |" << endl;

    cout << sep << endl;

    Node* current = (*list).head;
    int i = 1;
    
    while (current)
    {
        Worker& w = current->data;

        string shortName = w.fio.surname + " " +
                           w.fio.name[0] + "." +
                           w.fio.patronymic[0] + ".";

        ostringstream date;
        date << setw(2) << setfill('0') << w.day   << "."
             << setw(2) << setfill('0') << w.month << "."
             << setw(4) << setfill('0') << w.year;

        cout << "| " << padLeft (to_string(i),              W_NUM)
             << " | " << padRight(shortName,                 W_NAME)
             << " | " << padLeft (to_string(w.experience),   W_EXP)
             << " | " << padLeft (to_string(w.department_number), W_DEPT)
             << " | " << padRight(date.str(),                W_DATE)
             << " | " << padRight(w.job_title,               W_JOB)
             << " |" << endl;

        current = current->next;
        i++;
    }

    cout << sep << endl;
}