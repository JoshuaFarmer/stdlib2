#include <std2/stdlib2.h>

int main() {
	// its just "typedef Array String"
	// create arr with size 0
	String arr = newA(0);

	// get input (appends so it safe, 100%)
	// its (Array*, Echo?<bool>)
	bool res = input(&arr, true);
	if (res)
		print(arr);
	Array arr2 = newA(0);
	strip(arr, arr2, ',');
	print(arr2);
	delA(arr);
	return 0;
}
