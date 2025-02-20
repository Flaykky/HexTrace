#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

size_t calculateSize(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (!file) return 0;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return (size_t)size;
}

uint8_t* readBinaryFile(const char* file_path, size_t* file_size) {
    FILE* file = fopen(file_path, "rb");
    if (!file) return NULL;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    uint8_t* buffer = (uint8_t*)malloc(size);
    if (!buffer) {
        fclose(file);
        return NULL;
    }
    
    fread(buffer, 1, size, file);
    fclose(file);
    
    if (file_size) *file_size = (size_t)size;
    return buffer;
}

void createDisAsmFile(const char* asmCode) {
    FILE* file = fopen("output.asm", "w");
    if (file) {
        fputs(asmCode, file);
        fclose(file);
    }
}
