#include <capstone/capstone.h>
#include "disAssembler.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char* disassemble(const uint8_t* binaryCode, size_t codeSize, uint64_t address) {
    csh handle;
    cs_insn* insn;
    
    if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
        fprintf(stderr, "Error initializing Capstone\n");
        return NULL;
    }
    
    size_t count = cs_disasm(handle, binaryCode, codeSize, address, 0, &insn);
    if (!count) {
        cs_close(&handle);
        return NULL;
    }
    
    size_t total_len = 0;
    for (size_t i = 0; i < count; i++) {
        total_len += strlen(insn[i].mnemonic) + strlen(insn[i].op_str) + 3;
    }
    
    char* result = (char*)malloc(total_len);
    if (!result) {
        cs_free(insn, count);
        cs_close(&handle);
        return NULL;
    }
    
    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        offset += sprintf(result + offset, "%s %s\n", 
                        insn[i].mnemonic, 
                        insn[i].op_str);
    }
    
    cs_free(insn, count);
    cs_close(&handle);
    return result;
}
