#ifndef NODE_H
#define NODE_H

struct NODE
{
    char name[64];              //the name the dict/file
    char type;                  //D for dict, F for file
    struct NODE* childPtr;      //记录子结点地址
    struct NODE* siblingPtr;    //记录兄弟节点地址
    struct NODE* parentPtr;     //记录父节点地址
};
#endif // !NODE_H