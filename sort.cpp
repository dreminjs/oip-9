#include "sort.h"
#include "deque.h"
#include <iostream>
#include <algorithm>   // std::swap

using namespace std;

// ============================================================
//  Конвертация: дека -> динамический массив
// ============================================================
Worker* dequeToArray(const Deque* d, int& size) {
    size = d ? d->size : 0;
    if (size == 0) return nullptr;

    Worker* arr = new Worker[size];
    Node* curr = d->head;
    for (int i = 0; i < size; ++i) {
        arr[i] = curr->data;
        curr   = curr->next;
    }
    return arr;
}

// ============================================================
//  Конвертация: динамический массив -> дека
// ============================================================
void arrayToDeque(Deque* d, const Worker* arr, int size) {
    if (!d) return;

    // Очищаем деку
    while (!isEmpty(d)) popFront(d);

    for (int i = 0; i < size; ++i) {
        pushBack(d, arr[i]);
    }
}

// ============================================================
//  Сравнение двух работников
//  Возвращает < 0, если a < b  (при ascending=true)
//             = 0, если a == b
//             > 0, если a > b  (при ascending=true)
//  При ascending=false знак инвертируется.
// ============================================================
int cmpWorkers(const Worker& a, const Worker& b, SortField field, bool ascending) {
    int result = 0;

    if (field == FIELD_SURNAME) {
        // Строковое сравнение: фамилия
        result = a.fio.surname.compare(b.fio.surname);
    } else {
        // Числовое сравнение: стаж
        if      (a.experience < b.experience) result = -1;
        else if (a.experience > b.experience) result =  1;
        else                                  result =  0;
    }

    return ascending ? result : -result;
}

// ============================================================
//  Сортировка вставками (Insertion Sort)
//  Сложность: O(n^2) — медленная, стабильная.
//  Выбор структуры: массив — удобен для смещения элементов
//  на единицу вправо arr[j+1] = arr[j] без перелинковки узлов.
// ============================================================
void insertionSort(Worker* arr, int size, SortField field, bool ascending) {
    for (int i = 1; i < size; ++i) {
        Worker key = arr[i];
        int    j   = i - 1;

        // Сдвигаем элементы, которые больше key, на одну позицию вправо
        while (j >= 0 && cmpWorkers(arr[j], key, field, ascending) > 0) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// ============================================================
//  Разбиение Хоара
//  Опорный элемент берётся из середины массива.
//  Возвращает индекс последнего элемента левой части.
// ============================================================
int hoarePartition(Worker* arr, int left, int right, SortField field, bool ascending) {
    Worker pivot = arr[(left + right) / 2];
    int i = left  - 1;
    int j = right + 1;

    while (true) {
        // Двигаем i вправо, пока arr[i] «меньше» pivot
        do { ++i; } while (cmpWorkers(arr[i], pivot, field, ascending) < 0);

        // Двигаем j влево, пока arr[j] «больше» pivot
        do { --j; } while (cmpWorkers(arr[j], pivot, field, ascending) > 0);

        if (i >= j) return j;

        swap(arr[i], arr[j]);
    }
}

// ============================================================
//  Быстрая сортировка Хоара (QuickSort)
//  Сложность: O(n log n) среднее, O(n^2) худшее.
//  Выбор структуры: массив — индексный доступ O(1) необходим
//  для разбиения Хоара; в связном списке пришлось бы итерировать.
// ============================================================
void quickSort(Worker* arr, int left, int right, SortField field, bool ascending) {
    if (left < right) {
        int p = hoarePartition(arr, left, right, field, ascending);
        quickSort(arr, left,     p, field, ascending);
        quickSort(arr, p + 1, right, field, ascending);
    }
}

// ============================================================
//  Обёртка: сортировка вставками через деку
// ============================================================
void sortDequeInsertion(Deque* d, SortField field, bool ascending) {
    if (!d || d->size <= 1) return;

    int      size = 0;
    Worker*  arr  = dequeToArray(d, size);

    insertionSort(arr, size, field, ascending);

    arrayToDeque(d, arr, size);
    delete[] arr;
}

void sortDequeQuick(Deque* d, SortField field, bool ascending) {
    if (!d || d->size <= 1) return;

    int      size = 0;
    Worker*  arr  = dequeToArray(d, size);

    quickSort(arr, 0, size - 1, field, ascending);

    arrayToDeque(d, arr, size);
    delete[] arr;
}

void loadSampleData(Deque* d) {
    while (!isEmpty(d)) popFront(d);

    struct SampleWorker {
        const char* surname;
        const char* name;
        const char* patronymic;
        int experience;
        int dept;
        int day, month, year;
        const char* job_title;
    };

    SampleWorker samples[] = {
        {"Иванов",     "Алексей",   "Петрович",    12, 3, 15,  6, 2013, "Инженер-программист"},
        {"Смирнова",   "Елена",     "Викторовна",   5, 1, 20,  9, 2020, "Системный аналитик"},
        {"Козлов",     "Дмитрий",   "Сергеевич",   18, 2,  3,  2, 2007, "Руководитель отдела"},
        {"Новикова",   "Ольга",     "Александровна", 3, 4, 11,  1, 2022, "Тестировщик"},
        {"Морозов",    "Андрей",    "Николаевич",  25, 2,  7,  4, 2000, "Главный инженер"},
        {"Волкова",    "Наталья",   "Игоревна",     8, 3, 30, 11, 2016, "Специалист по БД"},
        {"Зайцев",     "Игорь",     "Владимирович",  1, 5, 14,  3, 2024, "Стажёр"},
        {"Соколова",   "Марина",    "Борисовна",   14, 1, 22,  8, 2011, "Бизнес-аналитик"},
        {"Попов",      "Виктор",    "Анатольевич", 20, 2,  5,  7, 2005, "Архитектор ПО"},
        {"Лебедева",   "Светлана",  "Геннадьевна",   7, 4, 18, 12, 2017, "Менеджер проекта"}
    };

    int n = sizeof(samples) / sizeof(samples[0]);
    for (int i = 0; i < n; ++i) {
        Worker w;
        w.fio.surname     = samples[i].surname;
        w.fio.name        = samples[i].name;
        w.fio.patronymic  = samples[i].patronymic;
        w.experience      = samples[i].experience;
        w.department_number = samples[i].dept;
        w.day             = samples[i].day;
        w.month           = samples[i].month;
        w.year            = samples[i].year;
        w.job_title       = samples[i].job_title;
        pushBack(d, w);
    }

    cout << "Загружено " << n << " тестовых сотрудников.\n";
}