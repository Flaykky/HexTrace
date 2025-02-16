
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


char* readBinaryFile(const char* file_path, size_t* file_size) {
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "Error: Failed to open file %s\n", file_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(size);
    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, size, file) != (size_t)size) {
        fprintf(stderr, "Error: Failed to read file\n");
        fclose(file);
        free(buffer);
        return NULL;
    }

    fclose(file);

    if (file_size) {
        *file_size = (size_t)size;
    }

    // �������������� �������� ������ � ������ � ����������������� �������
    char* hexString = (char*)malloc((size * 2) + 1);
    if (!hexString) {
        fprintf(stderr, "Error: Memory allocation failed for hex string\n");
        free(buffer);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        sprintf(hexString + (i * 2), "%02X", (unsigned char)buffer[i]);
    }
    hexString[size * 2] = '\0';

    free(buffer);
    return hexString;
}



void createDisAsmFile(const char* asmCode) {
    
    FILE* file = fopen("output.asm", "w");


    if (file) {
        fputs(asmCode, file);
        fclose(file); 
    }

    else {
        fprintf(stderr, "Error: Failed to create output file\n");
    }
}
