#ifndef COMMANDS_H
#define COMMANDS_H

#include<stdio.h>

#define MKDIR   0
#define RMDIR   1
#define LS      2
#define CD      3
#define PWD     4
#define CREAT   5
#define RM      6
#define SAVE    7
#define RELOAD  8
#define MENU    9
#define QUIT    10

//函数指针，用于调用所有的函数
int (*cmdPtr[])(char*) = { mkdir , rmdir , ls , cd , pwd , creat , rm , save , reload , menu , quit }; 

//为给定的路径名创建一个新目录
int mkdir(char* pathname);
//如果目录为空，则删除该目录
int rmdir(char* pathname);
//列出路径名或当前工作目录的目录内容
int ls(char* pathname);
//将当前的工作目录更改为路径名，如果没有路径名则更改为"/"
int cd(char* pathname);
//打印当前工作目录的（绝对）路径名
int pwd(char* pathname);
//创建一个FILE节点
int creat(char* pathname);
//删除FILE节点
int rm(char* pathname);
//将当前文件系统树保存为文件
int save(char* filename = "FileSystemTree.txt");
//从一个文件构造一个文件系统树
int reload(char* filename = "FileSystemTree.txt");
//显示有效命令菜单
int menu(char * = NULL);
//保存文件系统树，然后终止程序
int quit(char* filename = "FileSystemTree.txt");

#endif // !COMMANDS_H