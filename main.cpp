#include <iostream>
#include <clocale>
#include <windows.h>
#include <cwchar>
#include <cwctype>

#include "Unit_Input_Output.h"
#include "Unit_Operation.h" 

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    ProductArray products;
    initProductArray(&products);
    int choice;
    do {
        printmenu();
        wcout << L"Выберите действие (1-8): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            wcout << L"Введите число от 1 до 8." << endl;
            continue;
        }
        cin.ignore(1000, '\n');
        switch (choice) {
            case 1:
                freeProductArray(&products);
                initProductArray(&products);
                wcout << L"Создан новый массив товаров." << endl;
                break;
            case 2: {
                ExportProduct newProduct;
                inputproduct(&newProduct);
                addProductToArray(&products, &newProduct);
                wcout << L"Товар успешно добавлен." << endl;
                break;
            }
            case 3:
                if (getproductarraysize(&products) == 0) {
                    wcout << L"Массив товаров пуст." << endl;
                } else {
                    printarray(&products);
                }
                break;
            case 4:
                if (getproductarraysize(&products) == 0) {
                    wcout << L"Массив товаров и так пуст" << endl;
                    break;
                }
                wcout << L"\nСпособы удаления:" << endl;
                wcout << L"1. Удалить по номеру товара" << endl;
                wcout << L"2. Удалить все товары с названием" << endl;
                wcout << L"Выберите (1 или 2): ";
                int deleteChoice;
                if (!(cin >> deleteChoice)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    wcout << L"Ошибка ввода!" << endl;
                    break;
                }
                cin.ignore(1000, '\n');
                if (deleteChoice == 1) {
                    wcout << L"Текущий список товаров:" << endl;
                    printarray(&products);
                    int index;
                    wcout << L"Введите номер товара для удаления: ";
                    if (!(cin >> index)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        wcout << L"Ошибка ввода!" << endl;
                        break;
                    }
                    cin.ignore(1000, '\n');
                    removeProductByIndex(&products, index);
                } else if (deleteChoice == 2) {
                    wchar_t productName[100];
                    wcout << L"Введите название товара для удаления: ";
                    wcin.getline(productName, 100);
                    delprobelsinword(productName);
                    if (wcslen(productName) == 0) {
                        wcout << L"Название товара не может быть пустым." << endl;
                        break;
                    }
                    removeProductsByName(&products, productName);  
                } else {
                    wcout << L"Неверный выбор." << endl;
                }
                break;
            case 5:
                if (getproductarraysize(&products) == 0) {
                    wcout << L"Массив товаров пуст." << endl;
                } else {
                    bubbleSortByCountry(&products);
                    wcout << L"Массив отсортирован по стране." << endl;
                }
                break; 
            case 6:
                if (getproductarraysize(&products) == 0) {
                    wcout << L"Массив товаров пуст." << endl;
                    break;
                }
                {
                    wchar_t productName[100];
                    wcout << L"Введите наименование товара: ";
                    wcin.getline(productName, 100);
                    delprobelsinword(productName);
                    if (wcslen(productName) == 0) {
                        wcout << L"Название товара не может быть пустым." << endl;
                        break;
                    }
                    wchar_t** countries = nullptr;
                    int countriesCount = 0;
                    findcountriesforproduct(&products, productName, &countries, &countriesCount);
                    printresults(productName, countries, countriesCount);
                    if (countries != nullptr) {
                        deleteCountriesArray(countries, countriesCount);
                    }
                }
                break;
            case 7:
                alloperation();
                break;
            case 8:
                freeProductArray(&products);
                wcout << L"В С Ё" << endl;
                break; 
            default:
                wcout << L"Выберите от 1 до 8." << endl;
        }
    } while (choice != 8);
    return 0;
}