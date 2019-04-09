#include "List.h"


ListNode* ListNode::FoundPtr(ListNode *l, int index) {
	for (int i = 0; i < index; i++) {
		l = l->next;
	}
	return l;
}

int ListNode::FoundInd(ListNode *l, ListNode *found) {
	int res_index = 0;
	while (l != found) {
		l = l->next;
		res_index++;
	}
	return res_index;
}

ListNode* ListNode::push(ListNode *head, ListNode *l, std::string s, int randIndex) {
	//Создаем новый элемент
	ListNode *new_l = new ListNode[1];
	new_l->data = s;
	new_l->prev = l;
	new_l->next = NULL;
	//Первый параметр (FoundPtr) функции должен быть головой списка, чтобы была возможность найти любой элемент
	new_l->rand = ListNode::FoundPtr(head, randIndex);
	return new_l;
}

List::List(ListNode *head, ListNode* tail, int count) {
	this->head = head;
	this->tail = tail;
	this->count = count;
}

List::~List() {
	//Проходимся с хвоста и удалем весь список
	for (int i = 0; i < this->count; i++) {
		ListNode *l = this->tail->prev;
		delete[] this->tail;
		this->tail = l;
	}
	this->count = 0;
}

void List::Print() {
	ListNode *l = this->head;
	for (int i = 0; i < this->count; i++) {
		std::cout << "Print: " << l->data << " " << l->rand->data << std::endl;
		l = l->next;
	}
	std::cout << "________________________" << std::endl;
}

//Записываем в файл только необходимые параметры: длинну списка(count), будет идти первой в файле
//												  индекс (ind) рандомного элемента списка 
//                                                рамзер (leng) строки data элемента списка
//                                                строку(list->data) элемента списка
void List::Serialize(FILE * file) {// сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	//Указатель для прохода по списку
	ListNode *l = this->head;
	//Записываем переменную длинны списка в файл
	fwrite(&(this->count), sizeof(int), 1, file);

	int leng;//Используем эту переменную для того, чтобы хранить размер data

	//Проходим по списку и записываем его в файл
	for (int i = 0; i < this->count; i++) {
		//Находим по указателю rand номер элемента в списке и записываем в файл
		int ind = ListNode::FoundInd(this->head, l->rand);
		fwrite(&ind, sizeof(int), 1, file);

		//Высчитываем размер data и записываем его в файл
		leng = (l->data).size();
		fwrite(&leng, sizeof(int), 1, file);

		//Записываем data в виде С строки, то есть строки с нулевым символом, поэтому leng+1
		fwrite((l->data).c_str(), sizeof(char), leng + 1, file);
		l = l->next;
	}
	fclose(file);
}

void List::Deserialize(FILE * file) { // загрузка из файла (файл открыт с помощью fopen(path, "rb"))
	ListNode *l = new ListNode[1];//Указатель для пробежки по списку
	ListNode *head = l;//Голова списка
	l->prev = nullptr;
	l->next = nullptr;

	int count;//Записываем длинну списка из файлп
	fread(&count, sizeof(int), 1, file);

	for (int i = 0; i < count; i++) {
		int leng;//Тут храним длинну data, чтобы можно было её безошибочно считать
		int rand_index;//Тут храним индекс рандомного элемента

		fread(&rand_index, sizeof(int), 1, file);

		fread(&leng, sizeof(int), 1, file);

		//Храним промежуточное значение data
		char *data = new char[leng + 1];
		fread(data, sizeof(char), leng + 1, file);

		if (i > 0) {
			l->next = ListNode::push(head, l, std::string(data), rand_index);
			l = l->next;
		}
		else {
			l->data = std::string(data);
			l->rand = l;
		}
		//Удаляем промежуточное значение	
		delete[] data;
	}
	fclose(file);
	//Инициализируем параметры
	this->head = head;
	this->tail = tail;
	this->count = count;
}
