#ifndef UTILS_H
#define UTILS_H


#include <basetsd.h> // для size_t


// ======== структуры ========

// пока нету


// ======== обьявление функций ========

size_t calculateSize(const char* file_path); // вычисление размера файла 
    
char* readBinaryFile(const char* file_path, size_t* file_size); // чтение бинарного файла 
    
void createDisAsmFile(const char* asmCode); // создания дизассемблированного файла 

// readBinaryFile должна возвращать чтото типо такого: FFA1, тоесть двоичный код в шестнадцатеричном формате


#endif 
