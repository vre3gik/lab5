#ifndef UNIT_OPERATION_H
#define UNIT_OPERATION_H


#include "Unit_Воробьев_9.h"


void initProductArray(ProductArray* array);                        
void freeProductArray(ProductArray* array);                         
void addProductToArray(ProductArray* array, const ExportProduct* product); 
ExportProduct* getProductFromArray(const ProductArray* array, int index);  
int getProductArraySize(const ProductArray* array);                

void resizeProductArray(ProductArray* array, int newCapacity);     
void bubbleSortByCountry(ProductArray* array);                   
void findCountriesForProduct(const ProductArray* array,          
                            const wchar_t* productName, 
                            wchar_t*** countries, 
                            int* count);
void deleteCountriesArray(wchar_t** countries, int count);         
void demonstrateAllOperations();                                

#endif