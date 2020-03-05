#include <iostream>
#include <cstdio>

using namespace std;
class Stack {
public:
	class Node{
	public:
		int valne{};
		Node* next;
	};
	~Stack(){
		clear();
	}
private:	 
	int listsize{};//длина
	Node* front = { nullptr };
public:
	Node* push_front(int data) {
		Node* current = new Node;
		current->valne = data;
		current->next = front;
		front = current;
		++listsize;
		return current;
	}
	Node* del_front() {
		if (!listsize) {
			cout << "All clear" << endl;
			return front;
		}
		Node* current{ front };
		Node* currentDel = { nullptr };
		currentDel = current->next;
		delete current;
		current = currentDel;
		front = current;
		--listsize;
		return current;
	}
	void clear() {
		if (!listsize) {
			cout << "All clear" << endl;
			return;
		}
		Node* current{ front };
		Node* currentDel{ nullptr };
		while (current != nullptr) {
			currentDel = current->next;
			delete current;
			current = currentDel;
		}
		front = nullptr;
		listsize = 0;
		cout << "All clear" << endl;
	}

	int look_front() {
		if (!listsize) {
			cout << "Empty" << endl;
			return 0;
		}
		Node* current{ front };
		return current->valne;
	}
	void print() {
		for (Node* current{ front }; current != nullptr; current = current->next) {
			cout << current->valne << "  ";
		}
		cout << "\n";
	}
};

int main() {
	system("chcp 1251"); system("cls");
	Stack stack;
	stack.clear();
	cout << stack.look_front() << endl;
	stack.print();
	stack.push_front(5);
	stack.push_front(1);
	stack.push_front(8);
	stack.push_front(3);
	stack.push_front(9);
	stack.print();
	stack.del_front();
	stack.print();
	cout << stack.look_front() << endl;

	system("pause");
	return 0;
}