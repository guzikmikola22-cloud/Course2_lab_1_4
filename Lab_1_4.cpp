#include <iostream>
#include <Windows.h>
#include "Notebook.h"

using namespace std;

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Notebook nb;
    int choice;
    string searchStr;
    int index;

    do {
        cout << "\n======== МЕНЮ ЗАПИСНОЇ КНИЖКИ ========\n";
        cout << "1. Додати запис (Read)\n";
        cout << "2. Вивести всі записи (Display)\n";
        cout << "3. Знайти за прізвищем\n";
        cout << "4. Знайти за номером телефону\n";
        cout << "5. Сортувати за прізвищем\n";
        cout << "6. Сортувати за номером телефону\n";
        cout << "7. Видалити запис за номером (індексом)\n";
        cout << "0. Вийти\n";
        cout << "======================================\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            nb.Read(); // Демонстрація методу Read класу-контейнера
            break;
        case 2:
            nb.Display(); // Демонстрація методів Display та toString
            break;
        case 3:
            cout << "Введіть прізвище для пошуку: ";
            cin >> searchStr;
            nb.searchByLastName(searchStr);
            break;
        case 4:
            cout << "Введіть телефон для пошуку: ";
            cin >> searchStr;
            nb.searchByPhoneNumber(searchStr);
            break;
        case 5:
            nb.sortByLastName();
            cout << "Відсортовано за прізвищем!\n";
            nb.Display();
            break;
        case 6:
            nb.sortByPhoneNumber();
            cout << "Відсортовано за телефоном!\n";
            nb.Display();
            break;
        case 7:
            cout << "Введіть номер (індекс) запису для видалення (з першої колонки): ";
            cin >> index;
            if (nb.removeRecord(index))
                cout << "Запис успішно видалено!\n";
            else
                cout << "Помилка: запису з таким номером не існує.\n";
            break;
        case 0:
            cout << "Завершення роботи програми.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}