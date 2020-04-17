#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

template<typename T>
class Graph {
public:
	class Node;
	class Child {
	public:
		Node* next;
		Child* child;
	};
	class Node {
	public:
		T value{};
		int numIncoming{};
		Node* next;
		Child* child;
	};
private:
	int graphSize{};//длина
	int headSize{};
	Node* first{ nullptr };
	Node* head{ nullptr };
public:
	~Graph() {
		clear();
	}
	//поиск определенного числа 
	Node* Search_elem(T data) {
		Node* current{ first };
		if (current == nullptr) return nullptr;
		while (current != nullptr) {
			if (current->value == data) return current;
			current = current->next;
		}
		return nullptr;
	}
	//добавляет элемент в начало 
	Node* push(T data) {
		if (Search_elem(data) != nullptr) return nullptr;
		if (first == nullptr) {
			Node* current = new Node;
			current->value = data;
			current->numIncoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			first = current;
			++graphSize; 
			return current;
		}
		else {
			Node* current = new Node;
			current->value = data;
			current->numIncoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			Node* currentOld{ first };
			while (currentOld->next != nullptr)	currentOld = currentOld->next;
			currentOld->next = current;
			++graphSize;
			return current;
		}
	}
	//создает связи с детми
	void add_Child(T data, T dataChild) {
		if (!graphSize) {
			return;
		}
		Node* current{ Search_elem(data) };
		if (current == nullptr) return;
		Child* currentChild = new Child;
		Node* currentNodeChild{ Search_elem(dataChild) };
		if (currentNodeChild == nullptr) return;
		++currentNodeChild->numIncoming;
		currentChild->next = currentNodeChild;
		currentChild->child = nullptr;
		if (current->child == nullptr) current->child = currentChild;
		else {
			Child* newCurrentChild{ current->child };
			if (newCurrentChild->child != nullptr) 
				while (newCurrentChild->child != nullptr) newCurrentChild = newCurrentChild->child;			
			newCurrentChild->child = currentChild;
		}
	}
	//добавляет новый элемент в head
	Node* head_push(T data) {
		if (head == nullptr) {
			Node* current = new Node;
			current->value = data;
			current->numIncoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			head = current;
			++headSize;
			return current;
		}
		else {
			Node* current = new Node;
			current->value = data;
			current->numIncoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			Node* currentOld{ head };
			while (currentOld->next != nullptr)	currentOld = currentOld->next;
			currentOld->next = current;
			++headSize;
			return current;
		}
	}
	//проверка head на элемент 
	bool check_Search_elem(T data) {
		Node* current{ head };
		if (!headSize) return true;
		else while (current != nullptr) {
			if (current->value == data) return false;
			current = current->next;
		}
		return true;
	}
	//перестраиваем граф
	bool rebuild() {
		if (!graphSize) {
			return false;
		}
		Node* current{ first };
		Child* currentChild{ nullptr };
		int num{};
		for (int i{}; i < graphSize; ++i) {
			while (current != nullptr) {
				if ((current->numIncoming == 0) && (check_Search_elem(current->value))) {
					head_push(current->value);
					++num;
					if (current->child != nullptr) {
						currentChild = current->child;
						while (currentChild != nullptr) {
							--currentChild->next->numIncoming;
							currentChild = currentChild->child;
						}
					}
				}
				current = current->next;
			}
			if (graphSize == headSize) return true;
			current = first;
		}
		if ((num == 0) || (graphSize > headSize)) return false;
	}
	//полностью очищает графа
	void clear() {
		if (!graphSize) {
			first = nullptr;
			return;
		}
		Node* current{ first };
		Node* currentDel{ nullptr };
		while (current->next != nullptr) {
			currentDel = current->next;
			delete current;
			current = currentDel;
		}
		first = nullptr;
		graphSize = 0;
	}
	int look_graphSize() {
		return graphSize;
	}
	int look_I_num_head(int num) {
		Node* current{ head };
		for (int i{}; i < num; ++i, current = current->next);
		return current->value;
	}
	//выводит граф
	void print() {
		if (!graphSize) return;
		Node* current{ first };
		while (current != nullptr) {
			cout << current->value << "  ";
			current = current->next;
		}
		cout << endl;
	}
	//выводит перестроиный граф
	void printhead() {
		if (!graphSize) return;
		Node* current{ head };
		while (current != nullptr) {
			cout << current->value << "  ";
			current = current->next;
		}
		cout << endl;
	}
};

int main() {
	system("chcp 1251"); system("chcp 65001"); system("cls");
	ifstream inputFail;	inputFail.open("input.txt");
	ofstream outputFail; outputFail.open("output.txt");
	if (!inputFail.is_open() || !outputFail.is_open()) {
		cout << "Error opening file!" << endl;
	}	
	else {
		Graph<int> graph;
		string str{}, tranferStrToInt{};
		int tops{}/*вершины*/, ribs{}/*ребра*/;
		bool check{};
		getline(inputFail, str); 
		for (int i{}; i < (int)str.length(); ++i) {			//запись количества вершин графа и количества ребер(не юзаю)
			if ((i == (int)str.length()) || (str[i] != ' ')) {
				tranferStrToInt.clear();
				while (str[i] != ' ' && i != str.length()) {
					tranferStrToInt += str[i];
					++i;
				}
				if (!check) tops = stoi(tranferStrToInt);
				else ribs = stoi(tranferStrToInt);
				check = true;
			}
		}
		int num1{}, num2{};
		while (!inputFail.eof()) {
			getline(inputFail, str);
			check = false;
			for (int i{}; i < (int)str.length(); ++i) {
				if ((i == (int)str.length()) || (str[i] != ' ')) {
					tranferStrToInt.clear();
					while ((i != (int)str.length()) && (str[i] != ' ')) {
						tranferStrToInt += str[i];
						++i;
					}
					if (!check) num1 = stoi(tranferStrToInt);
					else num2 = stoi(tranferStrToInt);
					graph.push(stoi(tranferStrToInt));
					check = true;
				}
			}
			graph.add_Child(num1, num2);
		}
		graph.print();
		if (graph.rebuild()) {
			graph.printhead();
			for (int i{}; i < graph.look_graphSize(); ++i) {
				outputFail << graph.look_I_num_head(i) << " ";
			}
		}
		else {
			cout << "-1" << endl;
			outputFail << "-1";
		}
	}
	inputFail.close();
	outputFail.close();
	system("pause");
	return 0;
}