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




// ======= обьявление функций =======

// чтение бинарника
char* readBinaryFile(const char* file_path, size_t* file_size);
// должна возвращать чтото типо такого: 0x55, 0x48, 0x89, 0xe5, 



// основная функция для дизассемблера
char* disAssembler(const char* binaryCode, size_t codeSize, uint64_t address);
// должна принимать чтото типо такого: 0x55, 0x48, 0x89, 0xe5, а возвращать push rbp mov rbp, rsp и тд 





// создание asm файла 
void createDisAsmFile(const char* asmCode);


#ifdef __cplusplus
}
#endif

#endif 