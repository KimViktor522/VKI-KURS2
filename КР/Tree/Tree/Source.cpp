#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

template<typename T>
class Tree {
public:
	class Node {
	public:
		T value{};
		Node* leftChild{};
		Node* rightChild{};
	};
private:
	int treeNum{};//количество элементов
	Node* first{ nullptr };
public:
	~Tree() {
		clear(look_first());
	}
	//добавляет элемент в дерево
	Node* push(T data) { 
		if (first == nullptr) {
			Node* current = new Node;
			current->value = data;
			current->leftChild = nullptr;
			current->rightChild = nullptr;
			first = current;
			++treeNum;
			return current;
		}
		else {
			Node* current = new Node;
			current->value = data;
			current->leftChild = nullptr;
			current->rightChild = nullptr;
			Node* currentOld{ first }; 
			while (currentOld != nullptr){
				if (currentOld->value == data) {
					return current;
				}
				else if (currentOld->value > data){
					if (currentOld->leftChild != nullptr)
						currentOld = currentOld->leftChild;
					else {
						currentOld->leftChild = current;
						++treeNum;
						return current;
					}
				}
				else if (currentOld->value < data) {
					if (currentOld->rightChild != nullptr)
						currentOld = currentOld->rightChild;
					else {
						currentOld->rightChild = current;
						++treeNum;
						return current;
					}
				}
			}
		}
	}
private:
	//полностью очищает дерево
	void clear(Node* current) {
		if (!treeNum) return;
		else {
			if (current->leftChild != nullptr) {
				clear(current->leftChild);
			}
		}
		if (current->rightChild != nullptr) {
			clear(current->rightChild);
		}
		delete current;
		first = nullptr;
	}
public:
	Node* look_first() {
		return first;
	}
	//количество сыновей на заданном уравне 
	int search(Node* current, int p, int level, int num) {
		if (!treeNum) return 0;
		else {
			if (current->leftChild != nullptr) {
				num = search(current->leftChild, ++p, level, num);
				--p;
			}
		}
		if (current->rightChild != nullptr) {
			num = search(current->rightChild, ++p, level, num);
			--p;
		}
		if (p == level) ++num;
		return num;
	}
	//вывести все дерево
	void print(Node *current, int p) {
		if (!treeNum) return;
		else {
			if (current->leftChild != nullptr) {
				print(current->leftChild, ++p);
				--p;
			}
			for (int i{}; i < p; ++i) cout << "|";
			cout << current->value << endl;
		}
		if (current->rightChild != nullptr) {
			print(current->rightChild, ++p);
			--p;
		}
	}
};

int main() {
	ifstream inputFail;	inputFail.open("input.txt");
	ofstream outputFail; outputFail.open("output.txt");
	Tree<int> tree;
	string str{}, tranferStrToInt{};
	int level{ 0 };
	if (!inputFail.is_open() || !outputFail.is_open()) {
		cout << "Error opening file!" << endl;
	}
	else {														//создание дерева
		getline(inputFail, str);
		level = stoi(str);
		getline(inputFail, str);
		for (int i{}; i < (int)str.length(); ++i)
			if ((i == (int)str.length()) || (str[i] != ' ')) {
				while ((i != (int)str.length()) && (str[i] != ' ')) {
					tranferStrToInt += str[i];
					++i;
				}
				tree.push(stoi(tranferStrToInt));
				tranferStrToInt.clear();
			}
	}
	tree.print(tree.look_first(), 0);
	cout << endl;
	outputFail << tree.search(tree.look_first(), 0, level, 0) << endl;
	inputFail.close();
	outputFail.close();
	cout << "sons quantity level " << level << " - " << tree.search(tree.look_first(), 0, level, 0) << endl;
	return 0;
}