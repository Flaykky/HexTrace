#include "disAssembler.h"
#include <iostream>
#include <string>
#include <utils.c>
#include "utils.h"



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
