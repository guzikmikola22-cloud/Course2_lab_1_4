#include "Notebook.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ================= Допоміжні засоби для вирівнювання таблиці =================
namespace {
    // Ширини колонок (в символах)
    const int W_NUM = 3;
    const int W_NAME = 15;
    const int W_DATE = 12;
    const int W_PHONE = 15;

    // Довжина рядка в символах, а не в байтах (кирилиця в UTF-8 = 2 байти)
    int utf8Len(const string& s)
    {
        int len = 0;
        for (unsigned char c : s) {
            if ((c & 0xC0) != 0x80) len++;
        }
        return len;
    }

    // Доповнює рядок пробілами до потрібної ширини
    string pad(const string& s, int width)
    {
        int len = utf8Len(s);
        if (len < width) {
            return s + string(width - len, ' ');
        }
        return s;
    }
}

// ================= Реалізація класу Record =================
bool Record::setLastName(string value)
{
    if (!value.empty()) {
        lastName = value;
        return true;
    }
    return false;
}

bool Record::setBirthDate(string value)
{
    if (!value.empty()) {
        birthDate = value;
        return true;
    }
    return false;
}

bool Record::setPhoneNumber(string value)
{
    if (!value.empty()) {
        phoneNumber = value;
        return true;
    }
    return false;
}

bool Record::Init(string ln, string bd, string pn)
{
    return setLastName(ln) && setBirthDate(bd) && setPhoneNumber(pn);
}

void Record::Read()
{
    string ln, bd, pn;
    bool ok;
    do {
        cout << "Введіть прізвище: ";
        cin >> ln;
        cout << "Введіть дату народження (DD.MM.YYYY): ";
        cin >> bd;
        cout << "Введіть номер телефону: ";
        cin >> pn;
        ok = Init(ln, bd, pn);
        if (!ok) {
            cout << "Помилка! Дані не можуть бути порожніми. Повторіть введення.\n";
        }
    } while (!ok);
}

void Record::Display() const
{
    cout << toString();
}

string Record::toString() const
{
    stringstream sout;
    sout << pad(lastName, W_NAME) << " | "
        << pad(birthDate, W_DATE) << " | "
        << phoneNumber << "\n";
    return sout.str();
}

// ================= Реалізація класу Notebook =================
Notebook::Notebook()
{
    records = nullptr;
    Init(2); // Початкова місткість - 2 записи
}

Notebook::~Notebook()
{
    delete[] records;
}

bool Notebook::Init(int initialCapacity)
{
    if (initialCapacity > 0) {
        capacity = initialCapacity;
        count = 0;
        records = new Record[capacity];
        return true;
    }
    return false;
}

void Notebook::resize()
{
    capacity *= 2;
    Record* temp = new Record[capacity];
    for (int i = 0; i < count; i++) {
        temp[i] = records[i];
    }
    delete[] records;
    records = temp;
}

void Notebook::addRecord(const Record& r)
{
    if (count == capacity) {
        resize();
    }
    records[count] = r;
    count++;
}

bool Notebook::removeRecord(int index)
{
    if (index >= 0 && index < count) {
        for (int i = index; i < count - 1; i++) {
            records[i] = records[i + 1];
        }
        count--;
        return true;
    }
    return false;
}

void Notebook::Read()
{
    int n;
    cout << "Скільки записів хочете додати зараз? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\n--- Запис #" << (i + 1) << " ---\n";
        Record r;
        r.Read();
        addRecord(r);
    }
}

void Notebook::Display() const
{
    cout << toString();
}

string Notebook::toString() const
{
    stringstream sout;
    if (count == 0) {
        sout << "Записна книжка порожня.\n";
        return sout.str();
    }

    // Ширина лінії рахується з тих самих констант, що й колонки
    const int totalWidth = W_NUM + 3 + W_NAME + 3 + W_DATE + 3 + W_PHONE;
    const string line(totalWidth, '=');

    // Роздільна лінія між записами (з "+" у місцях вертикальних рисок)
    const string rowLine =
        string(W_NUM + 1, '-') + "+" +
        string(W_NAME + 2, '-') + "+" +
        string(W_DATE + 2, '-') + "+" +
        string(W_PHONE + 1, '-');

    sout << line << "\n";
    sout << pad("#", W_NUM) << " | "
        << pad("Прізвище", W_NAME) << " | "
        << pad("Дата нар.", W_DATE) << " | "
        << "Телефон\n";
    sout << line << "\n";

    for (int i = 0; i < count; i++) {
        sout << pad(to_string(i), W_NUM) << " | " << records[i].toString();
        if (i < count - 1) {
            sout << rowLine << "\n"; // лінія між записами, після останнього її немає
        }
    }

    sout << line << "\n";
    return sout.str();
}

void Notebook::searchByLastName(string ln) const
{
    bool found = false;
    cout << "\nРезультати пошуку за прізвищем '" << ln << "':\n";
    for (int i = 0; i < count; i++) {
        if (records[i].getLastName() == ln) {
            records[i].Display();
            found = true;
        }
    }
    if (!found) cout << "Записів не знайдено.\n";
}

void Notebook::searchByPhoneNumber(string pn) const
{
    bool found = false;
    cout << "\nРезультати пошуку за телефоном '" << pn << "':\n";
    for (int i = 0; i < count; i++) {
        if (records[i].getPhoneNumber() == pn) {
            records[i].Display();
            found = true;
        }
    }
    if (!found) cout << "Записів не знайдено.\n";
}

void Notebook::sortByLastName()
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (records[j].getLastName() > records[j + 1].getLastName()) {
                Record temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

void Notebook::sortByPhoneNumber()
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (records[j].getPhoneNumber() > records[j + 1].getPhoneNumber()) {
                Record temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}