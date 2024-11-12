#ifndef STD2_LINKED_H
#define STD2_LINKED_H

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Linked find_node(Linked list, size_t n);
Array get_node(Linked list, size_t n);
void set_node(Linked list, size_t n, Array x);
void create_node(Linked* list, Array value, size_t n);
void delete_node(Linked* list, size_t n);
void append_node(Linked list, Array value);
void pop_node(Linked list);
void delete_list(Linked list);
Linked new_list(Array init_value);
size_t find_list_length(Linked list);
Linked copy_list(Linked list);

#endif
