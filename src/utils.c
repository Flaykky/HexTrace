
#include "disAssembler.h"
#include <stdio.h>
#include <basetsd.h>

size_t calculateSize(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "Error: Failed to open file %s\n", file_path);
        return 0;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    fclose(file);
    
    return size;
}

