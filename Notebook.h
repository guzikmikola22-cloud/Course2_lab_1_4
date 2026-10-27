#pragma once
#include <string>
#include <sstream>

using namespace std;

// Допоміжний клас для зберігання одного запису
class Record
{
private:
    string lastName;    // Прізвище
    string birthDate;   // Дата народження
    string phoneNumber; // Номер телефону

public:
    // Константні гетери
    string getLastName() const { return lastName; }
    string getBirthDate() const { return birthDate; }
    string getPhoneNumber() const { return phoneNumber; }

    // Сетери з валідацією
    bool setLastName(string value);
    bool setBirthDate(string value);
    bool setPhoneNumber(string value);

    // Обов'язкові методи
    bool Init(string ln, string bd, string pn);
    void Read();
    void Display() const;
    string toString() const;
};

// Головний клас-контейнер "Записна книжка"
class Notebook
{
private:
    Record* records; // Динамічний масив записів
    int count;       // Фактична кількість записів
    int capacity;    // Місткість масиву

    void resize();   // Метод для збільшення масиву при нестачі місця

public:
    Notebook();
    ~Notebook();

    // Обов'язкові методи
    bool Init(int initialCapacity);
    void Read(); // Зчитування кількох записів
    void Display() const;
    string toString() const;

    // Методи за Варіантом 15
    void addRecord(const Record& r);
    bool removeRecord(int index);

    void searchByLastName(string ln) const;
    void searchByPhoneNumber(string pn) const;

    void sortByLastName();
    void sortByPhoneNumber();
};