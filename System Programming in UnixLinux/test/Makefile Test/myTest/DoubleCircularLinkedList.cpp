#include"DoubleCircularLinkedList.h"

template<class T>
DoubleCircularLinkedList<T>::DoubleCircularLinkedList()
{
	this->_head = nullptr;
	this->_size = 0;
}

template<class T>
DoubleCircularLinkedList<T>::DoubleCircularLinkedList(const DoubleCircularLinkedList<T>& other)
{
	if (&other == this)
	{
		return;
	}

	if (HEAD != nullptr && this->_size != 0)
	{
		this->~DoubleCircularLinkedList();
	}

	int i = 0;
	for (Node<T>* traversal = other._head; i < other._size; i++, traversal = traversal->get_next())
	{
		this->insert_tail(*traversal);
	}
}

template<class T>
DoubleCircularLinkedList<T>::~DoubleCircularLinkedList()
{
	if (HEAD == nullptr || this->_size == 0)
	{
		HEAD = nullptr;
		this->_size = 0;
		return;
	}

	if (this->_size == 1)
	{
		delete_head();
		HEAD = nullptr;
		return;
	}

	int i = 0;
	Node<T>* temp;
	for (Node<T>* traversal = HEAD; i < this->_size; i++)
	{
		temp = traversal;
		traversal = traversal->get_next();
		delete temp;
	}
	HEAD = nullptr;
	this->_size = 0;
}

template<class T>
void DoubleCircularLinkedList<T>::insert_head(T data)
{
	//创建新的节点，将数据存入其中，插入节点
	Node<T>* temp = new Node<T>;
	temp->set_data(data);

	//insert node
	if (HEAD == nullptr)
	{
		HEAD = temp;
		HEAD->set_next(HEAD);
		HEAD->set_pre(HEAD);
	}
	else
	{
		temp->set_next(HEAD);
		temp->set_pre(TAIL);

		TAIL->set_next(temp);
		HEAD->set_pre(temp);

		HEAD = temp;
	}

	this->_size++;
}

template<class T>
void DoubleCircularLinkedList<T>::insert_head(Node<T>& data)
{
	if (data.get_dataP() == nullptr)
	{
		std::cout << "EMPTY NODE, INSERTION FIALS" << std::endl;
		return;
	}

	//insert node
	if (HEAD == nullptr)
	{
		HEAD = &data;
		HEAD->set_next(HEAD);
		HEAD->set_pre(HEAD);
	}
	else
	{
		data.set_next(HEAD);
		data.set_pre(TAIL);

		TAIL->set_next(&data);
		HEAD->set_pre(&data);

		HEAD = &data;
	}

	this->_size++;
}

template<class T>
void DoubleCircularLinkedList<T>::insert_tail(T data)
{
	Node<T>* temp = new Node<T>;
	temp->set_data(data);

	if (HEAD == nullptr)
	{
		HEAD = temp;
		HEAD->set_next(HEAD);
		HEAD->set_pre(HEAD);
	}
	else
	{
		temp->set_next(HEAD);
		temp->set_pre(TAIL);

		TAIL->set_next(temp);
		HEAD->set_pre(temp);
	}
	this->_size++;
}

template<class T>
void DoubleCircularLinkedList<T>::insert_index(T data, int index)
{
	Node<T>* traversal = this->elementAtIndex(index);
	Node<T>* temp = new Node<T>;
	temp->set_data(data);
	temp->set_pre(traversal->get_pre());
	temp->set_next(traversal);

	traversal->get_pre()->set_next(temp);
	traversal->set_pre(temp);

	this->_size++;
#if 0
	if (!this->index(index))
	{
		throw(illegalIndex(index));
	}

	Node<T>* traversal = HEAD;
	for (int i = 0; i < index; i++)
	{
		traversal = traversal->get_next();
	}

	Node<T>* temp = new Node<T>;
	temp->set_data(data);
	temp->set_next(traversal->get_next());
	temp->set_pre(traversal);

	traversal->get_next()->set_pre(temp);
	traversal->set_next(temp);

	this->_size++;
#endif
}

template<class T>
void DoubleCircularLinkedList<T>::delete_head()
{
	if (empty())
	{
		std::cout << "the list is empty" << std::endl;
		return;
	}

	if (this->_size == 1)
	{
		delete HEAD;
		this->_size--;
		return;
	}

	Node<T>* newHead = HEAD->get_next();
	TAIL->set_next(newHead);
	newHead->set_pre(TAIL);
	delete HEAD;
	HEAD = newHead;

	this->_size--;
}

