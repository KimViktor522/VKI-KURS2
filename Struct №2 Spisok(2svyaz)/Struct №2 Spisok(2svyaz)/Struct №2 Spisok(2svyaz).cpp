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
		if ((position > listsize + 1) || (position < 1)) {
			cout << "NOT CORRECT POS!!!" << endl;
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

	//менять 2 элемента в задоной поиции
	Node* swap_pos(int position1, int position2) {
		if ((position1 > listsize) || (position2 > listsize) || (position1 < 1) || (position2 < 1)) {
			cout << "NOT CORRECT POS!!!" << endl;
			return front;
		}
		Node* currentOld{ get_front() };
		int i{ 1 };
		Node* current1n { nullptr };
		Node* current1b { nullptr };
		Node* current1_n { nullptr };
		Node* current1_b { nullptr };
		Node* current2n { nullptr };
		Node* current2b { nullptr };
		Node* current2_n { nullptr };
		Node* current2_b { nullptr };

		while (currentOld != nullptr) {
			if (i == position1) {
				current1_n = currentOld;
				current1n = currentOld->next;
				current1b = currentOld->behind;
				current1_b = currentOld->next->behind;
			}
			if (i == position2) {
				current2_n = currentOld;
				current2n = currentOld->next;
				current2b = currentOld->behind;
				current2_b = currentOld->next->behind;
			}
			i++;
			currentOld = currentOld->next;
		}
		currentOld = get_front();
		i = 1;
		while (currentOld != nullptr) {
			if (i == position1 - 1) {
				if (currentOld->next != nullptr) currentOld->next = current2_n;
			}
			if (i == position1) {
				if (currentOld->next != nullptr) currentOld->next = current1n;
				if (currentOld->behind != nullptr) currentOld->behind = current1b;
			}
			if (i == position1 + 1) {
				if (currentOld->behind != nullptr) currentOld->behind = current2_b;
			}
			if (i == position2 - 1) {
				if (currentOld->next != nullptr) currentOld->next = current1_n;
			}
			if (i == position2) {
				if (currentOld->next != nullptr) currentOld->next = current2n;
				if (currentOld->behind != nullptr) currentOld->behind = current2b;
			}
			if (i == position2 + 1) {
				if (currentOld->behind != nullptr) currentOld->behind = current1_b;
			}
			//print();
			i++;
			currentOld = currentOld->next;
		}
		cout << endl;
		/* //колхоз
		int current1{}, current2{};
		while (currentOld != nullptr) {
			if (i == position1) {
				current1 = currentOld->value;
			}
			if (i == position2) {
				current2 = currentOld->value;
			}
			i++;
			currentOld = currentOld->next;
		}
		i = 1;
		currentOld = get_front();
		while (currentOld != nullptr) {
			if (i == position1) {
				currentOld->value = current2;
				if (currentOld->behind != nullptr) currentOld->behind->next = currentOld;
				if (currentOld->next != nullptr) currentOld->next->behind = currentOld;
			}
			if (i == position2) {
				currentOld->value = current1;
				if (currentOld->behind != nullptr) currentOld->behind->next = currentOld;
				if (currentOld->next != nullptr) currentOld->next->behind = currentOld;
			}
			i++;
			currentOld = currentOld->next;
		}*/
		return currentOld;
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
	cout << endl;
	list.inst_in_pos(position, number);

	list.print();

	int position1{}, position2{};
	cout << "выберите позицию 1: ";
	cin >> position1;
	cout << endl << "позицию 2: ";
	cin >> position2;
	cout << endl;
	list.swap_pos(position1, position2);
	
	list.print();
	list.clear();
	system("pause");
	return 0;
}