#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

using namespace std;

int main() {
	ifstream inputFail;	inputFail.open("input.txt");
	ofstream outputFail; outputFail.open("output.txt");
	if (!inputFail.is_open() || !outputFail.is_open()) {
		cerr << "Error opening file!" << endl;
	}
	else {
		string str{}, tranferStrToInt{}, firstStr{};
		int num{ 0 }, size{ 0 };
		bool checkFirst{}, checkSkip{}/*проверяет удовлетворяет ли условию*/;
		getline(inputFail, str);
		for (int i{}; i < (int)str.length(); ++i) {
			if ((i == (int)str.length()) || (str[i] != ' ')) {
				while ((i != (int)str.length()) && (str[i] != ' ')) {
					for (int k{}; k < size; ++k) {
						if (str[i] == firstStr[k]) {
							checkSkip = true;
							break;
						}
					}
					tranferStrToInt += str[i];
					++i;
				}
				if ((checkSkip == false) && (checkFirst == true)) {
					outputFail << tranferStrToInt << endl;
					cout << tranferStrToInt << endl;
				}
				if (checkFirst == false) { // если первое слово 
					firstStr = str;
					size = i;
					checkFirst = true;
				}
				++num;
				checkSkip = false;
				tranferStrToInt.clear();
			}
		}
	}
	inputFail.close();
	outputFail.close();
	return 0;
}