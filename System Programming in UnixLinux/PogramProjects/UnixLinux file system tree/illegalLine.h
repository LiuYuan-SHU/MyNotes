#ifndef ILLEGAL_LINE_H
#define ILLEGAL_LINE_H

typedef struct
{
    char* errorInfo;
}illegalLine;

void illegalLine_constructor(illegalLine const * except,const char* info);
const char* what(const illegalLine const * except);


#endif // !IILEGAL_LINE_H