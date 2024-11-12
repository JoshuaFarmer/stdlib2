#include <stdlib2.h>

int main()
{
	print("Hello, World!\n");
	Array arr = newA(0);
	push(&arr, "Hello", ARR_CSTRING, 6);
	Linked list = new_list(arr);
	print(list);
	delete_list(list); // automatically deletes arrays
	return 0;
}
