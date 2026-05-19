#include "search.h"
#include "user_io.h"
#include "sort.h"
#include <iostream>
#include <cctype>
using namespace std;

string toLowerStr(const string& s)
{
    string out;
    out.reserve(s.size());
    int i = 0;
    while (i < (int)s.size()) {
        unsigned char c = (unsigned char)s[i];

        if (c < 0x80) {
            out += (char)tolower(c);
            i++;
        }
        else if (c == 0xD0 && i + 1 < (int)s.size()) {
            unsigned char c2 = (unsigned char)s[i + 1];
            if (c2 == 0x81) {                      
                out += (char)0xD1;
                out += (char)0x91;
            } else if (c2 >= 0x90 && c2 <= 0x9F) {
                out += (char)0xD0;
                out += (char)(c2 + 0x20);
            } else if (c2 >= 0xA0 && c2 <= 0xAF) { 
                out += (char)0xD1;
                out += (char)(c2 - 0xA0 + 0x80);
            } else {                                 
                out += (char)c;
                out += (char)c2;
            }
            i += 2;
        }
        else {
            
            int bytes = (c < 0xE0) ? 2 : (c < 0xF0) ? 3 : 4;
            for (int b = 0; b < bytes && i < (int)s.size(); b++, i++)
                out += s[i];
        }
    }
    return out;
}

string getFirstCharStr(const string& s)
{
    if (s.empty()) return "";
    unsigned char c = (unsigned char)s[0];
    if (c < 0x80) return s.substr(0, 1);
    if (c < 0xE0) return s.substr(0, 2);
    if (c < 0xF0) return s.substr(0, 3);
    return           s.substr(0, 4);
}

Node** linearSearchByJob(LinkedList* d, const string& jobTitle, int& count)
{
    count = 0;
    if (!d || isEmpty(d)) return nullptr;

    string target = toLowerStr(jobTitle);

    Node* curr = d->head;
    while (curr) {
        if (toLowerStr(curr->data.job_title) == target) count++;
        curr = curr->next;
    }

    if (count == 0) return nullptr;

    Node** result = new Node*[count];
    int idx = 0;
    curr = d->head;
    while (curr) {
        if (toLowerStr(curr->data.job_title) == target) {   
            result[idx++] = curr;
        }
        curr = curr->next;
    }
    return result;
}

Node** linearSearchByDept(LinkedList* d, int dept, int& count)
{
    count = 0;
    if (!d || isEmpty(d)) return nullptr;

    Node* curr = d->head;
    while (curr) {
        if (curr->data.department_number == dept) count++;
        curr = curr->next;
    }

    if (count == 0) return nullptr;

    Node** result = new Node*[count];
    int idx = 0;
    curr = d->head;
    while (curr) {
        if (curr->data.department_number == dept)
            result[idx++] = curr;
        curr = curr->next;
    }
    return result;
}

