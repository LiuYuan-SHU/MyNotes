#include"Node.h"
#include"Node.cpp"
#include"DoubleCircularLinkedList.h"
#include"DoubleCircularLinkedList.cpp"
#include"DoubleLinkedList.h"
#include"DoubleLinkedList.cpp"
#include<iostream>

using namespace std;

typedef void (*tests)();

void test_node()
{
	cout << "----------------------" << __func__ << "--------------------------\n";

	//variable constructor
	Node<string> node("hello");
	node.printNode();

	//copy constructor
	Node<string> node1(node);
	Node<string> node2;
	node1.printNode();

	//getter and setter
	node2.set_data("hello");
	node2.printNode();

	node1.set_next(&node);
	node1.set_pre(&node);
	node1.printNode();
	cout << node1.get_data() << endl;
	cout << node1.get_pre() << endl;
	cout << node1.get_next() << endl << endl;

	//destructor
	node1.~Node();
	node1.printNode();

	cout << "---------------------------------------------------------\n\n";
}

void test_list()
{
#define SHOW list.printList()
	//constructor
	DoubleCircularLinkedList<int> list;
	SHOW;

	//CRUD
//head insert
	Node<int> node(10);
	list.insert_head(node);
	SHOW;

	list.insert_head(10);
	SHOW;

//tail insert
	list.insert_tail(30);
	SHOW;

//index insert
	list.insert_index(40, 2);
	SHOW;

//copy constructor
	cout << "list1" << endl;
	DoubleCircularLinkedList<int> list1 = list;
	list1.printList();

//delete_head
	list.delete_head();
	SHOW;

//delete_index
	list.delete_index(1);
	SHOW;

//delete_tail
	list.delete_tail();
	SHOW;

	list = list1;
	SHOW;
#if TEST_PAST
//delete_ele
	list.delete_ele(10);
#endif
//get_index
	cout << "-----test get_index()-----" << endl;
	cout << list.get_index(10) << endl;

//get_ele
	cout << "-----test get_ele()-----" << endl;
	cout << list.get_ele(0) << endl;

//operator[]
	cout << "-----test operator[]-----" << endl;
	cout << list[2] << endl;

	cout << endl << "�˳����򣬳����������Ϊtest_list�����һ������" << endl;
	exit(__LINE__);
}

void test_list1()
{
	DoubleLinkedList<int> list;
	list.insert_head(123);
	list.show_list();

	list.insert_head(1);
	list.insert_tail(321);
	list.show_list();

	list.delete_head();
	list.show_list();
	list.delete_tail();
	list.show_list();
	list.delete_head();
	list.show_list();
	list.delete_head();
}

void callback_test()
{
	char key = '0';

	tests funcs[] = { test_node, test_list, test_list1};
	int length = sizeof(funcs) / sizeof(void*);

	cout << "PLEASE CHOOSE A TEST( INPUT 0 TO EIXT ):" << endl;
	cout << "+---------------------+" << endl;
	cout << "| 1 |  test_node      |" << endl;
	cout << "+---------------------+" << endl;
	cout << "| 2 |  test_list      |" << endl;
	cout << "+---------------------+" << endl;
	cout << "| 3 |  test_1         |" << endl;
	cout << "+---------------------+" << endl;

	while (!(cin >> key) || key > length + '0' || key < '0')
	{
		cin.clear(); 
		cin.ignore(1024, '\n');
		cout << "Please re-input: ";
	}
	if (key == '0')
	{
		exit(0);
	}
	else
	{
		funcs[key - '0' - 1]();
	}
}

int main()
{
	if (!TEST_PAST)
	{
		cout << "+-------------------------------WARNING-------------------------------+" << endl;
		cout << "| ����˫��ѭ��������DoubleCircularLinkedList.cpp/.h���е������������� |" << endl;
		cout << "| ��δ�����bug���ᵼ�³�������������������������ʱ����������       |" << endl;
		cout << "| ------------- ���ȵ��� test_node()���ٵ��� test_list() ------------ |" << endl;
		cout << "+---------------------------------------------------------------------+" << endl << endl;
	}
	while (true)
	{
		callback_test();
	}
	
	
	return 0;
}

int main1()
{
	test_list1();
}
