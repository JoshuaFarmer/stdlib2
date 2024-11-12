#include <stdlib2.h>

const size_t ArrayElemSizes[] = {
	-1, -1, 4, 4, 4, -1, sizeof(_Array), 1
};

void test() {
	println("Hello, from std2!");
}

void _printArray(Array, ...);

int _printArrayElem(ArrayElem_t ty, Array arr, size_t e, int i) {
	int ret = 1;

	if (ArrayElemSizes[ty] != (unsigned long long)-1 && ArrayElemSizes[ty] != arr->ElemSize[e])
		return ret;
	switch (ty) {
		case ARR_OTHER:
			printf("%.2x", arr->Data[e][i]);
			ret = 0;
			break;
		case ARR_BYTE:
			printf("%d", arr->Data[e][i]);
			ret = 0;
			break;
		case ARR_INT: {
			int r = arr->Data[e][i];
			r |= arr->Data[e][i+1] << 8;
			r |= arr->Data[e][i+2] << 16;
			r |= arr->Data[e][i+3] << 24;
			printf("%d", r);
			}
			break;
		case ARR_HEX: {
			int r = arr->Data[e][i];
			r |= arr->Data[e][i+1] << 8;
			r |= arr->Data[e][i+2] << 16;
			r |= arr->Data[e][i+3] << 24;
			printf("%.4x", r);
			}
			break;
		case ARR_SHORT: {
			int r = arr->Data[e][i];
			r |= arr->Data[e][i+1] << 8;
			printf("%.4x", r);
			}
			break;
		case ARR_FLOAT: {
			int r = arr->Data[e][i];
			r |= arr->Data[e][i+1] << 8;
			r |= arr->Data[e][i+2] << 16;
			r |= arr->Data[e][i+3] << 24;
			printf("%f", (float)r);
			}
			break;
		case ARR_CSTRING: {
			char* x = strdup((char*)arr->Data[e]);
			stripCStr(x, '\r');
			printf("\"%s\"", x);
			free(x);
			}
			break;
		case ARR_ARRAY: {
			Array arr0 = (Array)arr->Data[e];
			_printArray(arr0);
			}
			break;
		case ARR_CHAR: {
			char v = arr->Data[e][i];
			printf("'%c'", v);
			} break;
	}
	return ret;
}

void _printArray(Array arr, ...) {
	static int in = 0;
	int _ = in;
	in = 1;

	if (!arr) return;

	printf("{");
	for (size_t i = 0; i < arr->ElemCount; ++i) {
		if (arr->ElemSize[i] == 0) {
			printf("None");
			continue;
		}

		switch (arr->ElemType[i]) {
			case ARR_OTHER:
			case ARR_BYTE:
				printf("%.2x", (char)*arr->Data[i]);
				break;
			case ARR_CHAR:
				printf("%c", (char)*arr->Data[i]);
				break;
			case ARR_SHORT:
				printf("%.4x", (uint16_t)*arr->Data[i]);
				break;
			case ARR_INT:
				printf("%d", (int)*arr->Data[i]);
				break;
			case ARR_FLOAT:
				printf("%f", (float)*arr->Data[i]);
				break;
			case ARR_HEX:
				printf("%.8x", (int)*arr->Data[i]);
				break;
			case ARR_ARRAY: {
				Array arr2 = *((Array*)(void*)arr->Data[i]);
				_printArray(arr2);
				break;
			}
			case ARR_CSTRING: {
				for (size_t x = 0; x < arr->ElemSize[i]; ++x)
					_print((char)arr->Data[i][x]);
				break;
			}

			default:
				break;
		}
	
		if (i < arr->ElemCount-1)
			printf(", ");
	}
	printf("}");

	if (_ == 0) {
		in = 0;
	}
}

void _printIntP(int* i, ...) {
	printf("%d", *i);
	va_list args;
	va_start(args, i);
	while (1) {
		int* next = va_arg(args, int*);
		if ((int64_t)next) break;  // Sentinel value to stop printing
		printf("%d", *next);
	}
	va_end(args);
}

void _printInt(int i, ...) {
	printf("%d", i);
	va_list args;
	va_start(args, i);
	while (1) {
		int next = va_arg(args, int);
		if (next == -1) break;  // Sentinel value to stop printing
		printf("%d", next);
	}
	va_end(args);
}

void _printDouble(double d, ...) {
	printf("%.2lf", d);
	va_list args;
	va_start(args, d);
	while (1) {
		double next = va_arg(args, double);
		if (next == -1.0) break;  // Sentinel value to stop printing
		printf("%.2lf", next);
	}
	va_end(args);
}

void _printString(char* str, ...) {
	printf("%s", str);
	va_list args;
	va_start(args, str);
	char* next;
	while (1) {
		next = va_arg(args, char*);
		if ((int64_t)next) break;  // Sentinel value to stop printing
		printf("%s", next);
	}
	va_end(args);
}

void _printChar(char c, ...) {
	printf("%c", c);
	va_list args;
	va_start(args, c);
	char next;
	while (1) {
		next = va_arg(args, int);
		if (next == -1) break;  // Sentinel value to stop printing
		printf("%c", next);
	}
	va_end(args);
}

void _printLinked(Linked list, ...)
{
	printf("(");
	while (list != NULL)
	{
		_printArray(list->value);
		list = list->Next;
		if (list != NULL) {
			printf(", ");
		}
	}
	printf(")");
}

// Initialization functions with variable arguments
void initInt(int* value, ...) {
	va_list args;
	va_start(args, value);
	*value = va_arg(args, int); // Get the first argument for initialization
	va_end(args);
}

void initDouble(double* value, ...) {
	va_list args;
	va_start(args, value);
	*value = va_arg(args, double); // Get the first argument for initialization
	va_end(args);
}

void initString(char** value, ...) {
	va_list args;
	va_start(args, value);
	*value = va_arg(args, char*); // Get the first argument for initialization
	va_end(args);
}

void initGeneric(void* value, ...) {
	printf("Unsupported type, at: %p\n", value);
}

