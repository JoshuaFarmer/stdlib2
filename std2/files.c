#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "files.h"

File_t open(
	const char* filePath,
	const char* mode
) {
	// initialization
	File_t file = malloc(sizeof(_File_t));
	if (!file) {
		return NULL;
	}

	FILE* fp = fopen(filePath, mode);
	if (!fp) {
		sfree(file);
		return NULL;
	}

	file->fp = fp;
	file->mode = strdup(mode);
	if (!file->mode) {
		fclose(fp);
		sfree(file);
		return NULL;
	}
	
	// get the length
	if (fseek(fp, 0x00, SEEK_END)) {
		fclose(fp);
		sfree(file->mode);
		sfree(file);
		return NULL;
	}

	long fileSize = ftell(fp);
	if (fileSize == -1L) {
		fclose(fp);
		sfree(file->mode);
		sfree(file);
		return NULL;
	}

	if (fseek(fp, 0x00, SEEK_SET)) {
		fclose(fp);
		sfree(file->mode);
		sfree(file);
		return NULL;
	}

	// get the data*
	if (mode[0] == 'r') {
		file->data = malloc(sizeof(_u8) * fileSize);
		long read = fread(file->data, 1, fileSize, fp);
		if (fileSize != read) {
			fclose(fp);
			sfree(file->data);
			sfree(file->mode);
			sfree(file);
			return NULL;
		}
	} else {
		file->data = NULL;
	}

	file->size = fileSize;
	return file;
}

long _close(
	File_t file
) {
	if (!file || !file->fp) {
		return 1;
	}

	free(file->data);
	free(file->mode);
	fclose(file->fp);
	free(file);
	return 0;
}

long write(
	File_t file,
	Array  data
) {
	if (!file || !data || !file->fp || !data->Data || data->ElemCount == 0 || data->ElemSize == 0) {
		return -1;
	}

	// Write the data to the file
	size_t written=0;
	for (size_t i = 0; i < data->ElemCount; ++i) {
		written = fwrite(data->Data[i], data->ElemSize[i], 1, file->fp);
		if (written != data->ElemSize[i]) {
			return -1; // Indicate a write error
		}
		file->size += (long)(data->ElemSize[i] * data->ElemCount);
	}

	return (long)written; // Return the number of elements written
}
