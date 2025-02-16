#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <capstone/capstone.h>
#include "include/disAssembler.h"
#include "include/utils.h"

// Простой дизассемблер для Windows


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

