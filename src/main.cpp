#include "disAssembler.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {
    size_t file_size;
    std::string file_path;
    
    std::cout << "Enter binary file path: ";
    std::cin >> file_path;
    
    uint8_t* binary_data = readBinaryFile(file_path.c_str(), &file_size);
    if (!binary_data) {
        std::cerr << "Error reading file\n";
        return 1;
    }
    
    char* asm_code = disassemble(reinterpret_cast<const char*>(binary_data), file_size, 0x1000);
    if (!asm_code) {
        std::cerr << "Disassembly failed\n";
        free(binary_data);
        return 1;
    }
    
    createDisAsmFile(asm_code);
    
    free(binary_data);
    free(asm_code);
    return 0;
}
