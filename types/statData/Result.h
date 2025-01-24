#ifndef TYPES_STATDATA_RESULT_H
#define TYPES_STATDATA_RESULT_H

#include "Error.h"

typedef struct StatData StatData;

// Понимаю про over engeneering, но создано под расширение библиотеки StatData
typedef struct StatDataResult {
    StatData* result;
    Error_t error;
} StatDataResult;

typedef struct ErrorResult {
    Error_t error;
} ErrorResult;

typedef union Result_t {
    StatDataResult res1;
    ErrorResult res2;
} Result_t;


Result_t MakeResult1(StatData* statData, Error_t error);
Result_t MakeResult2(Error_t error);



#endif // TYPES_STATDATA_RESULT_H