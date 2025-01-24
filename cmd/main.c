#include <stdio.h>
#include <stdlib.h>
#include "../types/statData/StatData.h"

void ProcessFiles(const char *inputFile1, const char *inputFile2, const char *outputFile);
void HandleErrorResult1(Result_t res);
void HandleErrorResult2(Result_t res);

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <inputFile1> <inputFile2> <outputFile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    ProcessFiles(argv[1], argv[2], argv[3]);

    return EXIT_SUCCESS;
}


void ProcessFiles(const char *inputFile1, const char *inputFile2, const char *outputFile) {
    size_t length1, length2, resultLength;

    Result_t res = LoadDump(inputFile1, &length1);
    HandleErrorResult1(res);
    StatData* data1 = res.res1.result;

    Result_t res2 = LoadDump(inputFile2, &length2);
    HandleErrorResult1(res2);
    StatData* data2 = res2.res1.result;

    Result_t res3 = JoinDump(data1, length1, data2, length2, &resultLength);
    HandleErrorResult1(res3);
    StatData* joinedData = res3.res1.result;

    SortDump(joinedData, resultLength);

    printf("First 10 records:\n");
    for (size_t i = 0; i < resultLength && i < 10; i++) {
        printf("ID: %lx, Count: %d, Cost: %.3e, Primary: %c, Mode: %03o\n",
               joinedData[i].id,
               joinedData[i].count,
               joinedData[i].cost,
               joinedData[i].primary ? 'y' : 'n',
               joinedData[i].mode);
    }

    Result_t res4 = StoreDump(outputFile, joinedData, resultLength);
    HandleErrorResult2(res4);

    free(data1);
    free(data2);
    free(joinedData);
}



void HandleErrorResult1(Result_t res)
{
    if (res.res1.error.errorEnum_ != OK) {
        fprintf(stderr, "%s", res.res1.error.errorStr_);
        exit(EXIT_FAILURE);
    }
}

void HandleErrorResult2(Result_t res)
{
    if (res.res2.error.errorEnum_ != OK) {
        fprintf(stderr, "%s", res.res2.error.errorStr_);
        exit(EXIT_FAILURE);
    }
}