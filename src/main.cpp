#include "disAssembler.h"
#include <iostream>
#include <string>



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




int main() {


    size_t file_size;
    std::string file_path;

    std::cout << "enter the path to binary file: ";
    std::cin >> file_path;

    file_size = calculateSize(file_path.c_str());

    char* binaryCode = readBinaryFile(file_path.c_str(), &file_size);

    if (!binaryCode) {
        return 1;
    }

    char* asmCode = disAssembler(binaryCode, file_size, 0x0);

    if (!asmCode) {
        free(binaryCode);
        return 1;
    }

    createDisAsmFile(asmCode);


    return 0;
}