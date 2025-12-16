#include <iostream>
#include <cwchar>
#include <cwctype>
#include <cstdlib>
#include "Unit_Operation.h"
#include "Unit_Input_Output.h"

using namespace std;

void initProductArray(ProductArray* array) {
    array->data = nullptr;
    array->size = 0;
    array->capacity = 0;
}

void freeProductArray(ProductArray* array) {
    if (array->data != nullptr) {
        delete[] array->data;
        array->data = nullptr;
    }
    array->size = 0;
    array->capacity = 0;
}

void resizeProductArray(ProductArray* array, int newCapacity) {
    if (newCapacity <= array->capacity) {
        return;
    }
    ExportProduct* newData = new ExportProduct[newCapacity];
    for (int i = 0; i < array->size; i++) {
        newData[i] = array->data[i];
    }
    if (array->data != nullptr) {
        delete[] array->data;
    }
    array->data = newData;
    array->capacity = newCapacity;
}

void addProductToArray(ProductArray* array, const ExportProduct* product) {
    if (array->size >= array->capacity) {
        int newCapacity = (array->capacity == 0) ? 4 : array->capacity * 2;
        resizeProductArray(array, newCapacity);
    }
    array->data[array->size] = *product;
    array->size++;
}

ExportProduct* getProductFromArray(const ProductArray* array, int index) {
    if (index < 0 || index >= array->size) {
        return nullptr;
    }
    return &array->data[index];
}

int getProductArraySize(const ProductArray* array) {
    return array->size;
}

void bubbleSortByCountry(ProductArray* array) {
    if (array->size < 2) {
        return;
    }
    for (int i = 0; i < array->size - 1; i++) {
        for (int j = 0; j < array->size - i - 1; j++) {
            wchar_t country1[50], country2[50];
            wcscpy(country1, array->data[j].country);
            wcscpy(country2, array->data[j + 1].country);
            lowercase(country1);
            lowercase(country2);
            if (wcscmp(country1, country2) > 0) {
                ExportProduct temp = array->data[j];
                array->data[j] = array->data[j + 1];
                array->data[j + 1] = temp;
            }
        }
    }
}

void findCountriesForProduct(const ProductArray* array, const wchar_t* productName, wchar_t*** countries, int* count) {
    *count = 0;
    *countries = nullptr;
    if (array->size == 0) {
        return;
    }
    wchar_t** tempCountries = new wchar_t*[array->size];
    wchar_t searchName[100];
    wcscpy(searchName, productName);
    lowercase(searchName);
    for (int i = 0; i < array->size; i++) {
        wchar_t currentName[100];
        wcscpy(currentName, array->data[i].name);
        lowercase(currentName);
        if (wcscmp(currentName, searchName) == 0) {
            bool found = false;
            wchar_t currentCountry[50];
            wcscpy(currentCountry, array->data[i].country);
            lowercase(currentCountry);
            for (int j = 0; j < *count; j++) {
                wchar_t existingCountry[50];
                wcscpy(existingCountry, tempCountries[j]);
                lowercase(existingCountry);
                if (wcscmp(currentCountry, existingCountry) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                tempCountries[*count] = new wchar_t[wcslen(array->data[i].country) + 1];
                wcscpy(tempCountries[*count], array->data[i].country);
                (*count)++;
            }
        }
    }
    if (*count > 0) {
        *countries = new wchar_t*[*count];
        for (int i = 0; i < *count; i++) {
            (*countries)[i] = new wchar_t[wcslen(tempCountries[i]) + 1];
            wcscpy((*countries)[i], tempCountries[i]);
            delete[] tempCountries[i];
        }
    }
    delete[] tempCountries;
}

void deleteCountriesArray(wchar_t** countries, int count) {
    if (countries != nullptr) {
        for (int i = 0; i < count; i++) {
            delete[] countries[i];
        }
        delete[] countries;
    }
}

void demonstrateAllOperations() {
    wcout << L"\nДЕМОНСТРАЦИЯ ВСЕХ ОПЕРАЦИЙ\n";
    ProductArray products;
    initProductArray(&products);
    wcout << L"\n1. Добавление товаров:\n";
    ExportProduct p1 = {L"Нефть", L"Китай", 1000};
    addProductToArray(&products, &p1);
    wcout << L"Добавлен: ";
    printproduct(&p1);
    ExportProduct p2 = {L"Газ", L"Германия", 500};
    addProductToArray(&products, &p2);
    wcout << L"Добавлен: ";
    printproduct(&p2);
    ExportProduct p3 = {L"Нефть", L"Индия", 800};
    addProductToArray(&products, &p3);
    wcout << L"Добавлен: ";
    printproduct(&p3);
    ExportProduct p4 = {L"Уголь", L"Германия", 300};
    addProductToArray(&products, &p4);
    wcout << L"Добавлен: ";
    printproduct(&p4);
    wcout << L"\n2. Вывод массива до сортировки:\n";
    printarray(&products);
    wcout << L"\n3. Сортировка по стране (метод пузырька):\n";
    bubbleSortByCountry(&products);
    printarray(&products);
    wcout << L"\n4. Поиск стран для товара 'Нефть':\n";
    wchar_t** countries = nullptr;
    int countriesCount = 0;
    findCountriesForProduct(&products, L"Нефть", &countries, &countriesCount);
    if (countriesCount > 0) {
        wcout << L"Страны, импортирующие товар 'Нефть':\n";
        for (int i = 0; i < countriesCount; i++) {
            wcout << L"  " << i + 1 << L". " << countries[i] << endl;
        }
        deleteCountriesArray(countries, countriesCount);
    } else {
        wcout << L"Товар не найден.\n";
    }
    freeProductArray(&products);
    wcout << L"\n5. Память освобождена\n";
    wcout << L"\nВ С Ё\n";
}