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
	//удаление начала и конца
	void del_front_and_back() {
		Node* current{ nullptr };
		Node* currentF{ get_front() };
		Node* currentB{ get_back() };
		cout << "\n" << currentF->valne << "  " << currentB->valne << "\n";
		cout << currentF->next << "  " << currentB->next << "\n" << "\n";
		current = currentF->next;
		currentB = current;
		delete currentF;
		/*Node* currentBuf{ nullptr };
		while (currentB->next!=nullptr){
			currentBuf = currentB->next;
			cout << currentBuf->valne << "  ";
			if (currentBuf->next != nullptr) {
				currentB->next = nullptr;
				current = currentB;
			}
			else currentB = currentB->next;
		}
		cout << "\n";*/
		front = current;
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
	list.clear();
	list.print();
	list.push_front(1);
	list.push_back(2);
	list.print();
	system("pause");
	return 0;
}