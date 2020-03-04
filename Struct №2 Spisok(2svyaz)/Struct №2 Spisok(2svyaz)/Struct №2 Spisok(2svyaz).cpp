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

	//менять 2 элемента в заданной позиции
	Node* swap_pos(int position1, int position2) {
		if ((position1 >= listsize) || (position2 >= listsize) || (position1 < 1) || (position2 < 1)) { 
			cout << "NOT CORRECT POS!!!" << endl;
			return front;
		}
		Node* currentOld{ get_front() };	// Текущий елемент
		int i{ 1 };							
		Node* current1n = { nullptr };		// element1 next		
		Node* current1b = { nullptr };		// element1 back
		Node* current1_n = { nullptr };		// element1
		Node* current2n = { nullptr };		// element2 next		
		Node* current2b = { nullptr };		// element2 back
		Node* current2_n = { nullptr };		// element2

		while (currentOld != nullptr) {		// зы можно писать просто currentOld, ибо nullptr == false
			if (i == position1) {
				current1_n = currentOld;
				current1n = currentOld->next;
				current1b = currentOld->behind;
			}
			if (i == position2) {
				current2_n = currentOld;
				current2n = currentOld->next;
				current2b = currentOld->behind;
			}
			i++;
			currentOld = currentOld->next;
		}
		currentOld = get_front();
		if (front == current1_n) front = current2_n;
		else if (front == current2_n) front = current1_n;
		i = 1;

		bool goToNext{};		// если мы уже перешли к следующему, то ещё раз не переходим
		while (currentOld != nullptr) {
			goToNext = false;
			if (i == position1 - 1) {
				currentOld->next = current2_n;		// Если встали на предыдущий от pos1, то меняем его указатель и, так как теперь она указывает\
														на pos2, то переходим к следующей ячейке вручную
				currentOld = current1_n;
				goToNext = true;
			}
			else if (i == position1) {
				currentOld->behind = current2b;		// Та же логика
				currentOld->next = current2n;
				currentOld = current1n;
				goToNext = true;
			}
			else if (i == position1 + 1) {
				currentOld->behind = current2_n;
			}
			if (i == position2 - 1) {
				currentOld->next = current1_n;
				currentOld = current2_n;
				goToNext = true;
			}
			else if (i == position2) {
				currentOld->behind = current1b;
				currentOld->next = current1n;
				currentOld = current2n;
				goToNext = true;
			}
			else if (i == position2 + 1) {
				currentOld->behind = current1_n;
			}

			if (!goToNext) currentOld = currentOld->next;
			++i;
		}
		if (current1_n->next == current1_n) current1_n->next = current2_n;			// Если соседние, то элемент ссылается после замены сам на себя, хотя должен ссылаться на другой
		if (current2_n->next == current2_n) current2_n->next = current1_n;
		if (current2_n->behind == current2_n) current2_n->behind = current1_n;
		if (current1_n->behind == current1_n) current1_n->behind = current2_n;

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
		while (current != nullptr){
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
	
	/*int position{}, number{};
	cout << "Введите номер ячейки вкоторую хотите вставить число: ";
	cin >> position;
	cout << endl << "это число: ";
	cin >> number;
	cout << endl;
	list.inst_in_pos(position, number);*/

	//list.print();

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