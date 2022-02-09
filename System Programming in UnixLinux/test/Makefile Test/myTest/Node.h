#ifndef NODE_H
#define NODE_H

#include<iostream>

template<class T>
class Node
{
private:
    T* _data;           //data filed
    Node<T>* _pPre;        //pointer points the previous node, if singly linked list, it is always nullptr
    Node<T>* _pNext;       //pointer points the next node
public:
    //non-args constructor,set data filed as 0
    Node();
    //constructor with args,copy data, set pointers as nullptr
    Node(T data); 
    //deep-copy constructor,copy data, set pointers as nullptr
    Node(const Node& node);
    //destructor, free heap storage, set data filds as 0
    ~Node();

//------------------------------Getter and Setter------------------------------
    T& get_data() const;
    T* get_dataP() const { return this->_data; }
    Node<T>* get_pre() const { return this->_pPre; }
    Node<T>* get_next() const { return this->_pNext; }

    void set_data(T data);
    void set_pre(Node<T>* node) { this->_pPre = node; }
    void set_next(Node<T>* node) { this->_pNext = node; }

//show
    void printNode();

    //return the data of node
    operator T() const;
};

#endif // !NODE_H