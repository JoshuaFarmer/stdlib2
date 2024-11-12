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
void push(Array* arr, void* data, ArrayElem_t ty);
void insert(Array* arr, void* data, ArrayElem_t ty, size_t n);
void vinsert(Array* arr, void* data, ArrayElem_t ty, size_t s, size_t n);	// custom length (DISCOURAGED OUTSIDE OF STRUCTS)
void vpush(Array* arr, void* data, ArrayElem_t ty, size_t s);					// custom length (DISCOURAGED OUTSIDE OF STRUCTS)
void pop(Array* arr);
void popx(Array* arr, size_t n);
int compare(Array a, Array b);
Array split(const char* _data, char* delim);
void stripCStr(char* str, char x);
void strip(Array arr, Array out, char c);
Array clone(Array arr);

#endif