#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"NODE.h"
#include"Tools.h"

int main()
{
    init();
    while(1)
    {
        getLine();  //get the line from keyboard
        //check the legalty of command and find the index of the command
        if((cmdIndex = findCmd(command)) == -1)
        {
            printf("no such command: %s\n",command);
            continue;
        }
        //check the legalty of pathname
        if(findPath(pathname) == 0)
        {
            printf("illegal pathnmae: %s\n",pathname);
            continue;
        }
        test();
        
    }

    return 0;
}