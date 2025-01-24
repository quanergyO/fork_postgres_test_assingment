#ifndef TYPES_STATDATA_STATDATA_H
#define TYPES_STATDATA_STATDATA_H

#include <stddef.h>

#include "Error.h"
#include "Result.h"

typedef struct StatData {
    long id;
    int count;
    float cost;
    unsigned int primary:1;
    unsigned int mode:3;
} StatData;

// public
Result_t LoadDump(const char* filepath, size_t *length);
Result_t StoreDump(const char* filepath, const StatData *data, size_t length);
void SortDump(StatData* data, size_t length);
Result_t JoinDump(const StatData* data1, size_t length1, const StatData* data2, size_t length2, size_t *resultLength);

// private
int CompareByCost(const void* left, const void* right); // В проде компаратор нужно унести в единицу трансляции, что бы изолировать от внешнего использования


#endif // TYPES_STATDATA_STATDATA_H