#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

template<typename T>
class Node {
public:
	T value{};
	Node<T>* next;
};

template<typename T>
class List {
	int listSize{};
	Node<T>* front{ nullptr };
public:
	~List() {
		clear();
	}
	//вставка числа вправо
	Node<T>* push_front(T data) {
		Node<T>* current = new Node<T>;
		current->value = data;
		current->next = front;
		front = current;
		++listSize;
		return current;
	}
	//удаляет повторы подряд 
	void del_replay() {
		Node<T>* current{ front };
		bool check{};
		while (current->next != nullptr) {
			if  (current->value == current->next->value) {
				current->next = current->next->next;
				--listSize;
				check = true;
			}
			if (current == front) front = current;
			if (check == false) current = current->next;
			check = false;
		}
	}
	int look_listSize() {
		return listSize;
	}
	//элемент под номерм num
	int look_num_elem(int num) {
		if (!listSize) return 0;
		Node<T>* current{ front };
		for (int i{ listSize }; i > num + 1; --i)
			current = current->next;
		return current->value;
	}
	//удаление всего 
	void clear() {
		if (!listSize) return;
		Node<T>* current{ front };
		Node<T>* currentDel{ nullptr };
		while (current->next != nullptr) {
			currentDel = current->next;
			delete current;
			current = currentDel;
		}
		front = nullptr;
		listSize = 0;
	}
	//вывод
	void print() {
		if (!listSize) return;
		for (Node<T>* current{ front }; current != nullptr; current = current->next) {
			cout << current->value << "  ";
		}
		cout << "\n";
	}
};

int main() {
	ifstream inputFail;	inputFail.open("input.txt");
	ofstream outputFail; outputFail.open("output.txt");
	if (!inputFail.is_open() || !outputFail.is_open()) {
		cerr << "Error opening file!" << endl;
	}
	else {
		List<int> list;
		string str{}, tranferStrToInt{};
		getline(inputFail, str);
		for (int i{}; i < (int)str.length(); ++i) {
			if ((i == (int)str.length()) || (str[i] != ' ')) {
				while ((i != (int)str.length()) && (str[i] != ' ')) {
					tranferStrToInt += str[i];
					++i;
				}
				list.push_front(stoi(tranferStrToInt));
				tranferStrToInt.clear();
			}
		}
		list.del_replay();
		list.print();
		for (int i{}; i < list.look_listSize(); ++i) {
			outputFail << list.look_num_elem(i) << " ";
		}
	}
	inputFail.close();
	outputFail.close();
	return 0;
}