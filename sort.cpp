#include "sort.h"
#include "linkedList.h"
#include <iostream>

using namespace std;

Worker *dequeToArray(const LinkedList *d, int &size)
{
    size = d->size;
    if (size == 0)
        return nullptr;

    Worker *arr = new Worker[size];
    Node *curr = d->head;
    for (int i = 0; i < size; ++i)
    {
        arr[i] = curr->data;
        curr = curr->next;
    }
    return arr;
}

void arrayToDeque(LinkedList *d, const Worker *arr, int size)
{
    if (!d) {
        return;
    }

    while (!isEmpty(d)) {
        popFront(d);
    }

    for (int i = 0; i < size; ++i)
    {
        pushBack(d, arr[i]);
    }
}

int cmpWorkers(const Worker &a, const Worker &b, SortField field, bool ascending)
{
    int result = 0;

    if (field == FIELD_SURNAME) {
        result = a.fio.surname.compare(b.fio.surname); // САМИМ
    }
    else
    {
        if (a.experience < b.experience)
        {
            result = -1;
        }
        else if (a.experience > b.experience)
        {
            result = 1;
        }
        else
        {
            result = 0;
        }
    }

    return ascending ? result : -result;
}

void insertionSort(Worker *arr, int size, SortField field, bool ascending)
{
    for (int i = 1; i < size; ++i)
    {
        Worker key = arr[i];
        int j = i - 1;

        while (j >= 0 && cmpWorkers(arr[j], key, field, ascending) > 0)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int hoarePartition(Worker *arr, int left, int right, SortField field, bool ascending)
{
    Worker pivot = arr[(left + right) / 2];
    int i = left - 1;
    int j = right + 1;

    while (true)
    {
        do
        {
            ++i;
        } while (cmpWorkers(arr[i], pivot, field, ascending) < 0);
        do
        {
            --j;
        } while (cmpWorkers(arr[j], pivot, field, ascending) > 0);

        if (i >= j) {

            return j;
        }

        swap(arr[i], arr[j]);
    }
}

void quickSort(Worker *arr, int left, int right, SortField field, bool ascending)
{
    if (left < right)
    {
        int p = hoarePartition(arr, left, right, field, ascending);
        quickSort(arr, left, p, field, ascending);
        quickSort(arr, p + 1, right, field, ascending);
    }
}

void sortDequeInsertion(LinkedList *d, SortField field, bool ascending)
{
    if (!d || d->size <= 1)
        return;

    int size = 0;
    Worker *arr = dequeToArray(d, size);

    insertionSort(arr, size, field, ascending);

    arrayToDeque(d, arr, size);
    delete[] arr;
}

void sortDequeQuick(LinkedList *d, SortField field, bool ascending)
{
    if (!d || d->size <= 1)
        return;

    int size = 0;
    Worker *arr = dequeToArray(d, size);

    quickSort(arr, 0, size - 1, field, ascending);

    arrayToDeque(d, arr, size);
    delete[] arr;
}

void loadSampleData(LinkedList *d)
{
    while (!isEmpty(d)) {
        popFront(d);
    }

    Worker samples[] = {
        {{"Иванов", "Алексей", "Петрович"}, 12, 3, "Инженер-программист", 15, 6, 2013},
        {{"Смирнова", "Елена", "Викторовна"}, 5, 1, "Системный аналитик", 20, 9, 2020},
        {{"Козлов", "Дмитрий", "Сергеевич"}, 18, 2, "Руководитель отдела", 3, 2, 2007},
        {{"Новикова", "Ольга", "Александровна"}, 3, 4, "Тестировщик", 11, 1, 2022},
        {{"Морозов", "Андрей", "Николаевич"}, 25, 2, "Главный инженер", 7, 4, 2000},
        {{"Волкова", "Наталья", "Игоревна"}, 8, 3, "Специалист по БД", 30, 11, 2016},
        {{"Зайцев", "Игорь", "Владимирович"}, 1, 5, "Стажёр", 14, 3, 2024},
        {{"Соколова", "Марина", "Борисовна"}, 14, 1, "Бизнес-аналитик", 22, 8, 2011},
        {{"Попов", "Виктор", "Анатольевич"}, 20, 2, "Архитектор ПО", 5, 7, 2005},
        {{"Лебедева", "Светлана", "Геннадьевна"}, 7, 4, "Менеджер проекта", 18, 12, 2017}
    };

    int n = sizeof(samples) / sizeof(samples[0]);
    for (int i = 0; i < n; ++i)
    {
        pushBack(d, samples[i]);
    }

    cout << "Загружено " << n << " тестовых сотрудников.\n";
}

void swap(Worker &a, Worker &b) {
    Worker temp = a; 
    a = b;           
    b = temp;       
}