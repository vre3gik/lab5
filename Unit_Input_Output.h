#ifndef UNIT_INPUT_OUTPUT_H
#define UNIT_INPUT_OUTPUT_H
#include "Unit_Воробьев_9.h"

bool pustyaorprobeli(const wchar_t* str);           
void delprobelsinword(wchar_t* str);                
void lowercase(wchar_t* str);                       
void inputproduct(ExportProduct* product);          
void printproduct(const ExportProduct* product);    
void printarray(const ProductArray* array);         
void printmenu();                                
void printresults(const wchar_t* productName, wchar_t** countries, int countriesCount);

#endif