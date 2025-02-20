#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <vcruntime.h>

size_t calculateSize(const char* file_path);
uint8_t* readBinaryFile(const char* file_path, size_t* file_size);
void createDisAsmFile(const char* asmCode);

#endif
