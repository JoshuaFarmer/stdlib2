#include <std2/stdlib2.h>

int main() {
	Array arr = newA(0);
	bool res = input(&arr, true);
	if (res)
		print(arr);
	delA(arr);
	return 0;
}
