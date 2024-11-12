#ifndef STD2_DEF_H
#define STD2_DEF_H

#include <stdio.h>
#include <stdlib.h> // For malloc, free
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#include "types.h"
#include "files.h"
#include "array.h"
#include "io.h"
#include "linked.h"

#define foreach(y,x) \
	char* y;\
	for (size_t _=0; (y = (char*)x->Data[_]) && _<x->ElemCount; ++_)

void _test();

#endif // STD2_DEF_H
