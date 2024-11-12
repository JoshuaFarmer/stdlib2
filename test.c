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
	Array arr3 = newA(0);
	push(&arr3, "Hello 3", ARR_CSTRING);
	create_node(&list, arr3, 0);
	println(list);
	delete_node(&list, 0);
	println(list);
	println((int)find_list_length(list));
	Linked list2 = copy_list(list);
	println(list2);

	delete_list(list); // automatically deletes arrays
	delete_list(list2); // automatically deletes arrays

	Array arr4 = newA(0);
	push(&arr4, "list", ARR_CSTRING);
	Linked arrlist = new_list(arr4);

	Array arr5 = newA(0);
	push(&arr5, &arrlist, ARR_LINKED);
	printf("DEBUG3: %lu\n", arr5->ElemSize[0]);
	printf("DEBUG2: %p\n", arrlist);
	println(arr5);
	delete_list(arrlist); // automatically deletes arrays
	delA(arr5);
	return 0;
}
