#ifndef STD2_ARR_H
#define STD2_ARR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "types.h"

#define at(arr, at) arr->Data[at]
void* memdup(void* dat, size_t size);

Array newA(size_t count);
void delA(Array arr);
void push(Array* arr, void* data, ArrayElem_t ty, size_t s);
void insert(Array* arr, void* data, ArrayElem_t ty, size_t s, size_t n);
void pop(Array* arr);
void popx(Array* arr, size_t n);
int compare(Array a, Array b);
Array split(const char* _data, char* delim);
void strip(char* str, char x);

#endif