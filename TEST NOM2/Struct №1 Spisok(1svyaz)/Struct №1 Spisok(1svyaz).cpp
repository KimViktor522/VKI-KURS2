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
	//ищет ближайший элемент к данному
	T search_near_elem(T data) {
		if (!listsize) return T{};
		Node* current{ front };
		if (data < current->value) return current->value;
		else while (current->next != nullptr) {
			if ((current->value < data) && (current->next->value >= data)) {
				if (abs(current->value - data) <= abs(current->next->value - data)) return current->value;
				else return current->next->value;
			}
			current = current->next;
			if ((current->next == nullptr) && (current->value < data)) return current->value;
		}
		return T{};
	}
	//вывод ближайшего элемента к данному 
	void print_search_near_elem(T data) {
		cout << "Ближайший элемент к " << data << " = " << search_near_elem(data) << endl;
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
	list.push_front(20);
	list.push_front(15);
	list.push_front(7);
	list.push_front(3);
	list.push_front(1);
	list.print();
	list.print_search_near_elem(-34);
	system("pause");
	return 0;
}