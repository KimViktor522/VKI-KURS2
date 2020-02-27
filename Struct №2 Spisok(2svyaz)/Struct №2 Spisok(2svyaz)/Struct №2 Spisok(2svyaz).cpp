#include <iostream>
#include <cstdio>

using namespace std;
class List{
public:
	struct Node {
		int value{};
		Node* next;
		Node* behind;
	};

private:
	//длина 
	int listsize{};

	Node* front{ nullptr };
	Node* back{ nullptr };

	//число справа
	Node* get_front() { return front; };
	//число слева
	Node* get_back() {
		Node* current{ get_front() };
		while (current->next != nullptr) {
			current = current->next;
		}
		back = current;
		return back;
	}

public:

	~List() {
		clear();
	}

	//вставка числа вправо
	Node* push_front(int data) {
		Node* current = new Node;
		current->value = data;
		current->next = front;
		current->behind = nullptr;
		if (listsize) {
			front->behind = current;
		}
		front = current;
		++listsize;
		return current;
	}

	//вставка числа влево
	Node* push_back(int data) {
		Node* current = new Node;
		get_back();
		current->value = data;
		back->next = current;
		current->next = nullptr;
		current->behind = back;
		++listsize;
		return current;
	}
	

	//вставка в определенную позицию 
	Node* inst_in_pos(int position, int data) {
		if (position == 1) {
			return push_front(data);
		}
		if (position == listsize + 1) {
			return push_back(data);
		}
		if (position > listsize + 1) {
			cout << "NOT CORRECT!!!" << endl;
			return front;
		}
		Node* current = new Node;
		Node* currentOld{ get_front() };
		int i{ 1 };
		while (true) {
			if (i == position - 1) {
				current->next = currentOld->next;
			}
			if (i == position) {
				current->value = data;
				current->behind = currentOld->behind;
				current->behind->next = current;
				current->next->behind = current;
				break;
			}
			++i;
			currentOld = currentOld->next;
		}
		listsize++;
		return current;
	}

	//удаление начала и конца
	void del_front_and_back() {
		if (!listsize) {
			cout << "ERROR: DELETE FRONT AND BACK!!!" << endl;
			return;
		}
		Node* current{ nullptr };
		Node* currentF{ get_front() };
		current = currentF->next;
		current->behind = nullptr;
		--listsize;
		if (!listsize) {
			front = current;
			cout << "Delete front" << endl << "ERROR: DELETE BACK!!!" << endl;
			return;
		}
		Node* currentB{ current };
		delete currentF;
		while (currentB->next!=nullptr){
			if (currentB->next->next == nullptr) {
				currentB->next = nullptr;
				break;
			}
			else currentB = currentB->next;
		}
		front = current;
		--listsize;
		cout << "Delete front and back" << endl;
		print();
	}

	//удаление всего 
	void clear() { 
		if (!listsize) {
			cout << "All clear" << endl;
			return;
		}
		Node* current{ get_front() };
		Node* currentDel{ nullptr };
		while (current->next != nullptr){
			currentDel = current->next;
			delete current;	
			current = currentDel;
		}	
		front = nullptr;
		back = nullptr;
		listsize = 0;
		cout << "All clear" << endl;
	}

	//вывод
	void print() {
		for (Node* current{ get_front() }; current != nullptr; current = current->next) {
			cout << current->value << "  " << current->next << "  " << current->behind << endl;
		}
		cout << endl;
	}
};
int main() {
	system("chcp 1251"); system("cls");
	List list;
	list.clear();
	list.print();
	list.push_front(5);
	list.print();
	list.push_front(4);
	list.push_front(8);
	list.push_front(2);
	list.push_back(2);
	list.print();
	list.del_front_and_back();
	list.push_front(3);
	list.push_front(9);
	list.push_back(7);
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