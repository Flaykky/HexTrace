#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <capstone/capstone.h>
#include "include/disAssembler.h"


// Простой дизассемблер для Windows


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

    // Преобразование бинарных данных в строку в шестнадцатеричном формате
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

// Функция дизассемблирования
char* disassemble(const char* binaryCode, size_t codeSize, uint64_t address) {
    csh handle;
    cs_insn* insn;
    size_t count;

    // Инициализация Capstone для архитектуры x86-64
    if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
        fprintf(stderr, "Error: Failed to initialize Capstone\n");
        return NULL;
    }

    // Дизассемблирование
    count = cs_disasm(handle, (const uint8_t*)binaryCode, codeSize, address, 0, &insn);
    if (count > 0) {
        // Вычисляем размер буфера для хранения результатов
        size_t bufferSize = 0;
        for (size_t i = 0; i < count; i++) {
            bufferSize += strlen(insn[i].mnemonic) + strlen(insn[i].op_str) + 2; // +2 для пробела и перевода строки
        }

        char* result = (char*)malloc(bufferSize + 1);
        if (!result) {
            fprintf(stderr, "Error: Memory allocation failed for disassembly result\n");
            cs_free(insn, count);
            cs_close(&handle);
            return NULL;
        }

        // Формируем строку с результатами дизассемблирования
        size_t offset = 0;
        for (size_t i = 0; i < count; i++) {
            offset += sprintf(result + offset, "%s %s\n", insn[i].mnemonic, insn[i].op_str);
        }
        result[offset] = '\0';

        cs_free(insn, count);
        cs_close(&handle);
        return result;
    } else {
        fprintf(stderr, "Error: Failed to disassemble code\n");
        cs_close(&handle);
        return NULL;
    }
}




void createDisAsmFile(const char* asmCode) {
    FILE* file = fopen("output.asm", "w");
    if (file) {
        fputs(asmCode, file);
        fclose(file);
    } else {
        fprintf(stderr, "Error: Failed to create output file\n");
    }
}