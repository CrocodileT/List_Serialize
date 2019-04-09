#pragma once
#include <string>
#include <iostream>


struct ListNode {
	//Функция ищет элемент по номеру элемента списка и возвращает искомый элемент
	static ListNode* FoundPtr(ListNode *, int);
	//Функция ищет элемент по указателю и возвращает его номер
	static int FoundInd(ListNode *, ListNode *);
	//Создает новый элемент в списке и возвращает указатель на него
    //Рандомный индекс списка (randIndex) задается вне функции, по нему находится элемент списка с этим индексом 
	static ListNode* push(ListNode *, ListNode *, std::string , int);

	ListNode * prev;
	ListNode * next;
	ListNode * rand; // указатель на произвольный элемент данного списка либо указатель на  NULL
	std::string data;
};

class List {
public:
	List(ListNode *, ListNode*, int);

	~List();

	void Print();

	void Serialize(FILE *);

	void Deserialize(FILE *);

private:
	ListNode * head;
	ListNode * tail;
	int count;
};