Node* binarySearchBySurname(LinkedList* d, const string& surname, bool& isSorted)
{
    if (!d || isEmpty(d)) return nullptr;

    if (!isSorted) {
        cout << "  [Дека не отсортирована по фамилии. Выполняется сортировка...]\n";
        sortDequeInsertion(d, FIELD_SURNAME, true);
        isSorted = true;
        cout << "  [Сортировка завершена.]\n";
    }


    int n = d->size;
    Node** nodes = new Node*[n];
    Node* curr = d->head;
    for (int i = 0; i < n; i++, curr = curr->next) {

        nodes[i] = curr;
    }

    string target = toLowerStr(surname);
    int left = 0;
    int right = n - 1;
    Node* found = nullptr;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midVal = toLowerStr(nodes[mid]->data.fio.surname);
        int cmp = midVal.compare(target);

        if (cmp == 0) {
            found = nodes[mid];
            break;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    delete[] nodes;
    return found;
}


Node** filterByPrefix(LinkedList* d, const string& prefix, int& count)
{
    count = 0;
    if (!d || isEmpty(d) || prefix.empty()) return nullptr;

    string lPfx   = toLowerStr(prefix);
    size_t pfxLen  = lPfx.size();

    Node* curr = d->head;
    while (curr) {
        string lSurname = toLowerStr(curr->data.fio.surname);
        if (lSurname.size() >= pfxLen && lSurname.substr(0, pfxLen) == lPfx)
            count++;
        curr = curr->next;
    }

    if (count == 0) return nullptr;

    Node** result = new Node*[count];
    int idx = 0;
    curr = d->head;
    while (curr) {
        string lSurname = toLowerStr(curr->data.fio.surname);
        if (lSurname.size() >= pfxLen && lSurname.substr(0, pfxLen) == lPfx)
            result[idx++] = curr;
        curr = curr->next;
    }
    return result;
}

Node** filterBySubstring(LinkedList* d, const string& sub, int& count)
{
    count = 0;
    if (!d || isEmpty(d) || sub.empty()) return nullptr;

    string lSub = toLowerStr(sub);

    Node* curr = d->head;
    while (curr) {
        if (toLowerStr(curr->data.fio.surname).find(lSub) != string::npos)
            count++;
        curr = curr->next;
    }

    if (count == 0) return nullptr;

    Node** result = new Node*[count];
    int idx = 0;
    curr = d->head;
    while (curr) {
        if (toLowerStr(curr->data.fio.surname).find(lSub) != string::npos)
            result[idx++] = curr;
        curr = curr->next;
    }
    return result;
}

Node** filterByLetterRange(LinkedList* d,
                           const string& minLetter,
                           const string& maxLetter,
                           int& count)
{
    count = 0;
    if (!d || isEmpty(d)) return nullptr;

    string lMin = toLowerStr(getFirstCharStr(minLetter)); 
    string lMax = toLowerStr(getFirstCharStr(maxLetter)); 
    bool   hasMin = !lMin.empty();
    bool   hasMax = !lMax.empty();

    if (!hasMin && !hasMax) return nullptr;

    Node* curr = d->head;
    while (curr) {
        string firstCh = toLowerStr(getFirstCharStr(curr->data.fio.surname));
        bool ok = true;
        if (hasMin && firstCh < lMin) ok = false;
        if (hasMax && firstCh > lMax) ok = false;
        if (ok) count++;
        curr = curr->next;
    }

    if (count == 0) return nullptr;

    Node** result = new Node*[count];
    int idx = 0;
    curr = d->head;
    while (curr) {
        string firstCh = toLowerStr(getFirstCharStr(curr->data.fio.surname));
        bool ok = true;
        if (hasMin && firstCh < lMin) ok = false;
        if (hasMax && firstCh > lMax) ok = false;
        if (ok) result[idx++] = curr;
        curr = curr->next;
    }
    return result;
}


void removeNode(LinkedList* d, Node* node)
{
    if (!d || !node) return;

    if (node->prev) node->prev->next = node->next;
    else            d->head          = node->next;

    if (node->next) node->next->prev = node->prev;
    else            d->tail          = node->prev;

    delete node;
    d->size--;
}

void printFound(Node** found, int count)
{
    if (!found || count == 0) {
        cout << "  >>> Ничего не найдено.\n";
        return;
    }
    cout << "\n  Найдено элементов: " << count << "\n";
    for (int i = 0; i < count; i++) {
        if (!found[i]) continue;
        cout << "\n  [" << (i + 1) << "]\n";
        printWorker(found[i]->data);
    }
}

void editOrDeleteFound(LinkedList* d, Node** found, int count)
{
    if (!found || count == 0) return;

    for (int i = 0; i < count; i++) {
        if (!found[i]) continue; 

        cout << "\n--- Элемент " << (i + 1) << " из " << count << " ---\n";
        printWorker(found[i]->data);
        cout << "  1 — Редактировать\n"
             << "  2 — Удалить из деки\n"
             << "  0 — Пропустить\n"
             << "  Действие: ";

        int ch = -1;
        if (!(cin >> ch)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (ch) {
        case 1: {
            Worker newW;
            cout << "\nВведите новые данные сотрудника:\n";
            if (inputWorker(newW)) {
                found[i]->data = newW;
                cout << "  Данные успешно обновлены.\n";
            } else {
                cout << "  Ошибка ввода — данные не изменены.\n";
            }
            break;
        }
        case 2:
            removeNode(d, found[i]);
            found[i] = nullptr;
            cout << "  Элемент удалён из деки.\n";
            break;
        case 0:
        default:
            break;
        }
    }
}