template<class T>
void DoubleCircularLinkedList<T>::delete_index(int index)
{
	if (empty())
	{
		std::cout << "the list is empty" << std::endl;
		return;
	}

	if (index == 0)
	{
		delete_head();
		return;
	}
	else if (index == this->_size - 1)
	{
		delete_tail();
		return;
	}


	Node<T>* traversal = elementAtIndex(index);
	traversal->get_pre()->set_next(traversal->get_next());
	traversal->get_next()->set_pre(traversal->get_pre());

	delete traversal;
	this->_size--;
}

template<class T>
void DoubleCircularLinkedList<T>::delete_tail()
{
	if (empty())
	{
		std::cout << "the list is empty" << std::endl;
		return;
	}

	if (this->_size == 1)
	{
		delete_head();
		return;
	}

	Node<T>* temp = TAIL;
	TAIL->get_pre()->set_next(HEAD);
	HEAD->set_pre(TAIL->get_pre());
	delete temp;
	this->_size--;
}

//delete_indexa
#if TEST_PAST
template<class T>
void DoubleCircularLinkedList<T>::delete_ele(T data)
{
	int* indexes = new int[this->_size];	//存放要删除的元素的下标
	int num = 0;							//indexes的大小

	//记录下标
	int i = 0;
	for (Node<T>* p = HEAD; i < this->_size; p = p->get_next(), i++)
	{
		if (p->get_data() == data)
		{
			indexes[num++] = i;
		}
	}

	//std::cout << indexes << std::endl;
	//std::cout << num << std::endl;
	////debug
	//for (int j = 0; j < num; j++)
	//{
	//	std::cout << indexes[j] << '\t';
	//}
	//std::cout << std::endl;

	//删除元素
	int offset = 0;	//删除一个元素之后，下标对应减一，需要记录
	for (int i = 0; i < num; i++)
	{
		std::cout << "indexes[i] = " << indexes[i] << std::endl;
		std::cout << "offset = " << offset << std::endl;
		std::cout << "delete index " << (indexes[i] - offset) << std::endl;
		delete_index(indexes[i] - offset);
		offset++;
		printList();
	}
}
#endif

template<class T>
int DoubleCircularLinkedList<T>::get_index(T search)
{
	int index = 0;
	Node<T>* traversal = HEAD;
	for (index = 0; index < this->_size; index++, traversal = traversal->get_next())
	{
		if (traversal->get_data() == search)
		{
			return index;
		}
	}
	std::cout << "no such element" << std::endl;
	return -1;
}

template<class T>
T& DoubleCircularLinkedList<T>::get_ele(int index)
{
	return elementAtIndex(index)->get_data();
}

template<class T>
bool DoubleCircularLinkedList<T>::index(int index)
{
	if (index < 0 || index >= this->_size)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}

template<class T>
Node<T>* DoubleCircularLinkedList<T>::elementAtIndex(int index)
{
	if (!this->index(index))
	{
		throw(illegalIndex(index));
	}

	Node<T>* traversal = HEAD;
	for (int i = 0; i < index; i++)
	{
		traversal = traversal->get_next();
	}
	return traversal;
}

template<class T>
T& DoubleCircularLinkedList<T>::operator[](int index)
{
	return get_ele(index);
}

template<class T>
void DoubleCircularLinkedList<T>::printList()
{
	std::cout << "+---------DOUBLE CIRCULAR LINKED LIST-----------+" << std::endl;
	std::cout << "| List Head: " << this->_head << "\t\t\t\t|" << std::endl;
	std::cout << "| List Size: " << this->_size << "\t\t\t\t\t|" << std::endl;
	std::cout << "|-----------------------------------------------|" << std::endl;
	int i = 0;
	for (Node<T>* traversal = HEAD; i < this->_size; i++, traversal = traversal->get_next())
	{
		std::cout << "| \t |" << " \tDATA: " << traversal->get_data() << "(" << traversal->get_dataP() << ")\t\t|" << std::endl;
		std::cout << "| Node " << (i + 1) << " |" << "\tPre: " << traversal->get_pre() << "\t\t\t| " << std::endl;
		std::cout << "| \t |\tNext: " << traversal->get_next() << "\t\t\t|" << std::endl;
		std::cout << "| \t |\tADDRESS: " << traversal << "\t\t|" << std::endl;
		if (i != this->_size - 1)
		{
			std::cout << "|-----------------------------------------------|" << std::endl;
		}
	}
	std::cout << "+-----------------------------------------------+" << std::endl << std::endl << std::endl;
}