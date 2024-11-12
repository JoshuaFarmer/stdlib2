#ifndef STD2_LINKED_H
#define STD2_LINKED_H

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void append_node(Linked list, Array value);
void pop_node(Linked list);
void delete_list(Linked list);
Linked new_list(Array init_value);

#endif
