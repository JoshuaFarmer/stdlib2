#include "linked.h"

static Linked find_last_element(Linked list)
{
	Linked elem = list;
	Linked next = list->Next;
	while (next != NULL)
	{
		elem = next;
		next = elem->Next;
	}

	return elem;
}

Linked find_node(Linked list, size_t n) {
	if (!list) {
		printf("Failed to find node at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		return NULL;
	}

	Linked item = list;
	for (size_t i = 0; i < n && item->Next != NULL; ++i) {
		item = item->Next;
	}
	return item;
}

Array get_node(Linked list, size_t n) {
	Linked item = find_node(list, n);
	return item->value;
}

void set_node(Linked list, size_t n, Array x)
{
	if (!list) {
		printf("Failed to set node at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		return;
	}

	Linked item = find_node(list, n);
	item->value = x;
}

void append_node(Linked list, Array value)
{
	if (!list) {
		printf("Failed to append node at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		return;
	}
	
	Linked last = find_last_element(list);
	if (!last) {
		printf("Failed to append node at: %p\nReason: FAILED TO FIND LAST\n", (void*)list);
		return;
	}
	
	Linked new = calloc(1, sizeof(_Node));
	if (!new) {
		printf("Failed to create node at: %p\nReason: FAILED TO ALLOCATE\n", (void*)list);
		return;
	}

	last->Next = new;
	new->Prev = last;
	new->value = value;
}

void pop_node(Linked list)
{
	if (!list) {
		printf("Failed to pop node at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		return;
	}

	Linked last = find_last_element(list);
	if (!last) {
		printf("Failed to pop node at: %p\nReason: FAILED TO FIND LAST\n", (void*)list);
		return;
	}

	Linked prev = last->Prev;
	prev->Next = NULL;
	last->Prev = NULL;
	if (last->value)
		delA(last->value);
	free(last);
	last = NULL;
}

void create_node(Linked* list, Array value, size_t n)
{
	if (!list || !*list) {
		printf("Failed to create node at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		return;
	}

	Linked elem = find_node(*list, n);
	if (!elem) {
		printf("Failed to create node at: %p\nReason: FAILED TO FIND ELEM\n", (void*)list);
		return;
	}
	
	Linked new = calloc(1, sizeof(_Node));
	if (!new) {
		printf("Failed to create node at: %p\nReason: FAILED TO ALLOCATE\n", (void*)list);
		return;
	}

	// Set the new node's value
	new->value = value;

	Linked prev = elem->Prev;

	if (prev != NULL) {
		// Inserting between two nodes
		prev->Next = new;
		new->Prev = prev;
		new->Next = elem;
		elem->Prev = new;
	} else {
		// Inserting at the root (beginning) of the list
		new->Next = *list;
		(*list)->Prev = new;
		*list = new;
	}
}

void delete_node(Linked* list, size_t n)
{
	if (!list || !*list) {
		printf("Failed to delete node at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		return;
	}

	Linked elem = find_node(*list, n);
	if (!elem) {
		printf("Failed to delete node at: %p\nReason: FAILED TO FIND ELEM\n", (void*)list);
		return;
	}

	Linked prev = elem->Prev;
	elem->Prev = NULL;

	if (prev != NULL) {
		prev->Next = elem->Next;
		elem->Next->Prev = prev;
	} else { // root node
		elem->Next->Prev = prev;
		*list = elem->Next;
	}

	if (elem->value)
		delA(elem->value);
	free(elem);
	elem = NULL;
}

void delete_list(Linked list)
{
	if (!list) {
		printf("Failed to delete list at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		return;
	}

	Linked last = find_last_element(list);
	if (!last) {
		printf("Failed to delete list at: %p\n", (void*)list);
		return;
	}

	while (last != list && last != NULL) {
		delA(last->value);
		last = last->Prev;
		free(last->Next);
	}
}

Linked new_list(Array init_value)
{
	Linked list = calloc(1, sizeof(_Node));
	if (!list) {
		printf("Failed to create list at: %p\n", (void*)list);
		return NULL;
	}

	list->Next = NULL;
	list->Prev = NULL;
	list->value = NULL;

	if (init_value != NULL)
	{
		list->value = init_value;
	}

	return list;
}

size_t find_list_length(Linked list) {
	if (!list) {
		printf("Failed to find list length at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		return 0;
	}

	Linked item = list;
	size_t i;
	for (i=1; item->Next != NULL; ++i) {
		item = item->Next;
	}

	return i;
}

Linked copy_list(Linked list) {
	size_t s = find_list_length(list);
	if (s == 0) {
		printf("Failed to copy list at: %p\nReason: NO VALID LIST PROVIDED\n", (void*)list);
		NULL;
	}

	Linked new = new_list(list->value);
	for (size_t i = 1; i < s; ++i) {
		Array arr = clone(get_node(list, i));
		append_node(new, arr);
	}

	return new;
}
