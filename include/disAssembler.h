#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#ifdef __cplusplus
extern "C" {
#endif

char* disassemble(const char* binaryCode, size_t codeSize, uint64_t address);

#ifdef __cplusplus
}
#endif

#endif
