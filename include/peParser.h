#ifndef PeParser_H
#define PeParser_H

#include <stdint.h>
#include <sys/types.h>
#include <basetsd.h>

typedef struct {
    uint32_t virtualAddress;
    uint32_t size;
    uint8_t* rawData;
} SectionInfo;

SectionInfo* extractTextSection(const char* filePath);

#endif 