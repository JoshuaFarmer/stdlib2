#include <std2/stdlib2.h>

int main() {
	// array with size zero
	Array arr = newA(0);
	push(&arr, "Array", ARR_CSTRING, 6);
	push(&arr, "Test", ARR_CSTRING, 5);

	int exampleValue = 65;
	push(&arr, &exampleValue, ARR_INT, 4);

	print((char*)arr->Data[102222222]);
	delA(arr);
	return 0;
}
