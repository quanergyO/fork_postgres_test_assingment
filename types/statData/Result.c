#include "Result.h"


Result_t MakeResult1(StatData* statData, Error_t error) {
    StatDataResult res_p = { .result = statData, .error = error };
    Result_t result;
    result.res1 = res_p;

    return result;
}

Result_t MakeResult2(Error_t error) {
    ErrorResult res_p = { .error = error };
    Result_t result;
    result.res2 = res_p;

    return result;
}