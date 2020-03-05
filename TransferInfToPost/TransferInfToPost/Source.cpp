#include <iostream>
#include <cstdio>
#include <string>     

using namespace std;

template<typename T>
class Stack {
public:
	class Node{
	public:
		T valne{};
		Node* next;
	};
private:	 
	int stacksize{};//�����
	Node* front = { nullptr };
public:
	~Stack(){
		clear();
	}
	//��������� ������� � ������ 
	Node* push_front(T data) {
		Node* current = new Node;
		current->valne = data;
		current->next = front;
		front = current;
		++stacksize;
		return current;
	}
	//������� ������� �� ������
	Node* del_front() {
		if (!stacksize) {
			cout << "All clear" << endl;
			return front;
		}
		Node* current{ front };
		Node* currentDel = { nullptr };
		currentDel = current->next;
		delete current;
		current = currentDel;
		front = current;
		--stacksize;
		return current;
	}
	//��������� ������� ����
	void clear() {
		if (!stacksize) {
			cout << "All clear" << endl;
			return;
		}
		Node* current{ front };
		Node* currentDel{ nullptr };
		while (current != nullptr) {
			currentDel = current->next;
			delete current;
			current = currentDel;
		}
		front = nullptr;
		stacksize = 0;
		cout << "All clear" << endl;
	}
	//���������� ������ �������
	int look_front() {
		if (!stacksize) {
			cout << "Empty" << endl;
			return 0;
		}
		Node* current{ front };
		return current->valne;
	}
	bool empty() {
		if (!stacksize)	return false;
		else return true;
	}
	//������� ���� ����
	void print() {
		for (Node* current{ front }; current != nullptr; current = current->next) {
			cout << current->valne << "  ";
		}
		cout << "\n";
	}
};

//�������� ����������� ��������� ������
bool validCheck_Str(string input) {
	bool checkBracket{}/*�������� ������������ ��������*/, checkActions{}/*�������� �� ��� ������ ��������*/,
		checkEequally{}/*�������� �� ������� �����(=)*/, checkVariable{}/*�������� �� ������ ����������*/,
		checkBracket_And_Actions{}/*�������� �� �������� ����� �� �������*/;
	for (int i{}; i < input.length(); ++i) {
		if (input[i] == '(') {
			checkBracket = true;
			checkBracket_And_Actions = true;
		}
		else checkBracket_And_Actions = false;
		if (input[i] == ')') checkBracket = false;
		if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/')) {
			if (checkActions) return false;		//��� ���������� ����� ������ (/*-+) 
			checkActions = true;
		}
		else checkActions = false;
		if (input[i] == '=') {
			if (checkEequally) return false;	//��� ������� ����� (=)
			checkEequally = true;
		}
		if ((input[i] != '(') || (input[i] != ')') || (input[i] != '+') || (input[i] != '-') || (input[i] != '*') || (input[i] != '/')) {//�������� �� ����������
			if (checkVariable) return false;	//��� ���������� ����� ����������
			checkVariable = true;
		}
		if ((checkBracket) && (input[i] == '='))
			return false;						//��� �������� �������� ���� (=)
		if ((checkBracket_And_Actions) && ((input[i] == '+') || (input[i] == '=') || (input[i] == '*') || (input[i] == '/')))
			return false;						//��� �������� (+*/=) ����� �� ������ (()
	}
	if (checkBracket) return false;				//��� ��������� ������� (())
	else return true;
}

//������� �� ��������� � �����������
string tranferInfToPost(string input,Stack<char> stack) {
	string output{};
	for (int i{}; i < input.length(); ++i) {
		if (input[i] == '(') {

		}
		else if (input[i] == ')') {

		}
		else if (input[i] == '=');

	}
	while (stack.empty) {
		output += stack.look_front();
		stack.del_front();
	}
	return output;
}

int main() {
	system("chcp 1251"); system("cls");
	string input{}, output{};
	cout << "������� ������ � ��������� ����: ";
	cin >> input; 
	input = "a+(f-b*c/(2-x)+y)/(a*r-k)";
	cout << endl;
	if (validCheck_Str(input)) {
		Stack<char> stack;
		output = tranferInfToPost(input, stack);
		cout << output;
	}
	else cout << "NOT CORRECT INPUT!!!";
	system("pause");
	return 0;
}