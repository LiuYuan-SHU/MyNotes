#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include"Node.h"
#include"illegalIndex.h"

template<class T>
class DoubleLinkedList
{
private:
    Node<T>* _head;
    int _size;
public:
#define HEAD this->_head
    DoubleLinkedList();
    DoubleLinkedList(int size);
    DoubleLinkedList(const DoubleLinkedList<T>& list);
    ~DoubleLinkedList();

    void insert_head(T data);
    void insert_tail(T data);
    
    void delete_head();
    void delete_tail();

    int get_index(T data);
    T get_elem(int index);

    void show_list();
};

#endif // !DOUBLE_LINKED_LIST_H