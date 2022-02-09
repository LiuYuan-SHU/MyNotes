#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Tools.h"
#include"NODE.h"

void init()
{
    //initialize root node
    root = (struct NODE *)malloc(sizeof(struct NODE));
    strcmp(root->name,"root");
    root->type = 'D';                   //set the type of root node as D
    root->parentPtr = NULL;
    root->siblingPtr = NULL;
    root->childPtr = NULL;
    
    //initialize cwd
    cwd = root;                         //set cwd as root

    //initialize dname and bname
    strcmp(dname,"/");
    strcmp(bname,"/");
}

void getLine()
{
    printf("Input command: ");
    fgets(line,128,stdin);      //get line from stdin
    line[strlen(line) - 1] = 0; //protection
    if(sscanf(line,"%s %s",command,pathname) != 2)
    {
        strcpy(pathname,"");
    }
    fflush(stdin);
    /*
    while(sscanf(line,"%s %s",command,pathname) != 2)  //split the command
    {
        if(!strcmp(command,"cd") || !strcmp(command,"ls"))
        {
            strcpy(pathname,"");
            return;
        }
        printf("----------ILLEGAL INPUT----------\n");
        printf("Input command: ");
        fgets(line,128,stdin);      //get line from stdin
        line[strlen(line) - 1] = 0; //protection
        fflush(stdin);              //flush the stdin
    }
    */
}

void test()
{
    printf("----------TEST----------\n");
    printf("root:\t%p\n",root);
    printf("command:%s\n",command);
    printf("pathname:%s\n",pathname);
    printf("------------------------\n");
}

int findCmd(char* command)
{
    
    int i = 0;
    while(cmd[i])
    {
        if(!strcmp(command,cmd[i]))
        {
            return i;
        }
        i++;
    }
    return -1;
}

int findPath(char* pathname)
{
    
}