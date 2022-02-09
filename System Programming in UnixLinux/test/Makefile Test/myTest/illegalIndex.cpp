#include "illegalIndex.h"

const char* illegalIndex::what()
{
    return errorInfo.c_str();
}
