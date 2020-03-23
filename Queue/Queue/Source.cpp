#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

template<typename T>
class Buffer {
public:
	class Node {
	public:
		T value{};
		Node* next;
	};
private:
	int bufferSize{};//длина
	Node* front{ nullptr };
public:
	~Buffer() {
		clear();
	}
	//добавляет элемент в начало 
	Node* push(T data) {
		if (front == nullptr) {
			Node* current = new Node;
			current->value = data;
			current->next = current;
			front = current;
			++bufferSize;
			return current;
		}
		else {
			Node* current = new Node;
			current->value = data;
			current->next = front;
			Node* currentOld{ front };
			for (int i{}; i < bufferSize - 1; currentOld = currentOld->next, ++i);
			currentOld->next = current;
			++bufferSize;
			return current;
		}
	}
	//удаляет элемент из начала
	Node* del_front() {
		if (!bufferSize) {
			//cout << "All clear" << endl;
			front = nullptr;
			return front;
		}
		Node* current{ front };
		Node* currentDel = { nullptr };
		currentDel = current->next;
		delete current;
		current = currentDel;
		front = current;
		--bufferSize;
		return current;
	}
	//полностью очищает стек
	void clear() {
		if (!bufferSize) {
			//cout << "All clear" << endl;
			front = nullptr;
			return;
		}
		Node* current{ front };
		Node* currentDel{ nullptr }; 
		for (int i{}; i < bufferSize; ++i) {
			currentDel = current->next;
			delete current;
			current = currentDel;
		}
		front = nullptr;
		bufferSize = 0;
		//cout << "All clear" << endl;
	}
	//возвращает первый элемент
	T look_front_value() {
		if (!bufferSize) {
			//cout << "Empty" << endl;
			return 0;
		}
		return front->value;
	}
	//возвращает сколько заполнино элементов
	int look_bufferSize() {
		return bufferSize;
	}
	//выводит весь стек
	void print() {
		if (!bufferSize) return;
		Node* current{ front };
		for (int i{}; i < bufferSize; ++i) {
			cout << current->value << "  ";
			current = current->next;
		}
		cout << "\n";
	}
};

int main() {
	system("chcp 65001"); system("cls"); 
	Buffer<int> buffer;
	ifstream inputFail;	inputFail.open("input.txt");
	ofstream outputFail; outputFail.open("output.txt");
	if (!inputFail.is_open() || !outputFail.is_open()) {
		cout << "Error opening file!" << endl;
	}
	else {
		string str{}, tranferStrToInt{};
		int maxSizeBuffer{}, numElem{};
		bool check{};
		getline(inputFail, str);
		for (int i{}; i < str.length(); ++i) {			//запись длины буыера и количества элесентов 
			tranferStrToInt.clear();
			while (str[i] != ' ' && i != str.length()) {
				tranferStrToInt += str[i];
				++i;
			}
			if (!check) maxSizeBuffer = stoi(tranferStrToInt);
			else numElem = stoi(tranferStrToInt);
			check = true;
		}
		int num{}, midArifm{}, sum{};
		bool checkSkip{};
		while (!inputFail.eof()) {						//
			getline(inputFail, str);
			num = stoi(str);
			checkSkip = false;
			sum = 0;
			if (num > 0) {
				for (int i{}; i < num; ++i) {
					if (checkSkip) {
						getline(inputFail, str);
						continue;
					}
					if (buffer.look_bufferSize() < maxSizeBuffer) {
						getline(inputFail, str);
						int elem{ stoi(str) };
						buffer.push(elem);
					}
					else {
						getline(inputFail, str);
						outputFail << "Memory overflow" << endl;
						checkSkip = true;
					}
				}
			}
			else if (num < 0){
				midArifm = 0;
				for (int i{}; i < abs(num); ++i) {
					if (buffer.look_front_value() != 0) ++sum;
					midArifm += buffer.look_front_value();
					buffer.del_front();
				}
				midArifm = midArifm / sum;				
				outputFail << midArifm << endl;
				if (buffer.look_bufferSize() == 0) outputFail << "Emptyqueue" << endl;
			}
			buffer.print();
		}
	}
	inputFail.close();
	outputFail.close();
	system("pause");
	return 0;
}