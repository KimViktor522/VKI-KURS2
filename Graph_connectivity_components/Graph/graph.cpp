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
	int numIncoming{0};
	int numOutcoming{0};
	int intСomponent{0};//к какой компаненте относится точка
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
	int graphSize{0};//длина
	int num_Connectivity_Components{1};//количество компонентов связности
	Node<T>* first{ nullptr };
public:
	~Graph() {
		clear();
	}
	//поиск определенного числа 
	Node<T>* Search_elem(T data) {
		Node<T>* current{ first };
		if (current == nullptr) return nullptr;
		while (current != nullptr) {
			if (current->value == data) return current;
			current = current->next;
		}
		return nullptr;
	}
	//добавляет элемент в начало 
	Node<T>* push(T data) {
		if (Search_elem(data) != nullptr) return nullptr;
		if (first == nullptr) {
			Node<T>* current = new Node<T>;
			current->value = data;
			current->numIncoming = 0;
			current->numOutcoming = 0;
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
			current->numOutcoming = 0;
			current->next = nullptr;
			current->child = nullptr;
			Node<T>* currentOld{ first };
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
		Node<T>* current{ Search_elem(data) };
		if (current == nullptr) return;
		Child<T>* currentChild = new Child<T>;
		Node<T>* currentNodeChild{ Search_elem(dataChild) };
		if (currentNodeChild == nullptr) return;
		++current->numOutcoming;
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
	//поиск того элемента который еще не проверялся
	Node<T>* search_Free_Element() {
		Node<T>* current{ first };
		for (int i{ 0 }; i < graphSize; ++i) {		
			if (current->intСomponent == 0) return current;
			else current = current->next;
		}
		return nullptr;
	}
	//проверка звязи между вержинами 
	bool check_Connectivity_Tops(T num1, T num2) {
		Node<T>* current{ first };
		for (int i{ 0 }; i < graphSize; ++i) {
			if (current->value == num1) break;
			else current = current->next;
		}
		if (current->child != nullptr) {
			Child<T>* currentSec{ current->child };
			for (int i{ 0 }; i < current->numOutcoming; ++i) {
				if (currentSec->next->value == num2) return true;
				else if (currentSec->child != nullptr) currentSec = currentSec->child;
			}
		}
		return false;
	}
	//поиск компонентов связности
	void search_For_Connectivity_Components_rec(Node<T>* current) {
		current->intСomponent = num_Connectivity_Components;
		if (current->child != nullptr) {
			Child<T>* currentSec{ current->child };
			for (int k{ 0 }; k < current->numOutcoming; ++k) {
				if (currentSec->next->intСomponent == 0) {
					search_For_Connectivity_Components_rec(currentSec->next);
				}
				else if (currentSec->child != nullptr) currentSec = currentSec->child;
				else {
					if (search_Free_Element() != nullptr) {
						if (check_Connectivity_Tops(currentSec->next->value, search_Free_Element()->value) == false) ++num_Connectivity_Components;
						search_For_Connectivity_Components_rec(search_Free_Element());
					}
					return;
				}
			}
		}
		else {			
			if (search_Free_Element() != nullptr) {
				++num_Connectivity_Components;
				search_For_Connectivity_Components_rec(search_Free_Element());
			}
		}
		return;
	}
	//вывод количества компонентов связности
	int look_Num_Connectivity_Components() {
		return num_Connectivity_Components;
	}
	//количество элементов
	int look_graphSize() {
		return graphSize;
	}
	//полностью очищает графа
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
	//вывод номеров подграфа
	int num_Subgraph(int numElem) {
		Node<T>* current{ first };
		int num{};
		for (int i{ 0 }; i < numElem; ++i) current = current->next;
		return current->intСomponent;
	}
	//выводит граф
	void print() {
		if (!graphSize) return;
		Node<T>* current{ first };
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
		int tops{}/*вершины*/, ribs{}/*ребра*/;
		bool check{};
		getline(inputFail, str); 
		for (int i{}; i < (int)str.length(); ++i) {			//запись количества вершин графа и количества ребер
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
		for (int i{ 1 }; i <= tops; ++i) graph.push(i);		//добавление точек
		int num1{}, num2{};
		for (int p{ 0 }; p < ribs; ++p) {
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
					check = true;
				}
			}
			graph.add_Child(num1, num2);//создает двойные связи (неориентированный граф)
			graph.add_Child(num2, num1);
		}
		graph.print();
		graph.search_For_Connectivity_Components_rec(graph.search_Free_Element());
		//вывод в файл
		outputFail << graph.look_Num_Connectivity_Components() << endl;
		for (int i{ 0 }; i < graph.look_graphSize(); ++i) outputFail << graph.num_Subgraph(i) << " ";
		//вывод в консоль
		cout << graph.look_Num_Connectivity_Components() << endl;
		for (int i{ 0 }; i < graph.look_graphSize(); ++i) cout << graph.num_Subgraph(i) << " ";
		cout << endl;

	}
	inputFail.close();
	outputFail.close();
	system("pause");
	return 0;
}