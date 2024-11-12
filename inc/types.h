#ifndef STD2_TYPES_H
#define STD2_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#define sfree(x) del(x)
#define si sizeof

typedef uint8_t  _u8;
typedef uint16_t _u16;
typedef uint32_t _u32;
typedef uint64_t _u64;

typedef int8_t  _i8;
typedef int16_t _i16;
typedef int32_t _i32;
typedef int64_t _i64;

typedef uint8_t*  u8;
typedef uint16_t* u16;
typedef uint32_t* u32;
typedef uint64_t* u64;

typedef int8_t*  i8;
typedef int16_t* i16;
typedef int32_t* i32;
typedef int64_t* i64;

#define Chr(x) *(char*)x

typedef int* Int;

typedef struct {
	double x, y;
} _Vec2;

typedef struct {
	int64_t x, y;
} _Vec2i;

typedef struct {
	double x, y, z;
} _Vec3;

typedef struct {
	int64_t x, y, z;
} _Vec3i;

typedef struct {
	double x, y, z, w;
} _Vec4;

typedef struct {
	int64_t x, y, z, w;
} _Vec4i;

typedef enum {
	ARR_BYTE,
	ARR_SHORT,
	ARR_CSTRING,
	ARR_INT,
	ARR_HEX,
	ARR_FLOAT,
	ARR_OTHER, // use type casting
	ARR_ARRAY,
	ARR_CHAR,
	ARR_LINKED,
} ArrayElem_t;

typedef struct _s_Array {
	ArrayElem_t* ElemType;
	size_t  ElemCount;
	size_t* ElemSize;
	u8*     Data;
} _Array;

typedef _Vec2* Vec2;
typedef _Vec2i* Vec2i;
typedef _Vec3* Vec3;
typedef _Vec3i* Vec3i;
typedef _Vec4* Vec4;
typedef _Vec4i* Vec4i;

typedef _Array* Array;
typedef _Array* String;

typedef struct _Node_s {
	Array value;
	struct _Node_s* Next;
	struct _Node_s* Prev;
} _Node;

typedef _Node* Linked;
#include "linked.h"

typedef struct { int is_void; void* data; size_t length; } Something;
#define Void (Something){1, NULL, 0};
#define Smth(x) (Something){0, x, sizeof(x)}

typedef struct {
	Something (*functionPtr)(int,...);
} _function;

#define HAS_ARGS(...)	(sizeof((int[]){__VA_ARGS__}) > 0)
#define init_with_args(ptr, ...) \
	_Generic((ptr), \
		int*: initInt, \
		double*: initDouble, \
		char**: initString, \
		default: initGeneric \
	)(__VA_ARGS__)

#define new(t, ...) ({ \
	t ptr = (t)malloc(sizeof(*ptr)); \
	if (ptr) { \
		if (HAS_ARGS(__VA_ARGS__)) { \
			init_with_args(ptr, __VA_ARGS__); \
		} else { \
			initGeneric(ptr); \
		} \
	} \
	ptr; \
})

#define newc(t, n) { \
	t ptr = (t)malloc(sizeof(*ptr) * (n)); \
	if (ptr) memset(ptr, 0, sizeof(*ptr) * (n)); \
	ptr; \
}

#define del(x) {free(x); x = NULL;}

// Initialization functions with variable arguments
void initInt(int* value, ...);
void initDouble(double* value, ...);
void initString(char** value, ...);
void initGeneric(void* value, ...);

typedef enum {
	Success,
	Error,
} StdError;

// Generic print function
#define print(value, ...) _Generic((value), \
	int: _printInt, \
	int*: _printIntP, \
	double: _printDouble, \
	char*: _printString, \
	const char*: _printString, \
	char: _printChar, \
	Array: _printArray, \
	Linked: _printLinked \
)(value, ##__VA_ARGS__, -1, NULL)

#define _print(value) _Generic((value), \
	int: _printInt, \
	int*: _printIntP, \
	double: _printDouble, \
	char*: _printString, \
	const char*: _printString, \
	char: _printChar, \
	Array: _printArray, \
	Linked: _printLinked, \
	default: _printInt \
)(value, -1, NULL)

#define println(value, ...) { \
	print(value, ##__VA_ARGS__); \
	printf("\n"); \
}

int _printArrayElem(ArrayElem_t ty, Array arr, size_t e, int i);
void _printArray(Array arr, ...);
void _printIntP(int* i, ...);
void _printInt(int i, ...);
void _printDouble(double d, ...);
void _printString(char* str, ...);
void _printChar(char c, ...);
void _printLinked(Linked list, ...);

#define is_null(x) (x == NULL)

#endif
