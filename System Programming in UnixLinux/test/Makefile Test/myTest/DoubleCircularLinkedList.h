#ifndef DOUBLE_CIRCULATION_LINKED_LIST_H
#define DOUBLE_CIRCULATION_LINKED_LIST_H

#define TEST_PAST false

#include"Node.h"
#include"illegalIndex.h"
#include<iostream>

template<class T>
class DoubleCircularLinkedList
{
private:
    Node<T> *_head;     //record head node
    int _size;          //record the size of the list
public:
#define HEAD this->_head
#define TAIL this->_head->get_pre()
    //non-args constructor, set data filds as 0
    DoubleCircularLinkedList();
    //deep-copy constructor
    DoubleCircularLinkedList(const DoubleCircularLinkedList<T>& other);
    //destructor,set data filds as 0
    ~DoubleCircularLinkedList();

//----------------------------------------CRUD----------------------------------------
    //insert a node before the head node
    void insert_head(T data);
    void insert_head(Node<T>& data);
    //insert a node after the tail node
    void insert_tail(T data);
    //insert a node at the specified index
    void insert_index(T data,int index);

    //delete the head node
    void delete_head();
    //delete a node at te specified index
    void delete_index(int index);
    //delete the tail node;
    void delete_tail();
#if TEST_PAST
    //delete a specified element in the list
    void delete_ele(T data);
#endif

    //search a specified element in the list,return the index of the first element found, if not found, return -1
    int get_index(T search);
    //return the element at the specified index
    T& get_ele(int index);

//----------------------------------------tool functions----------------------------------------
    //judge if the index is legal
    bool index(int index);
    
    //return if the list is empty
    bool empty() {return this->_size <= 0;}

    //return a pointer points the element at the index
    Node<T>* elementAtIndex(int index);

//----------------------------------------operators----------------------------------------
    //return the element at the specifid index
    T& operator[](int index);

//----------------------------------------SHOW----------------------------------------
    void printList();
};

#endif // !DOUBLE_CIRCULATION_LINKED_LIST_H