#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

template<typename T>
class Node {
public:
	T value{};
	Node<T>* next;
};

template<typename T>
class Queue {
	int queueSize{};
	Node<T>* first{ nullptr };
public:
	~Queue() {
		clear();
	}	
	//вставка числа вправо
	Node<T>* push_front(T data) {
		if (first == nullptr) {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->next = nullptr;
			first = current;
			++queueSize;
			return current;
		}
		else {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->next = nullptr;
			Node<T>* currentOld{ first };
			while ( currentOld->next != nullptr) currentOld = currentOld->next;
			currentOld->next = current;
			++queueSize;
			return current;
			
		}
	}
	//вывод города под номером i
	T look_data(int i) {
		if ((queueSize < i + 1) || (!queueSize)) return T{};
		Node<T>* current{ first };
		for (int k{ 1 }; k < i+1; ++k) {
			current = current->next;
		}
		return current->value;
	}
	//удаление города по номером i
	Node<T>* del_data(int i) {
		if (!queueSize) return nullptr;
		Node<T>* currentOld{ first };
		if (i == 0) {//first = first->next;
			Node<T>* current{ first };
			current = currentOld->next;
			first = current;
			delete currentOld;
			--queueSize;
			return current;
		}
		else {
			for (int k{ 1 }; k < i; ++k) {
				currentOld = currentOld->next;
			}
			Node<T>* current{ currentOld->next };
			currentOld->next = current->next;
			delete current;
			--queueSize;
			return currentOld;
		}
	}
	//длина очереди 
	int length() {
		return queueSize;
	}
	//удаляет повторяющиеся из текущего 
	void delRepeat(Queue queue) {
		for (int i{ 0 }; i < length(); ++i) {
			for (int j{ 0 }; j < queue.length(); ++j) {
				if (look_data(i) == queue.look_data(j)) del_data(i);
			}
		}
	}
	//удаление всего 
	void clear() {  
		while (!queueSize){
			del_data(0);
		}
	}
	//вывод
	void print() {
		if (!queueSize) return;
		for (Node<T>* current{ first }; current != nullptr; current = current->next) {
			cout << current->value << ",  ";
		}
		cout << "\n";
	}
};

int main() {
	system("chcp 1251"); system("cls");//удалить из второго первый
	Queue<string> queue1;
	Queue<string> queue2;
	queue2.push_front("Barnaul");
	queue2.push_front("Novosibirsk");
	queue2.push_front("Novokuznetsk");
	queue2.push_front("Tula");
	queue2.push_front("Tomsk");
	queue2.push_front("Chelyabinsk");
	queue2.push_front("Shadrinsk");
	queue2.push_front("Yaroslavl");
	cout << "queue2: "; queue2.print();
	queue1.push_front("Barnaul");
	queue1.push_front("Novokuznetsk");
	queue1.push_front("Tomsk");
	queue1.push_front("Yaroslavl");
	cout << "queue1: "; queue1.print();
	queue2.delRepeat(queue1);
	cout << "queue2: "; queue2.print();
	system("pause");
	return 0;
}