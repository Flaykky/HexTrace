#ifndef disAssembler_H
#define disAssembler_H

#ifdef __cplusplus
extern "C" {
#endif

// ======= структуры ======= 

typedef struct {
    char* buffer;
    int size;
} BinaryFile;

typedef struct {
    char* buffer;
    int size;
} AsmFile;

#include <sys/types.h>
#include <baseTsd.h>


// ======= обьявление функций =======

// основная функция для дизассемблера
char* disAssembler(const char* binaryCode, size_t codeSize, uint64_t address);
// должна принимать чтото типо такого: 0x55, 0x48, 0x89, 0xe5, а возвращать push rbp mov rbp, rsp и тд 


#ifdef __cplusplus
}
#endif

#endif 
