#include"Node.h"
#include<iostream>

template<class T>
Node<T>::Node():_data(nullptr),_pPre(nullptr),_pNext(nullptr)
{
}

template<class T>
Node<T>::Node(T data):_pPre(nullptr),_pNext(nullptr)
{
    this->_data = new T;
    *(this->_data) = data;
}

template<class T>
Node<T>::Node(const Node<T>& node)
{
    this->_data = new T;
    *this->_data = *(node._data);
    this->_pNext = nullptr;
    this->_pPre = nullptr;
}

template<class T>
Node<T>::~Node()
{
    if (this->_data != nullptr)
    {
        delete this->_data;
        this->_data = nullptr;
    }
    this->_pPre = nullptr;
    this->_pNext = nullptr;
}

template<class T>
T& Node<T>::get_data() const
{
    if (this->_data == nullptr)
    {
        std::cout << "NODE HAS NO DATA" << std::endl;
        exit(-1);
    }
    return *this->_data;
}

template<class T>
void Node<T>::set_data(T data)
{
    if (this->_data != nullptr)
    {
        delete this->_data;
    }
    this->_data = new T;
    *this->_data = data;
}

template<class T>
void Node<T>::printNode()

{
    std::cout << "------------------NODE-----------------" << std::endl;
    if (this->_data != nullptr)
    {
        std::cout << "DATA: " << *this->_data << std::endl;
    }
    else
    {
        std::cout << "DATA: NULL" << std::endl;
    }
    std::cout << "PREV: " << this->_pPre << std::endl;
    std::cout << "NEXT: " << this->_pNext << std::endl;
    std::cout << "---------------------------------------" << std::endl << std::endl;
}

template<class T>
Node<T>::operator T() const
{
    return *(this->_data);
}