#include <iostream>
#include <cstdio>
#include <list>

using namespace std;

struct Node {
	int valne{};
	Node* next;
};

struct List {
	//число справа
	Node* front{ nullptr };
	Node* get_front() { return front; };

	//число слева
	Node* back{ nullptr };
	Node* get_back() {
		Node* current{ get_front() };
		while (current->next != nullptr) {
			current = current->next;
		}
		back = current;
		return back;
	}

	//вставка числа вправо
	Node* push_front(int data) { 
		Node* current = new Node;
		current->valne = data;
		current->next = front;
		front = current;
		return current;
	}
	//вставка числа влево
	Node* push_back(int data) {
		Node* current = new Node;
		get_back();
		current->valne = data;
		back->next = current;
		current->next = nullptr;
		return current;
	}
	//вставка в определенную позицию 
	Node* inst_in_pos(int position, int data) {
		if (position == 1) {
			return push_front(data);
		}
		Node* current = new Node;
		Node* currentOld{ get_front() };
		int i{ 1 };
		while (currentOld->next != nullptr) {			
			if (i == position - 1) {
				current->next = currentOld->next;
			}
			if (i == position) {
				current->valne = data;
				break;
			}
			++i;
			currentOld = currentOld->next;
		}
		currentOld = get_front();
		while (currentOld->next != nullptr) {
			if (current->next == currentOld->next) {
				currentOld->next = current;
				break;
			}
			currentOld = currentOld->next;
		}		
		
		return currentOld;
	}
	//удаление начала и конца
	void del_front_and_back() {
		Node* current{ nullptr };
		Node* currentF{ get_front() };
		current = currentF->next;
		Node* currentB{ current };
		delete currentF;
		Node* currentBuf{ nullptr };
		while (currentB->next!=nullptr){
			currentBuf = currentB->next;
			if (currentBuf->next == nullptr) {
				currentB->next = nullptr;
				break;
			}
			else currentB = currentB->next;
		}
		front = current;
		delete currentBuf;
	}

	//удаление всего 
	void clear() { 
		Node* current{ get_front() };
		Node* currentDel{ nullptr };
		while (current->next != nullptr){///переделать
			currentDel = current->next;
			current->valne = currentDel->valne;	
			current = current->next;
		}	
		delete current;	
		front = nullptr;
		back = nullptr;
	}

	//вывод
	void print() {
		for (Node* current{ get_front() }; current != nullptr; current = current->next) {
			cout << current->valne << "  ";
		}
		cout << "\n";
	}
};

int main() {
	system("chcp 1251");
	List list;
	list.print();
	list.push_front(5);
	list.print();
	list.push_front(4);
	list.push_back(2);
	list.push_front(5);
	list.push_back(6);
	list.push_front(9);
	list.push_back(1);
	list.print();
	list.del_front_and_back();
	list.print();

	int position{}, number{};
	cout << "Введите номер ячейки вкоторую хотите вставить число: ";
	cin >> position;
	cout << endl << "это число: ";
	cin >> number;
	list.inst_in_pos(position, number);

	list.print();
	list.clear();
	system("pause");
	return 0;
}