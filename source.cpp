#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>
#include "List.h"


//Список из строк aaa->bbb->ccc->ddd
int main() {
	int size = 1;

	ListNode *head = new ListNode[1];
	ListNode *tail;
	head->prev = nullptr;
	head->next = nullptr;
	head->data = "aaa";
	head->rand = head;
	srand(time(NULL));
	head->next = ListNode::push(head, head, "bbb", rand() % size++);
	head->next->next = ListNode::push(head, head->next, "ccc", rand() % size++);
	head->next->next->next = ListNode::push(head, head->next->next, "ddd", rand() % size++);

	tail = head->next->next->next;

	List list = List(head, tail, size);

	list.Print();
	FILE *in, *out;
	in = fopen("buf.txt", "wb");
	list.Serialize(in);
	out = fopen("buf.txt", "rb");
	list.Deserialize(out);
	list.Print();
	system("pause");
}
