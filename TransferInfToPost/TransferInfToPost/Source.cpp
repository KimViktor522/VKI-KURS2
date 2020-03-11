#include <iostream>
#include <cstdio>
#include <string>     

using namespace std;

template<typename T>
class Stack {
public:
	class Node{
	public:
		int priority{};
		T value{};
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
	Node* push_front(T data, int num) {
		Node* current = new Node;
		current->value = data;
		current->priority = num;
		current->next = front;
		front = current;
		++stacksize;
		return current;
	}
	//удаляет элемент из начала
	Node* del_front() {
		if (!stacksize) {
			//cout << "All clear" << endl;
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
			//cout << "All clear" << endl;
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
		//cout << "All clear" << endl;
	}
	//возвращает первый элемент
	T look_front_value() {
		if (!stacksize) {
			//cout << "Empty" << endl;
			return 0;
		}
		Node* current{ front };
		return current->value;
	}
	int look_front_priority() {
		if (!stacksize) {
			//cout << "Empty" << endl;
			return 0;
		}
		Node* current{ front };
		return current->priority;
	}
	//проверка на пустату стека
	bool empty() {
		if (!stacksize)	return false;
		else return true;
	}
	//выводит весь стек
	void print() {
		for (Node* current{ front }; current != nullptr; current = current->next) {
			cout << current->value << "  ";
		}
		cout << "\n";
	}
}; 

bool isbracket(char input) {
	if ((input == '(') || (input == ')')) return true;
	else return false;
}

bool isoperatr(char input) {
	if ((input == '(') || (input == ')') || (input == '+') || (input == '-') || (input == '*') || (input == '/') || (input == '=')) return true;
	else return false;
}

bool isactions_and_equally(char input) {
	if ((input == '+') || (input == '-') || (input == '*') || (input == '/') || (input == '=')) return true;
	else return false;
}

bool isactions(char input) {
	if ((input == '+') || (input == '-') || (input == '*') || (input == '/')) return true;
	else return false;
}

//проверка коректности инфиксной строки
bool validInfix_Str(string input) {
	bool checkBracket{}/*проверка неправельных скобочек*/, checkActions{}/*проверка на два подряд действия*/,
		checkEqually{}/*проверка на несколько равно(=)*/, checkVariable{}/*проверка на повтор переменных*/,
		checkBracket_And_Actions{}/*проверка на действие рядом со скобкой*/, 
		checkEqually_And_Actions{}/*проверка на подряд равно и действия */,
		checkPoint{}/*проверка на две точки в одном числе*/;
	int sumBracket{};
	for (int i{}; i < input.length(); ++i) {
		if (!isalnum(input[i]) && !isoperatr(input[i]) && input[i] != '.')
			return false;								//при вводе некорректного символа
		if ((input[i] == '.') && (!((i - 1) >= 0) || !(isdigit(input[i - 1])) || !((i + 1) < input.length()) || !(isdigit(input[i + 1])) || (checkPoint))) {
			return false;								//при неправельном дробном числе 
		}
		if ((isalnum(input[i]) && input[i + 1] == '(') || (isalnum(input[i + 1]) && input[i] == ')'))
			return false;								//при цифре перед '(' или после ')'
		if ((input[i] == '-' || input[i] == '+') && input[i - 1] == '(' && input[i + 1] == ')')
			return false;								//при минусе или плюсе внутри скобок '(-)''(+)'
		if (input[i] == '.') checkPoint = true;
		if (isactions_and_equally(input[i])) checkPoint = false;
		if ((checkBracket_And_Actions) && (isactions_and_equally(input[i])) && (input[i] != '-') && (input[i] != '+'))
			return false;								//при действие '/*=+' после знака '('
		if ((checkBracket) && (input[i] == '='))
			return false;								//при открытых скобоках знак '='
		if (input.empty()) return false;				//при пустой строке
		if (input[i] == '(') {
			++sumBracket;
			checkBracket = true;
			checkBracket_And_Actions = true;
		}
		else checkBracket_And_Actions = false;
		if (input[i] == ')') {
			if (input[i - 1] == '(') return false;		//при пустых скобках 
			--sumBracket;
			checkBracket = false;
		}
		if (input[i] == '=') {
			if (checkActions) return false;				//при действие перед знака '='
		}
		if (isactions(input[i])) {
			if (checkActions) return false;				//при повторенеи рядом знаков '/*-+'
			if ((checkEqually_And_Actions) && (input[i] != '-'))
				return false;  //при действие после знака '='
			checkActions = true;
		}
		else checkActions = false; 
		if (input[i] == '=') {
			if (checkEqually) return false;				//при повторе знака '='
			checkEqually = true;
			checkEqually_And_Actions = true;
		}
		else checkEqually_And_Actions = false;
		if ((i == (input.length() - 1)) && (isactions_and_equally(input[i])))
			return false;								//при действии в конце
		//cout << i << " ";
	}
	if ((checkBracket) || (sumBracket)) return false;	//при нарушенеи порядка скобочек '( )'
	else return true;
}

string upgradeInfix(string input) {
	for (int i{}; i < input.length(); ++i) {
		if (input[i] == ',') input[i] = '.';
		if (input[i] == '(' && (input[i + 1] == '-')) input.insert(++i, "0"); //(-
		if (i == 0 && (input[i] == '-')) {
			input.insert(i, "0"); //-(
			++i;
		}
		if (isalnum(input[i]) && input[i + 1] == '(') input.insert(++i,"*");
		if (input[i] == ')' && isalnum(input[i + 1])) input.insert(++i, "*");
		if (input[i] == ')' && input[i + 1] == '(') input.insert(++i, "*");
	}
	return input;
}

//перевод из инфиксной в постфиксную
string tranferInfToPost(string input) {
	string output{};
	Stack<char> stack;
	for (int i{}; i < input.length(); ++i) {
		if ((input[i] != '.') && !(isbracket(input[i])) && !(isalnum(input[i]))){
			output += ' ';
		}
		if (!isoperatr(input[i])) {
			output += input[i]; 
		}
		else if (input[i] == '(') {
			stack.push_front(input[i], 1);
		}
		else if (input[i] == ')') {
			while (stack.look_front_priority() > 1) {	//удаляем из стека пока не встретим приоритет 1 '('
				output += ' ';
				output += stack.look_front_value();
				stack.del_front();
			}
			stack.del_front();							//удалить из стека приоритет 1 '('
		}
		else if (isactions_and_equally(input[i])) {		//если встретелись знаки '=/*-+'
			if (input[i] == '=') {
				while (stack.look_front_priority() >= 3) {	
					output += stack.look_front_value();
					if ((input[i + 1] != '-') && (input[i + 1] != '(')) output += ' ';
					stack.del_front();
				}
				stack.push_front(input[i], 3);
			}
			else if ((input[i] == '+') || (input[i] == '-')) {
				while (stack.look_front_priority() >= 4) {
					output += stack.look_front_value();
					output += ' ';
					stack.del_front();
				}
				stack.push_front(input[i], 4);
			}
			else if ((input[i] == '*') || (input[i] == '/')) {
				while (stack.look_front_priority() >= 5) {
					output += stack.look_front_value();
					output += ' ';
					stack.del_front();
				}
				stack.push_front(input[i], 5);
			}
		}
		//if (!stack.empty()) cout << endl; stack.print(); cout << endl;  //вывод стека для проверки 
	}
	output += ' ';
	while (stack.empty()) {
		output += stack.look_front_value();
		output += ' ';
		stack.del_front();
	}
	return output;
}

//проверка коректности постфиксной строки
bool validPostfix_Str(string input) {
	for (int i{}; i < input.length(); ++i) {
		if (!isdigit(input[i]) && !isoperatr(input[i]) && (input[i] != '.') && (input[i] != ' ') && (input[i] != '='))
			return false;								//при вводе некорректного символа
	}
	return true;
}

//перевод из инфиксной в постфиксную
double tranferPostToNum(string input) {
	string tranferStrToDoub{};
	Stack<double> stack;
	//if (!isdigit(input[i]) && !isoperatr(input[i]) && (input[i] != '.') && (input[i] != ' '))
	for (int i{}; i < input.length(); ++i) {
		if (isdigit(input[i])) {
			while (input[i] != ' ') {
				tranferStrToDoub += input[i];
				++i;
			}
			stack.push_front(stod(tranferStrToDoub), 0);
			tranferStrToDoub.clear();
		}
		if (isactions(input[i])) {
			double current1{};
			current1 = stack.look_front_value();
			stack.del_front();
			if (input[i] == '+') {
				current1 += stack.look_front_value();
			}
			else if (input[i] == '-') {
				current1 = stack.look_front_value() - current1;
			}
			else if (input[i] == '*') {
				current1 *= stack.look_front_value();
			}
			else if (input[i] == '/') {
				if (current1 == 0) {
					cout << endl << "NOT CORRECT 0!!!" << endl;
					return 0;
				}
				current1 = stack.look_front_value() / current1;
			}
			
			stack.del_front();
			stack.push_front(current1,0);
		}
		//stack.print();
	}
	return stack.look_front_value();
}

int main() {
	/*system("chcp 1251"); */system("chcp 65001"); system("cls");
	string input{}, output{};
	double num{};
	cout << "Введите строку в инфиксном виде: ";
	cin >> input; 
	//input = "(a)+(f-b*c/(2-x)+y)/(a*r-k)";
	input = "5(1)/(5)";
	cout << endl << input << endl;
	input = upgradeInfix(input);
	cout << input << endl;
	if (validInfix_Str(input)) {
		output = tranferInfToPost(input);
		cout << endl << "строка в постфиксном виде: " << output << endl << endl;
	}
	else cout << endl << "NOT CORRECT INPUT!!!(FOR tranferInfToPost)" << endl << endl;
	if (validPostfix_Str(output)) {
		num = tranferPostToNum(output);
		cout << endl << "результат: " << num << endl << endl;
	}
	else cout << endl << "NOT CORRECT INPUT!!!(FOR tranferPostToNum)" << endl << endl;
	system("pause");
	return 0;
}