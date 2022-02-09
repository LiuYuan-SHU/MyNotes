#include"DoubleLinkedList.h"

template<class T>
DoubleLinkedList<T>::DoubleLinkedList():_head(nullptr),_size(0)
{}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(int size)
{
    if(size < 0)
    {
        std::cout<<"illegal size"<<std::endl;
        return;
    }

    this->_size = size;
    for(int i = 0;i<size;i++)
    {
        this->insert_tail(0);
    }
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& list)
{
    if(&list == this)
    {
        return;
    }

    if(HEAD != nullptr || this->_size != 0)
    {
        this->~DoubleLinkedList();
    }

    this->_size = list._size;
    Node<T>* traversal = list._head;
    while(traversal != nullptr)
    {
        this->insert_head(traversal->get_data());
    }
}

template<class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    if(HEAD == nullptr || this->_size == 0)
    {
        return;
    }

    Node<T>* traversal = HEAD;
    Node<T>* next;
    while(traversal != nullptr)
    {
        next = traversal->get_next();
        delete traversal;
        traversal = next;
    }

    HEAD = nullptr;
    this->_size = 0;
}

template<class T>
void DoubleLinkedList<T>::insert_head(T data)
{
    Node<T>* temp = new Node<T>;
    temp->set_data(data);

    if(this->_size == 0 || HEAD == nullptr)
    {
        HEAD = temp;
        this->_size = 1;
        return;
    }

    temp->set_next(HEAD);
    HEAD->set_pre(temp);
    HEAD = temp;
    this->_size++;
}

template<class T>
void DoubleLinkedList<T>::insert_tail(T data)
{
    Node<T>* temp = new Node<T>;
    temp->set_data(data);

    if(HEAD == nullptr || this->_size == 0)
    {
        HEAD = temp;
        this->_size = 1;
        return;
    }

    Node<T>* traversal = HEAD;
    while(traversal->get_next() != nullptr)
    {
        traversal = traversal->get_next();
    }

    traversal->set_next(temp);
    temp->set_pre(traversal);
    this->_size++;
    return;
}

template<class T>
void DoubleLinkedList<T>::delete_head()
{
    if(HEAD==nullptr || this->_size == 0)
    {
        std::cout<<"The list is empty,delete failed"<<std::endl;
        return;
    }

    Node<T>* temp = HEAD;
    HEAD = HEAD->get_next();
    if(HEAD != nullptr)
    {
        HEAD->set_pre(nullptr);
    }
    this->_size--;
    delete temp;
}

template<class T>
void DoubleLinkedList<T>::delete_tail()
{
    if(HEAD==nullptr || this->_size == 0)
    {
        std::cout<<"The list is empty,delete failed"<<std::endl;
        return;
    }

    Node<T>* traversal = HEAD;
    while(traversal->get_next() != nullptr)
    {
        traversal = traversal->get_next();
    }

    if(traversal->get_pre() != nullptr)
    {
        traversal->get_pre()->set_next(nullptr);
    }
    
    delete traversal;
    this->_size--;
}

template<class T>
int DoubleLinkedList<T>::get_index(T data)
{
    if(HEAD==nullptr || this->_size == 0)
    {
        std::cout<<"The list is empty,delete failed"<<std::endl;
        return -1;
    }

    int index = 0;
    Node<T>* traversal = HEAD;
    while(traversal != nullptr)
    {
        if(traversal->get_data() == data)
        {
            return index;
        }
        traversal = traversal->get_next();
        index++;
    }

    return -1;
}

template<class T>
T DoubleLinkedList<T>::get_elem(int index)
{
    if(HEAD==nullptr || this->_size == 0)
    {
        std::cout<<"The list is empty"<<std::endl;
        return;
    }

    if(index >= this->_size || index < 0)
    {
        throw(illegalIndex(index));
    }

    int i = 0;
    Node<T>* traversal = HEAD;
    while(traversal != nullptr)
    {
        if(i == index)
        {
            return traversal->get_data();
        }
        i++;
    }

    std::cout<<"Search failed"<<std::endl;

    return T(0);
}

template<class T>
void DoubleLinkedList<T>::show_list()
{
	std::cout << "+--------------DOUBLE LINKED LIST---------------+" << std::endl;
	std::cout << "| List Head: " << this->_head << "\t\t\t|" << std::endl;
	std::cout << "| List Size: " << this->_size << "\t\t\t\t\t|" << std::endl;
	std::cout << "|-----------------------------------------------|" << std::endl;
	int i = 0;
	for (Node<T>* traversal = HEAD; i < this->_size; i++, traversal = traversal->get_next())
	{
		std::cout << "| \t |" << " \tDATA: " << traversal->get_data() << "(" << traversal->get_dataP() << ")\t|" << std::endl;
		std::cout << "| Node " << (i + 1) << " |" << "\tPre: " << traversal->get_pre() << "\t\t\t\t| " << std::endl;
		std::cout << "| \t |\tNext: " << traversal->get_next() << "\t\t\t\t|" << std::endl;
		std::cout << "| \t |\tADDRESS: " << traversal << "\t\t|" << std::endl;
		if (i != this->_size - 1)
		{
			std::cout << "|-----------------------------------------------|" << std::endl;
		}
	}
	std::cout << "+-----------------------------------------------+" << std::endl << std::endl << std::endl;
}