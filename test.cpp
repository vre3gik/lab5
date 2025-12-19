#include <iostream>
#include <clocale>
#include <windows.h>
#include <cwchar>
#include <cwctype>

using namespace std;

struct ExportProduct {
    wchar_t name[100];
    wchar_t country[50];
    int quantity;
};

struct ProductArray {
    ExportProduct* data;
    int size;
    int capacity;
};

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
    while (end >= 0 && (str[end] == L' ' || str[end] == L'\t' || str[end] == L'\n' || str[end] == L'\r')) {
        str[end] = L'\0';
        end--;
    }
}

void lowercase(wchar_t* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = towlower(str[i]);
    }
}

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

int getproductarraysize(const ProductArray* array) {
    return array->size;
}

bool removeproductfromarray(ProductArray* array, int index) {
    if (index < 0 || index >= array->size) {
        return false;
    }
    for (int i = index; i < array->size - 1; i++) {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
    return true;
}

int findallproductsname(const ProductArray* array, const wchar_t* productName, int** indexfoundproduct) {
    wchar_t searchName[100];
    wcscpy(searchName, productName);
    lowercase(searchName);
    int count = 0;
    int* listindexfoundproduct = new int[array->size];
    for (int i = 0; i < array->size; i++) {
        wchar_t currentName[100];
        wcscpy(currentName, array->data[i].name);
        lowercase(currentName);
        if (wcscmp(currentName, searchName) == 0) {
            listindexfoundproduct[count] = i;
            count++;
        }
    }
    if (count > 0) {
        *indexfoundproduct = new int[count];
        for (int i = 0; i < count; i++) {
            (*indexfoundproduct)[i] = listindexfoundproduct[i];
        }
    } else {
        *indexfoundproduct = nullptr;
    }
    delete[] listindexfoundproduct;
    return count;
}

void inputproduct(ExportProduct* product) {
    wcout << L"Введите наименование товара: ";
    wcin.getline(product->name, 100);
    while (pustyaorprobeli(product->name)) {
        wcout << L"Название не может быть пустым. Введите еще раз: ";
        wcin.getline(product->name, 100);
    }
    wcout << L"Введите страну импортера: ";
    wcin.getline(product->country, 50);
    while (pustyaorprobeli(product->country)) {
        wcout << L"Страна не может быть пустой. Введите еще раз: ";
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
    wcout << L"Товар: " << product->name << L", Страна: " << product->country << L", Количество: " << product->quantity << endl;
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

void findcountriesforproduct(const ProductArray* array, const wchar_t* productName, wchar_t*** countries, int* count) {
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

int removeProductsByName(ProductArray* array, const wchar_t* productName) {
    int* indices = nullptr;
    int count = findallproductsname(array, productName, &indices);
    if (count == 0) {
        wcout << L"Товар '" << productName << L"' не найден." << endl;
        return 0;
    }
    wcout << L"\nНайдено " << count << L" товаров с названием '" << productName << L"':" << endl;
    for (int i = 0; i < count; i++) {
        wcout << i + 1 << L". ";
        printproduct(&array->data[indices[i]]);
    }
    wcout << L"\nВы точно хотите удалить все эти товары? (да/нет): ";
    wchar_t answer[10];
    wcin.getline(answer, 10);
    lowercase(answer);
    int deletedCount = 0;
    if (wcscmp(answer, L"да") == 0) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (indices[j] < indices[j + 1]) {
                    int temp = indices[j];
                    indices[j] = indices[j + 1];
                    indices[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < count; i++) {
            if (removeproductfromarray(array, indices[i])) {
                deletedCount++;
            }
        }
        wcout << L"Удалено " << deletedCount << L" товаров." << endl;
    } else {
        wcout << L"Удаление отменено." << endl;
    }
    if (indices != nullptr) {
        delete[] indices;
    }
    return deletedCount;
}

bool removeProductByIndex(ProductArray* array, int index) {
    if (index < 1 || index > array->size) {
        wcout << L"Неверный номер товара. Выберите значения от 1-" << array->size << endl;
        return false;
    }
    wcout << L"Выбран товар для удаления:" << endl;
    printproduct(&array->data[index - 1]);
    wcout << L"Вы точно хотите удалить этот товар? (да/нет): ";
    wchar_t answer[10];
    wcin.getline(answer, 10);
    lowercase(answer);
    if (wcscmp(answer, L"да") == 0) {
        if (removeproductfromarray(array, index - 1)) {
            wcout << L"Товар успешно удален." << endl;
            return true;
        }
    } else {
        wcout << L"Удаление отменено." << endl;
    }
    return false;
}

void alloperation() {
    wcout << L"\nДемонстрация всех операций\n";
    ProductArray products;
    initProductArray(&products);
    wcout << L"\n1. Добавление товаров:\n";
    ExportProduct p1;
    wcscpy(p1.name, L"Нефть");
    wcscpy(p1.country, L"Китай");
    p1.quantity = 1000;
    addProductToArray(&products, &p1);
    wcout << L"Добавлен: ";
    printproduct(&p1);
    ExportProduct p2;
    wcscpy(p2.name, L"Газ");
    wcscpy(p2.country, L"Германия");
    p2.quantity = 500;
    addProductToArray(&products, &p2);
    wcout << L"Добавлен: ";
    printproduct(&p2);
    ExportProduct p3;
    wcscpy(p3.name, L"Нефть");
    wcscpy(p3.country, L"Индия");
    p3.quantity = 800;
    addProductToArray(&products, &p3);
    wcout << L"Добавлен: ";
    printproduct(&p3);
    ExportProduct p4;
    wcscpy(p4.name, L"Уголь");
    wcscpy(p4.country, L"Германия");
    p4.quantity = 300;
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
    findcountriesforproduct(&products, L"Нефть", &countries, &countriesCount);
    if (countriesCount > 0) {
        wcout << L"Страны, импортирующие товар 'Нефть':\n";
        for (int i = 0; i < countriesCount; i++) {
            wcout << L"  " << i + 1 << L". " << countries[i] << endl;
        }
        deleteCountriesArray(countries, countriesCount);
    } else {
        wcout << L"Товар не найден.\n";
    }
    wcout << L"\n5. Демонстрация удаления всех товаров 'Нефть':\n";
    removeProductsByName(&products, L"Нефть");
    wcout << L"Массив после удаления:" << endl;
    printarray(&products);
    freeProductArray(&products);
}

void printmenu() {
    wcout << L"\nМЕНЮ" << endl;
    wcout << L"1. Создать новый массив товаров" << endl;
    wcout << L"2. Добавить товар" << endl;
    wcout << L"3. Просмотреть все товары" << endl;
    wcout << L"4. Удалить товар" << endl;
    wcout << L"5. Отсортировать по стране (метод пузырька)" << endl;
    wcout << L"6. Найти страны для указанного товара" << endl;
    wcout << L"7. Демонстрация всех операций" << endl;
    wcout << L"8. Выход" << endl;
}

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
                    if (countriesCount == 0) {
                        wcout << L"Товар '" << productName << L"' не найден." << endl;
                    } else {
                        wcout << L"\nСтраны, импортирующие товар '" << productName << L"':" << endl;
                        for (int i = 0; i < countriesCount; i++) {
                            wcout << i + 1 << L". " << countries[i] << endl;
                        }
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