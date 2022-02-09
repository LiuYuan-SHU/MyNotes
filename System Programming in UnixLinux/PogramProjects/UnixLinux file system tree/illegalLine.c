#include"illegalLine.h"
#include<stdio.h>
#include<string.h>

void illegalLine_constructor(illegalLine const * except, const char* info)
{
    strcpy(except->errorInfo,info);
}

const char* what(const illegalLine const * except)
{
    return (const char*)except->errorInfo;
}