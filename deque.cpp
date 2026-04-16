#include "deque.h"
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

    if (d->head) {
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
        cerr << ">>> Ошибка: дека пуста (front)!\n";
        static Worker dummy{};
        return dummy;
    }
    return d->head->data;
}

const Worker& back(const Deque* d) {
    if (!d || isEmpty(d)) {
        cerr << ">>> Ошибка: дека пуста (back)!\n";
        static Worker dummy{};
        return dummy;
    }
    return d->tail->data;
}


void clear(Deque* d) {
    if (!d) return;

    if (isEmpty(d)) {
        cout << "Дека уже пуста.\n";
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

void printDequeTable(const Deque* d) {
    if (!d || isEmpty(d)) {
        cout << "\n--- Дека пуста ---\n";
        return;
    }

    const int W_NUM  = 4;
    const int W_NAME = 25;
    const int W_EXP  = 8;
    const int W_DEPT = 8;
    const int W_DATE = 10;
    const int W_JOB  = 20;

    int totalWidth = W_NUM + W_NAME + W_EXP + W_DEPT + W_DATE + W_JOB + 13;

    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << "\n";

    cout << "| " << setw(W_NUM)  << left  << "№"
         << " | " << setw(W_NAME) << left  << "ФИО"
         << " | " << setw(W_EXP)  << right << "Стаж"
         << " | " << setw(W_DEPT) << right << "Отдел"
         << " | " << setw(W_DATE) << left  << "Дата"
         << " | " << setw(W_JOB)  << left  << "Должность"
         << " |\n";

    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << "\n";

    Node* current = d->head;
    int   i       = 1;

    while (current) {
        const Worker& w = current->data;

        string shortName = w.fio.surname + " " +
                           w.fio.name[0] + "." +
                           w.fio.patronymic[0] + ".";

        ostringstream date;
        date << setw(2) << setfill('0') << w.day   << "."
             << setw(2) << setfill('0') << w.month << "."
             << setw(4) << setfill(' ') << w.year;

        cout << "| " << setw(W_NUM)  << right << i
             << " | " << setw(W_NAME) << left  << shortName
             << " | " << setw(W_EXP)  << right << w.experience
             << " | " << setw(W_DEPT) << right << w.department_number
             << " | " << setw(W_DATE) << left  << date.str()
             << " | " << setw(W_JOB)  << left  << w.job_title
             << " |\n";

        current = current->next;
        i++;
    }

    cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << "\n";
}