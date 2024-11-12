#include <stdlib2.h>

int main()
{
	print("Hello, World!\n");
	Array arr = newA(0);
	push(&arr, "Hello", ARR_CSTRING);
	Linked list = new_list(arr);
	Array arr2 = newA(0);
	push(&arr2, "Hello 2", ARR_CSTRING);
	append_node(list, arr2);
	println(list);
	delete_list(list); // automatically deletes arrays
	return 0;
}
