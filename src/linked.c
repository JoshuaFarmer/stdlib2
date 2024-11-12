#include "linked.h"
// untested

static Linked find_last_element(Linked list)
{
	Linked elem = list;
	while (elem != NULL)
	{
		elem = elem->Next;
	}

	return elem;
}

void append_node(Linked list, Array value)
{
	Linked last = find_last_element(list);
	if (!last) return;
	
	Linked new = calloc(1, sizeof(_Node));
	last->Next = new;
	new->Prev = last;
	new->value = value;
}

void pop_node(Linked list)
{
	Linked last = find_last_element(list);
	if (!last) return;
}

void delete_list(Linked list)
{
	Linked last = find_last_element(list);
	if (!last) return;

	while (last != list && last != NULL) {
		delA(last->value);
		last = last->Prev;
		free(last->Next);
	}
}

Linked new_list(Array init_value)
{
	Linked list = calloc(1, sizeof(_Node));
	if (!list) return NULL;

	if (init_value != NULL)
	{
		list->value = init_value;
	}

	return list;
}

