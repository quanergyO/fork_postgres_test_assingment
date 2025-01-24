#ifndef TYPES_STATDATA_ERROR_H
#define TYPES_STATDATA_ERROR_H

#include <stddef.h>

typedef enum ErrorEnum {
    OK,
    ErrorOpenFile,
    ErrorWriteInFile,
    ErrorReadFile,
    ErrorFileSize,
    ErrorAllocateMemory,
    ErrorReallocateMemory,
    Undefined
} ErrorEnum;

typedef struct Error_t {
    const char* errorStr_;
    ErrorEnum errorEnum_;
} Error_t;

Error_t MakeError(ErrorEnum err);


#endif // TYPES_STATDATA_ERROR_H