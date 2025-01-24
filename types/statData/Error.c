#include "Error.h"

const char* ErrorOpenFile_s = "Failed to open file for writing\n";
const char* ErrorWriteInFile_s = "Failde to write data to file\n";
const char* ErrorReadFile_s = "Failde to read data from file\n";
const char* ErrorFileSize_s = "File size is not valid for StatData structure\n";
const char* ErrorAllocateMemory_s = "Failed to allocate memory\n";
const char* ErrorReallocateMemory_s = "Failed to reallocate memory for JoinDump\n";
const char* Undefined_s = "Undefined Error\n";


Error_t MakeError(ErrorEnum err) {
    Error_t error;
    error.errorEnum_ = err;
    switch (err)
    {
        case OK: {
            error.errorStr_ = NULL;
            break;
        }
        case ErrorOpenFile: {
            error.errorStr_ = ErrorOpenFile_s;
            break;
        }
        case ErrorWriteInFile: {
            error.errorStr_ = ErrorWriteInFile_s;
            break;
        }
        case ErrorFileSize: {
            error.errorStr_ = ErrorFileSize_s;
            break;
        }
        case ErrorAllocateMemory: {
            error.errorStr_ = ErrorAllocateMemory_s;
            break;
        }
        case ErrorReallocateMemory: {
            error.errorStr_ = ErrorReallocateMemory_s;
            break;
        }
        default:
            error.errorStr_ = Undefined_s;
    }
    return error;
}