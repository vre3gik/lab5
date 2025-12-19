#ifndef UNIT_OPERATION_H
#define UNIT_OPERATION_H
#include "Unit_Воробьев_9.h"

void initProductArray(ProductArray* array);
void freeProductArray(ProductArray* array);
void resizeProductArray(ProductArray* array, int newCapacity);
void addProductToArray(ProductArray* array, const ExportProduct* product);
ExportProduct* getProductFromArray(const ProductArray* array, int index);
int getproductarraysize(const ProductArray* array);
bool removeproductfromarray(ProductArray* array, int index);
int findallproductsname(const ProductArray* array, const wchar_t* productName, int** indexfoundproduct);

void bubbleSortByCountry(ProductArray* array);
void findcountriesforproduct(const ProductArray* array, const wchar_t* productName, wchar_t*** countries, int* count);
void deleteCountriesArray(wchar_t** countries, int count);
int removeProductsByName(ProductArray* array, const wchar_t* productName);  
bool removeProductByIndex(ProductArray* array, int index);
void alloperation();

#endif