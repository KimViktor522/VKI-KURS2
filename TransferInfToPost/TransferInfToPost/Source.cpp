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
	int stacksize{};//длина
	Node* front = { nullptr };
public:
	~Stack(){
		clear();
	}
	//добавляет элемент в начало 
	Node* push_front(T data) {
		Node* current = new Node;
		current->valne = data;
		current->next = front;
		front = current;
		++stacksize;
		return current;
	}
	//удаляет элемент из начала
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
	//полностью очищает стек
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
	//возвращает первый элемент
	int look_front() {
		if (!stacksize) {
			cout << "Empty" << endl;
			return 0;
		}
		Node* current{ front };
		return current->valne;
	}
	//проверка на пустату стека
	bool empty() {
		if (!stacksize)	return false;
		else return true;
	}
	//выводит весь стек
	void print() {
		for (Node* current{ front }; current != nullptr; current = current->next) {
			cout << current->valne << "  ";
		}
		cout << "\n";
	}
}; 

bool isbracket(char input) {
	if ((input == '(') || (input == ')')) return true;
	else return false;
}

bool isoperatr(char input) {
	if ((input >= '(') || (input >= ')') || (input >= '+') || (input >= '-') || (input >= '*') || (input >= '/') || (input >= '=')) return true;
	else return false;
}

bool isactions_and_equally(char input) {
	if ((input >= '+') || (input >= '-') || (input >= '*') || (input >= '/') || (input >= '=')) return true;
	else return false;
}

bool isactions(char input) {
	if ((input >= '+') || (input >= '-') || (input >= '*') || (input >= '/')) return true;
	else return false;
}

//проверка коректности инфиксной строки
bool validCheck_Str(string input) {
	bool checkBracket{}/*проверка неправельных скобочек*/, checkActions{}/*проверка на два подряд действия*/,
		checkEqually{}/*проверка на несколько равно(=)*/, checkVariable{}/*проверка на повтор переменных*/,
		checkBracket_And_Actions{}/*проверка на действие рядом со скобкой*/;
	for (int i{}; i < input.length(); ++i) {
		if (isalnum(input[i]) || isoperatr(input[i])) 
			return false;						//при не правильном вводе
		if (input.empty()) return false;		//при пустой строке
		if (input[i] == ' ') return false;		//при нахождение пробела
		if (input[i] == '(') {
			checkBracket = true;
			checkBracket_And_Actions = true;
		}
		else checkBracket_And_Actions = false;
		if (input[i] == ')') checkBracket = false;
		if (isactions(input[i])) {
			if (checkActions) return false;		//при повторенеи рядом знаков (/*-+) 
			checkActions = true;
		}
		else checkActions = false;
		if (input[i] == '=') {
			if (checkEqually) return false;		//при повторе знака (=)
			checkEqually = true;
		}
		if (isbracket(input[i]) || isactions(input[i])) {//проверка на переменную
			if (checkVariable) return false;	//при повторение рядом переменных
			checkVariable = true;
		}
		if ((checkBracket) && (input[i] == '='))
			return false;						//при открытых скобоках знак (=)
		if ((checkBracket_And_Actions) && ((input[i] == '+') || (input[i] == '=') || (input[i] == '*') || (input[i] == '/')))
			return false;						//при действие (+*/=) рядом со знаком (()
		if ((i == input.length - 1) && isactions_and_equally(input[i])) 
			return false;						//при действии в конце
	}
	if (checkBracket) return false;				//при нарушенеи порядка (())
	else return true;
}

//перевод из инфиксной в постфиксную
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
	cout << "Введите строку в инфиксном виде: ";
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