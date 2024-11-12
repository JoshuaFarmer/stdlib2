#include <std2/stdlib2.h>

int main() {
	// its just "typedef Array String"
	// create arr with size 0
	String arr = newA(0);

	// get input (appends so it safe, 100%)
	// its (Array*, Echo?<bool>)
	bool res = input(&arr, true);
	insert(&arr, "Hello, World!\0", ARR_CSTRING, 14, 1);
	print(arr);
	popx(&arr, 1);
	print(arr);
	delA(arr);
	return 0;
}
