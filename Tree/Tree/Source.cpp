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
	//поиск определенного числа 
	Node* Search_elem(Node* current, T data) {
		if (!treeNum) return nullptr;
		else if ((current == nullptr) || (current->value == data)) return current;
		if (current->value > data) return Search_elem(current->leftChild, data);
		else return Search_elem(current->rightChild, data);
	}
	//поиск родителя определенного числа 
	Node* Search_Parent_elem(Node* current, T data) {
		if (!treeNum) return nullptr;
		else if (first->value == data) return first;
		else if (((current->leftChild != nullptr) && (current->leftChild->value == data)) || ((current->rightChild != nullptr) && (current->rightChild->value == data)))
			return current;
		if (current->value > data) return Search_Parent_elem(current->leftChild, data);
		else return Search_Parent_elem(current->rightChild, data);
	}
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
	//удаляет элемент из начала
	void del_elem(T data) {
		if (!treeNum) {
			cout << "Дерева нет" << endl;
			return;
		}
		Node* currentOld{ Search_Parent_elem(first, data) };
		if ((currentOld == first) && (currentOld->value == data)) {
			if ((currentOld->leftChild == nullptr) && (currentOld->rightChild == nullptr))//если нет сыновей и главный элемент
				clear(first);
			else if (currentOld->leftChild == nullptr) {//если есть один сын и главный элемент
				first = currentOld->rightChild;
				delete currentOld;
			}
			else if (currentOld->rightChild == nullptr) {//если есть один сын и главный элемент				
				first = currentOld->leftChild;
				delete currentOld;
			}
			else if ((currentOld->leftChild != nullptr) && (currentOld->rightChild != nullptr)) { //если есть два сына и главный элемент
				if (currentOld->rightChild->leftChild != nullptr) {
					Node* currentNew{ currentOld->rightChild };
					while (currentNew->leftChild != nullptr) currentNew = currentNew->leftChild;
					T num{ currentNew->value };
					del_elem(currentNew->value);
					++treeNum;
					currentNew = new Node;
					currentNew->value = num;
					currentNew->leftChild = currentOld->leftChild;
					currentNew->rightChild = currentOld->rightChild;
					first = currentNew;
				}
				else {												//елси спрва только 1 элемент
					Node* currentNew{ currentOld->rightChild };
					currentNew->leftChild = currentOld->leftChild;
					first = currentNew;
				}
			}
		}
		else {
			Node* current{};
			if ((currentOld->leftChild != nullptr) && (currentOld->leftChild->value == data)) current = currentOld->leftChild;
			else if (currentOld->rightChild != nullptr) current = currentOld->rightChild;
			if ((current != nullptr) && (current->value == data)) {
				if ((current->leftChild == nullptr) && (current->rightChild == nullptr)) {//если нет сыновей 
					if ((currentOld->leftChild != nullptr) && (currentOld->leftChild->value == data)) currentOld->leftChild = nullptr;
					else if (currentOld->rightChild != nullptr) currentOld->rightChild = nullptr;
					delete current;
				}
				else if (current->leftChild == nullptr) {//если есть один сын 
					current = current->rightChild;
					if ((currentOld->leftChild != nullptr) && (currentOld->leftChild->value == data)) currentOld->leftChild = current;
					else if (currentOld->rightChild != nullptr) currentOld->rightChild = current;
				}
				else if (current->rightChild == nullptr) {//если есть один сын 
					current = current->leftChild;
					if ((currentOld->leftChild != nullptr) && (currentOld->leftChild->value == data)) currentOld->leftChild = current;
					else if (currentOld->rightChild != nullptr) currentOld->rightChild = current;
				} 
				else if ((current->leftChild != nullptr) && (current->rightChild != nullptr)) { //если есть два сына
					if (current->rightChild->leftChild != nullptr) {
						Node* currentNew{ current->rightChild };
						while (currentNew->leftChild != nullptr) currentNew = currentNew->leftChild;
						T num{ currentNew->value };
						del_elem(currentNew->value);
						++treeNum;
						currentNew = new Node;
						currentNew->value = num;
						if ((currentOld->leftChild != nullptr) && (currentOld->leftChild->value == data)) {
							currentNew->leftChild = currentOld->leftChild->leftChild;
							currentNew->rightChild = currentOld->leftChild->rightChild;
							currentOld->leftChild = currentNew;
						}
						else if (currentOld->rightChild != nullptr) {
							currentNew->leftChild = currentOld->rightChild->leftChild;
							currentNew->rightChild = currentOld->rightChild->rightChild;
							currentOld->rightChild = currentNew;
						}
					}
					else {
						Node* currentNew{ current->rightChild };
						currentNew->leftChild = current->leftChild;
						if ((currentOld->leftChild != nullptr) && (currentOld->leftChild->value == data)) {
							currentOld->leftChild = currentNew;
						}
						else if (currentOld->rightChild != nullptr) {
							currentOld->rightChild = currentNew;
						}
					}
				}
			}
		}
		--treeNum;
	}
	Node* look_first() {
		return first;
	}
	//проверка на то существует ли это число в дереве
	bool check_Search_Elem(int data) {
		if (Search_elem(look_first(), data) == nullptr) return true;
		else return false;
	}
	//количество сыновей без сыновей
	int child(Node *current, int c) {
		if (!treeNum) return 0;
		else {
			if (current->leftChild != nullptr) {
				c = child(current->leftChild, c);
			}
		}
		if (current->rightChild != nullptr) {
			c = child(current->rightChild, c);
		}
		else if (current->leftChild == nullptr) ++c;
		return c;
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
	system("chcp 1251"); system("chcp 65001"); system("cls");
	ifstream inputFail;	inputFail.open("input.txt");
	ofstream outputFail; outputFail.open("output.txt");
	Tree<int> tree;
	string str{}, tranferStrToInt{};
	if (!inputFail.is_open() || !outputFail.is_open()) {
		cout << "Error opening file!" << endl;
	}
	else {														//создание дерева
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
	outputFail << tree.child(tree.look_first(), 0) << endl;
	inputFail.close();
	outputFail.close();
	cout << "Количество сыновей без сыновей - " << tree.child(tree.look_first(), 0) << endl;
	cout << "q - Выход | p - Вывод |  Любое другое целое число будет найдено в дереве и удаленно (если оно там есть)" << endl ;
	string strIn{};
	tranferStrToInt.clear();
	while (true) {												//ожидание ввода на удаляемый элемент
		cout << endl << "Ввод:";
		cin >> strIn;
		cout << endl;
		if ((char)strIn[0] == 'q') break;
		if ((char)strIn[0] == 'p') tree.print(tree.look_first(), 0);
		else for (int i{}; i < (int)strIn.length(); ++i) {
			if (!isdigit(strIn[i])) {
				cout << "Некорректный ввод!!!" << endl;
				tranferStrToInt.clear();
				strIn.clear();
				break;
			}
			tranferStrToInt += strIn[i];
		}
		if (tranferStrToInt.empty()) continue;
		if (tree.check_Search_Elem(stoi(tranferStrToInt))) {
			cout << "Такого числа в дереве нет!!!" << endl;
			tranferStrToInt.clear();
			strIn.clear();
			continue;
		}
		tree.del_elem(stoi(tranferStrToInt));
		tranferStrToInt.clear();
		strIn.clear();
		tree.print(tree.look_first(), 0);
	}
	system("pause");
	return 0;
}