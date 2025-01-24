#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StatData.h"


Result_t StoreDump(const char* filepath, const StatData *data, size_t length)
{
    FILE *file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return MakeResult2(MakeError(ErrorOpenFile));
    }

    if (fwrite(data, sizeof(StatData), length, file) != length) {
        perror("Failde to write data to file");
        fclose(file);
        return MakeResult2(MakeError(ErrorWriteInFile));
    }

    fclose(file);
    return MakeResult2(MakeError(OK));
}

Result_t LoadDump(const char* filepath, size_t *length) 
{
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file for reading");

        return MakeResult1(NULL, MakeError(ErrorOpenFile));
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    if (filesize % sizeof(StatData) != 0) {
        fprintf(stderr, "File size is not valid for StatData structure\n");
        fclose(file);

        return MakeResult1(NULL, MakeError(ErrorFileSize));
    }

    *length = filesize / sizeof(StatData);
    StatData* data = (StatData*)malloc(filesize);
    if (!data) {
        perror("Failed to allocate memory");
        fclose(file);

        return MakeResult1(NULL, MakeError(ErrorAllocateMemory));
    }

    if (fread(data, sizeof(StatData), *length, file) != *length) {
        perror("Failde to read data from file");
        free(data);
        fclose(file);

        return MakeResult1(NULL, MakeError(ErrorReadFile));
    }

    fclose(file);

    return MakeResult1(data, MakeError(OK));
}


void SortDump(StatData* data, size_t length) {
    qsort(data, length, sizeof(StatData), CompareByCost);
}

Result_t JoinDump(const StatData *data1, size_t length1, const StatData *data2, size_t length2, size_t *resultLength) {
    size_t maxSize = length1 + length2;
    StatData *result = malloc(maxSize * sizeof(StatData));
    if (!result) {
        perror("Failed to allocate memory for JoinDump");
        
        return MakeResult1(NULL, MakeError(ErrorAllocateMemory));
    }

    // TODO неоптимальный алгоритм за O((m + k)^2) Можно за O(m+k)
    size_t index = 0;
    for (size_t i = 0; i < length1; i++) {
        result[index++] = data1[i];
    }
    for (size_t i = 0; i < length2; i++) {
        result[index++] = data2[i];
    }

    for (size_t i = 0; i < index; i++) {
        for (size_t j = i + 1; j < index; ) {
            if (result[i].id == result[j].id) {
                result[i].count += result[j].count;
                result[i].cost += result[j].cost;
                result[i].primary &= result[j].primary;
                result[i].mode = (result[i].mode > result[j].mode) ? result[i].mode : result[j].mode;

                for (size_t k = j; k < index - 1; k++) {
                    result[k] = result[k + 1];
                }
                index--;
            } else {
                j++;
            }
        }
    }

    *resultLength = index;
    StatData *temp = realloc(result, index * sizeof(StatData));
    if (!temp) {
        perror("Failed to reallocate memory for JoinDump");
        free(result);
        return MakeResult1(NULL, MakeError(ErrorReallocateMemory));
    }
    result = temp;

    return MakeResult1(result, MakeError(OK));
}


int CompareByCost(const void* left, const void* right) {
 const StatData *dataA = (const StatData*)left;
    const StatData *dataB = (const StatData*)right;
    
    if (dataA->cost < dataB->cost) return -1;
    if (dataA->cost > dataB->cost) return 1;
    return 0;
}