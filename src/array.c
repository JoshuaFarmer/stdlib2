#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "array.h"

Array newA(size_t count) {
	Array arr = (Array)malloc(sizeof(_Array));
	if (!arr) return NULL;

	arr->ElemSize = (size_t*)calloc(count, sizeof(size_t));
	arr->ElemType = (ArrayElem_t*)calloc(count, sizeof(size_t));
	arr->ElemCount = count;
	arr->Data = calloc(count, sizeof(u8));
	for (size_t i = 0; i < count; ++i) {
		arr->Data[i] = (u8)calloc(1, 1);
		arr->ElemSize[i] = 1;
		arr->ElemType[i] = ARR_BYTE;
	}
	return arr;
}

void delA(Array arr) {
	if (!arr) return;

	for (size_t i = 0; i < arr->ElemCount; ++i) {
		sfree(arr->Data[i]);
	}
	sfree(arr->Data);
	sfree(arr->ElemSize);
	sfree(arr->ElemType);
	sfree(arr);
}

void* memdup(void* dat, size_t size) {
	if (!dat) return NULL;

	char* dat1 = (char*)calloc(1, size);
	memcpy(dat1, dat, size);
	return dat1;
}

void push(Array* arr, void* data, ArrayElem_t ty, size_t s) {
	if (!arr || !*arr || !data) return;

	Array oldArr = *arr;
	Array newArr = newA(oldArr->ElemCount + 1);

	// copy sizes
	memcpy(newArr->ElemSize,
			 oldArr->ElemSize,
			 oldArr->ElemCount * si(size_t));
	// copy types
	memcpy(newArr->ElemType,
			 oldArr->ElemType,
			 newArr->ElemCount * si(ArrayElem_t));
	newArr->ElemSize[oldArr->ElemCount] = s;

	// copy data
	for (size_t i = 0; i < oldArr->ElemCount; ++i)
		newArr->Data[i] = (u8)memdup(oldArr->Data[i], oldArr->ElemSize[i]);
	newArr->Data[oldArr->ElemCount] = (u8)memdup(data, s);
	newArr->ElemType[oldArr->ElemCount] = ty;

	// del old
	delA(oldArr);
	*arr = newArr;
}

void insert(Array* arr, void* data, ArrayElem_t ty, size_t s, size_t n) {
	if (!arr || !*arr || !data) return;

	Array oldArr = *arr;
	if (n > oldArr->ElemCount) return;

	Array newArr = newA(oldArr->ElemCount + 1); // Allocate space for the new array

	// Copy elements before the insertion point
	for (size_t i = 0; i < n; ++i) {
		newArr->Data[i] = memdup(oldArr->Data[i], oldArr->ElemSize[i]);
		newArr->ElemSize[i] = oldArr->ElemSize[i];
		newArr->ElemType[i] = oldArr->ElemType[i];
	}

	// Insert the new element
	newArr->Data[n] = memdup(data, s);
	newArr->ElemSize[n] = s;
	newArr->ElemType[n] = ty;

	// Copy the remaining elements
	for (size_t i = n; i < oldArr->ElemCount; ++i) {
		newArr->Data[i + 1] = memdup(oldArr->Data[i], oldArr->ElemSize[i]);
		newArr->ElemSize[i + 1] = oldArr->ElemSize[i];
		newArr->ElemType[i + 1] = oldArr->ElemType[i];
	}

	// Delete old array
	delA(oldArr);
	*arr = newArr;
}

void pop(Array* arr) {
	if (!arr || !*arr) return;
	Array oldArr = *arr;
	Array newArr = newA(oldArr->ElemCount - 1);

	// copy sizes
	memcpy(newArr->ElemSize,
			 oldArr->ElemSize,
			 newArr->ElemCount * si(size_t));

	// copy types
	memcpy(newArr->ElemType,
			 oldArr->ElemType,
			 newArr->ElemCount * si(ArrayElem_t));

	// copy data
	for (size_t i = 0; i < newArr->ElemCount; ++i)
		newArr->Data[i] = (u8)memdup(oldArr->Data[i], oldArr->ElemSize[i]);

	// del old
	delA(oldArr);
	*arr = newArr;
}

void popx(Array* arr, size_t n) {
	if (!arr || !*arr) return;
	Array oldArr = *arr;
	if (n > oldArr->ElemCount) return;
	Array newArr = newA(0);

	for (size_t i = 0; i < n; ++i) {
		push(&newArr, oldArr->Data[i], oldArr->ElemType[i], oldArr->ElemSize[i]);
	}

	for (size_t i = n+1; i < oldArr->ElemCount; ++i) {
		push(&newArr, oldArr->Data[i], oldArr->ElemType[i], oldArr->ElemSize[i]);
	}

	// Delete old
	delA(oldArr);
	*arr = newArr;
}

int compare(Array a, Array b) {
	if (!a || !b) return 1;
	if (a->ElemCount != b->ElemCount) return 1;
	for (size_t i = 0; i < a->ElemCount; ++i) {
		if (a->ElemType[i] != b->ElemType[i])
			return 2;
		if (a->ElemSize[i] != b->ElemSize[i])
			return 3;
		for (size_t y = 0; y < a->ElemSize[i]; ++y) {
			if (a->Data[i][y] != b->Data[i][y])
				return 4;
		}
	}

	return 0;
}

Array split(
	const char* _data,
	char* delim
) {
	if (!_data || !delim) return NULL;
	char* data = strdup(_data);

	Array arr = newA(0);
	char* pch = strtok(data, delim);
	while (pch != NULL)
	{
		push(&arr, pch, ARR_CSTRING, strlen(pch));
		pch = strtok(NULL, delim);
	}
	sfree(data);
	return arr;
}

void stripCStr(
	char* str,
	char x
) {
	if (!str || !x) return; // Check for null input or invalid character

	char* src = str; // Source pointer to traverse the string
	char* dst = str; // Destination pointer to build the new string

	// Traverse the original string
	while (*src) {
		if (*src != x) { // If current character is not x
			*dst = *src; // Copy character to the destination
			dst++; // Move to the next position in the destination
		}
		src++; // Move to the next character in the source
	}
	*dst = '\0'; // Null-terminate the modified string
}

void strip(
	Array arr,
	Array out,
	char c
) {
	if (!arr || !c || (arr->ElemCount == 0) || !out) return; // Check for null input or invalid character

	for (size_t i = 0; i < arr->ElemCount; ++i) {
		for (size_t x = 0; x < arr->ElemSize[i]; ++x) {
			if (at(arr, i)[x] != c) {
				char c = at(arr, i)[x];
				push(&out, &c, ARR_CHAR, 1);
			}
		}
	}
}
