#include <iostream>
#include <cwctype>
#include <clocale>
#include <windows.h>
#include "Unit_Input_Output.h"

using namespace std;


bool pustyaorprobeli(const wchar_t* str) {
    for (int i = 0; str[i] != L'\0'; i++) {
        if (!iswspace(str[i])) {
            return false;
        }
    }
    return true;
}


void delprobelsinword(wchar_t* str) {
    int start = 0;
    while (str[start] == L' ' || str[start] == L'\t') {
        start++;
    }
    if (start > 0) {
        int i = 0;
        while (str[start + i] != L'\0') {
            str[i] = str[start + i];
            i++;
        }
        str[i] = L'\0';
    }
    int end = wcslen(str) - 1;
    while (end >= 0 && (str[end] == L' ' || str[end] == L'\t' || 
                        str[end] == L'\n' || str[end] == L'\r')) {
        str[end] = L'\0';
        end--;
    }
}


void lowercase(wchar_t* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = towlower(str[i]);
    }
}


void inputproduct(ExportProduct* product) {
    wcout << L"Введите наименование товара: ";
    wcin.getline(product->name, 100);
    while (pustyaorprobeli(product->name)) {
        wcout << L"Название не может быть пустым,введите еще раз: ";
        wcin.getline(product->name, 100);
    }
    
    wcout << L"Введите страну импортера: ";
    wcin.getline(product->country, 50);
    while (pustyaorprobeli(product->country)) {
        wcout << L"Страна не может быть пустым,введите еще раз: ";
        wcin.getline(product->country, 50);
    }
    wcout << L"Введите количество (в штуках): ";
    while (true) {
        cin >> product->quantity;
        if (cin.fail() || product->quantity < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            wcout << L"Ошибка! Введите положительное число: ";
        } else {
            cin.ignore(1000, '\n');
            break;
        }
    }
}


void printproduct(const ExportProduct* product) {
    wcout << L"Товар: " << product->name 
          << L", Страна: " << product->country 
          << L", Количество: " << product->quantity << endl;
}


void printarray(const ProductArray* array) {
    if (array->size == 0) {
        wcout << L"Массив пуст." << endl;
        return;
    }
    wcout << L"\nСписок всех товаров:" << endl;
    for (int i = 0; i < array->size; i++) {
        wcout << i + 1 << L". ";
        printproduct(&array->data[i]);
    }
    wcout << L"Всего товаров: " << array->size << endl;
}


void printmenu() {
    wcout << L"\nМЕНЮ" << endl;
    wcout << L"1. Создать новый массив товаров" << endl;
    wcout << L"2. Добавить товар" << endl;
    wcout << L"3. Просмотреть все товары" << endl;
    wcout << L"4. Отсортировать по стране (метод пузырька)" << endl;
    wcout << L"5. Найти страны для указанного товара" << endl;
    wcout << L"6. Демонстрация всех операций" << endl;
    wcout << L"7. Выход" << endl;
}

void printresults(const wchar_t* productName, wchar_t** countries, int countriesCount) {
    if (countriesCount == 0) {
        wcout << L"Товар '" << productName << L"' не найден." << endl;
    } else {
        wcout << L"\nСтраны, импортирующие товар '" << productName << L"':" << endl;
        for (int i = 0; i < countriesCount; i++) {
            wcout << i + 1 << L". " << countries[i] << endl;
        }
    }
}