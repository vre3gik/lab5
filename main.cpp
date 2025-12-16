#include <iostream>
#include <clocale>
#include <windows.h>
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
        wcout << L"Выберите действие (1-7): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            wcout << L"Ошибка ввода! Пожалуйста, введите число от 1 до 7." << endl;
            continue;
        }
        cin.ignore(1000, '\n');  
        switch (choice) {
            case 1: {
                freeProductArray(&products); 
                initProductArray(&products);  
                wcout << L"Создан новый массив товаров." << endl;
                break;
            }
            case 2: {
                ExportProduct newProduct;
                inputproduct(&newProduct);
                addProductToArray(&products, &newProduct);
                wcout << L"Товар успешно добавлен." << endl;
                break;
            }
            case 3: {
                if (getProductArraySize(&products) == 0) {
                    wcout << L"Массив товаров пуст." << endl;
                } else {
                    printarray(&products);
                }
                break;
            }
            
            case 4: {
                if (getProductArraySize(&products) == 0) {
                    wcout << L"Массив товаров пуст." << endl;
                } else {
                    bubbleSortByCountry(&products);
                    wcout << L"Массив отсортирован по стране." << endl;
                }
                break;
            }
            
            case 5: {
                if (getProductArraySize(&products) == 0) {
                    wcout << L"Массив товаров пуст." << endl;
                    break;
                }
                wchar_t productName[100];
                wcout << L"Введите наименование товара: ";
                wcin.getline(productName, 100);
                delprobelsinword(productName);
                if (wcslen(productName) == 0) {
                    wcout << L"Ошибка! Наименование товара не может быть пустым." << endl;
                    break;
                }
                wchar_t** countries = nullptr;
                int countriesCount = 0;
                findCountriesForProduct(&products, productName, &countries, &countriesCount);
                printresults(productName, countries, countriesCount);
                if (countries != nullptr) {
                    deleteCountriesArray(countries, countriesCount);
                }
                break;
            }
            case 6: {
                demonstrateAllOperations();
                break;
            }
            case 7: {
                freeProductArray(&products);
                wcout << L"Программа завершена. Память освобождена." << endl;
                break;
            }
            default:
                wcout << L"Неверный выбор! Пожалуйста, выберите от 1 до 7." << endl;
        }
    } while (choice != 7);
    return 0;
}