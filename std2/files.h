#ifndef STD2_FILES_H
#define STD2_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "stdlib2.h"

typedef struct {
	FILE* fp;		// the actual file
	long  size;
	_u8*  data;		// read on open() if read mode
	char* mode;
} _File_t;

typedef _File_t* File_t;

File_t open( const char* filePath, const char* mode);
long _close(File_t file);
long write(File_t file, Array  data);

#define close(f) ({_close(f); f = NULL;})

#endif