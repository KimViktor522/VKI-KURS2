#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

template<typename T>
class Child;
template<typename T>
class Node {
	friend class Child<T>;
public:
	T value{};
	int numIncoming{};
	Node<T>* next;
	Child<T>* child;
};

template<typename T>
class Child {
	friend class Node<T>;
public:
	Node<T>* next;
	Child<T>* child;
};

template<typename T>
class Graph {
	int graphSize{};//�����
	int headSize{};
	Node<T>* first{ nullptr };
	Node<T>* head{ nullptr };
public:
	~Graph() {
		clear();
	}
	//����� ������������� ����� 
	Node<T>* Search_elem(T data) {
		Node<T>* current{ first };
		if (current == nullptr) return nullptr;
		while (current != nullptr) {
			if (current->value == data) return current;
			current = current->next;
		}
		return nullptr;
	}
	//��������� ������� � ������ 
	Node<T>* push(T data) {
		if (Search_elem(data) != nullptr) return nullptr;
		if (first == nullptr) {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->numIncoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			first = current;
			++graphSize; 
			return current;
		}
		else {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->numIncoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			Node<T>* currentOld{ first };
			while (currentOld->next != nullptr)	currentOld = currentOld->next;
			currentOld->next = current;
			++graphSize;
			return current;
		}
	}
	//������� ����� � �����
	void add_Child(T data, T dataChild) {
		if (!graphSize) {
			return;
		}
		Node<T>* current{ Search_elem(data) };
		if (current == nullptr) return;
		Child<T>* currentChild = new Child<T>;
		Node<T>* currentNodeChild{ Search_elem(dataChild) };
		if (currentNodeChild == nullptr) return;
		++currentNodeChild->numIncoming;
		currentChild->next = currentNodeChild;
		currentChild->child = nullptr;
		if (current->child == nullptr) current->child = currentChild;
		else {
			Child<T>* newCurrentChild{ current->child };
			if (newCurrentChild->child != nullptr) 
				while (newCurrentChild->child != nullptr) newCurrentChild = newCurrentChild->child;			
			newCurrentChild->child = currentChild;
		}
	}
	//��������� ����� ������� � head
	Node<T>* head_push(T data) {
		if (head == nullptr) {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->numIncoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			head = current;
			++headSize;
			return current;
		}
		else {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->numIncoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			Node<T>* currentOld{ head };
			while (currentOld->next != nullptr)	currentOld = currentOld->next;
			currentOld->next = current;
			++headSize;
			return current;
		}
	}
	//�������� head �� ������� 
	bool check_Search_elem(T data) {
		Node<T>* current{ head };
		if (!headSize) return true;
		else while (current != nullptr) {
			if (current->value == data) return false;
			current = current->next;
		}
		return true;
	}
	//������������� ����
	bool rebuild() {
		if (!graphSize) {
			return false;
		}
		Node<T>* current{ first };
		Child<T>* currentChild{ nullptr };
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
		return false; //if ((num == 0) || (graphSize > headSize)) 
	}
	//��������� ������� �����
	void clear() {
		if (!graphSize) {
			first = nullptr;
			return;
		}
		Node<T>* current{ first };
		Node<T>* currentDel{ nullptr };
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
		Node<T>* current{ head };
		for (int i{}; i < num; ++i, current = current->next);
		return current->value;
	}
	//������� ����
	void print() {
		if (!graphSize) return;
		Node<T>* current{ first };
		while (current != nullptr) {
			cout << current->value << "  ";
			current = current->next;
		}
		cout << endl;
	}
	//������� ������������ ����
	void printhead() {
		if (!graphSize) return;
		Node<T>* current{ head };
		while (current != nullptr) {
			cout << current->value << "  ";
			current = current->next;
		}
		cout << endl;
	}
};

int main() {
	system("chcp 65001"); system("cls");
	ifstream inputFail;	inputFail.open("input.txt");
	ofstream outputFail; outputFail.open("output.txt");
	if (!inputFail.is_open() || !outputFail.is_open()) {
		cerr << "Error opening file!" << endl;
	}	
	else {
		Graph<int> graph;
		string str{}, tranferStrToInt{};
		int tops{}/*�������*/, ribs{}/*�����*/;
		bool check{};
		getline(inputFail, str); 
		for (int i{}; i < (int)str.length(); ++i) {			//������ ���������� ������ ����� � ���������� �����(�� ����)
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