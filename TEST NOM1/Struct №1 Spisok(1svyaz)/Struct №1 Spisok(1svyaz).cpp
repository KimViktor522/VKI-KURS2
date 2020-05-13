#include <iostream>
#include <cstdio>

using namespace std;

template<typename T>
class List {
public:
	class Node {
	public:
		T value{};
		Node* next;
	};
private:
	//число справа
	Node* front{ nullptr };
	int listsize{};
public:
	~List() {
		clear();
	}
	//вставка числа вправо
	Node* push_front(T data) { 
		Node* current = new Node;
		current->value = data;
		current->next = front;
		front = current;
		++listsize;
		return current;
	}
	//вставка числа вслево
	Node* push_back(T data) {
		Node* current{ front };
		while (current->next != nullptr) current = current->next;
		current->value = data;
		current->next = front;
		++listsize;
		return current;
	}
	//вставка в упорядоченую последовательность
	Node* inst_in_list(T data) {
		if (!listsize) return nullptr;
		Node* current{ front };
		if (data < current->value) push_back(data);
		else while (current->next != nullptr) {
			if ((current->value < data) && (current->next->value >= data)) {
				Node* currentNew = new Node;
				currentNew->value = data;
				currentNew->next = current->next;
				current->next = currentNew;
				return current;
			}
			current = current->next;
		}
	}
	//удаление всего 
	void clear() { 
		if (!listsize) return;
		Node* current{ front };
		Node* currentDel{ nullptr };
		while (current->next != nullptr){
			currentDel = current->next;
			delete current;	
			current = currentDel;
		}	
		front = nullptr;
		listsize = 0;
	}
	//вывод
	void print() {
		if (!listsize) return;
		for (Node* current{ front }; current != nullptr; current = current->next) {
			cout << current->value << "  ";
		}
		cout << "\n";
	}
};

int main() {
	system("chcp 1251"); system("cls");
	List<int> list;
	list.push_front(7);
	list.push_front(5);
	list.push_front(4);
	list.push_front(2);
	list.push_front(1);
	list.print();
	list.inst_in_list(3);
	list.inst_in_list(6);
	list.print();
	system("pause");
	return 0;
}