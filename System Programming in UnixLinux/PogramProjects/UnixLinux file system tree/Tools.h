#ifndef TOOLS_H
#define TOOLS_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"NODE.h"

struct NODE* root;              //record the root dict
struct NODE* cwd;               //record current work dict
char line[128];                 //user input command line
char command[16],pathname[64];  //command and pathname strings
char dname[64],bname[64];       //dirname and basename string holders
//commands
const static char* cmd[] = {"mkdir","rmdir","ls","cd","pwd","creat","rm","reload","save","menu","quit",NULL};
int cmdIndex;

//initialize the system
void init();
//get command from the terminal
void getLine();
//split the pathname, return how many node is in the pathname
int splitPath(char* pathname);
//print root, command, pathname
void test();
//judge the legalty of the command and identify the command
int findCmd(char* command);
//judge the legalty of the pathname
int findPath(char* pathname);

#endif // !TOOLS_H