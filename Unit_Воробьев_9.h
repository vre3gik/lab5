#ifndef UNIT_VOROBEV_9_H
#define UNIT_VOROBEV_9_H

#include <cwchar>

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

#endif