#include <iostream>
#include <cstdio>
#include <vector>
#include <time.h>

using namespace std;
using mas = vector<vector<int>>;

const int N{ 10 }; //количество пар

//создание вектора
void creatMas(mas& array) {
	array.resize(N);
	for (int i{}; i < N; ++i) {
		array[i].resize(N);
	}
}

//заполнение приоритетов мущин или женцин
void inputValunInMas(mas& array) {
	int j{}, p{};
	for (int i{}; i < N; ++i) {
		p = N-1;
		while (p!=0) {
			j = rand()%N;
			if (array[i][j] == 0) {
				array[i][j] = p;
				--p;
			}
		}
	}

}

//вывод приоритетов мущин или женцин
void printMas(mas& array) {
	for (int i{}; i < N; ++i) {
		cout << i << ": ";
		for (int j{}; j < N; ++j) {
			cout << array[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

//вывод таблицы приоритных пар
void printMasPF(mas& array) {
	cout << "M/W";
	for (int i{}; i < N; ++i) cout << i << ":\t";
	cout << endl;
	for (int i{}; i < N; ++i) {
		cout << i << ": ";
		for (int j{}; j < N; ++j) {
			cout << array[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

//вывод пар
void printMasFamily(int(&family)[N][2]) {
	cout << "M W" << endl;
	for (int i{}; i < N; ++i) {
		for (int j{}; j < 2; ++j) {
			cout << family[i][j];
			if (j == 0) cout << "-";
		}
		cout << endl;
	}
	cout << endl;
}

//построенеи таблицы приоритетов
void unionTwoMasInOne(mas& priorityFamily, mas& man, mas& woman) {
	int number{}, j{};
	for (int i{}; i < N; ++i) {
		for (int k{}; k < N; ++k){
			for (int j{}; j < N; ++j){
				if (woman[man[i][k]][j] == i) {
					number = N * 2 - k - j;
					if (number > priorityFamily[i][man[i][k]])
						priorityFamily[i][man[i][k]] = number;
					break;
				}
			}		
		}
	}

}

//определение пар и запись в отдельный массив
void findFamily(int (&family)[N][2], mas& priorityFamily) {
	int max{}, k{}, l{}, numFamily{};
	for (int n{}; n < N; ++n) {
		max = 0;
		for (int i{}; i < N; ++i) {
			for (int j{}; j < N; ++j) {
				if (priorityFamily[i][j] > max) {
					max = priorityFamily[i][j];
					k = i;
					l = j;
				}
			}
		}
		family[numFamily][0] = k;
		family[numFamily][1] = l;
		++numFamily;
		for (int i{}; i < N; ++i) priorityFamily[i][l] = 0;
		for (int j{}; j < N; ++j) priorityFamily[k][j] = 0;
	}
}

int main() {
	system("chcp 1251"); system("chcp 65001"); system("cls");
	srand((unsigned)time(0));
	mas man{}; creatMas(man); inputValunInMas(man);
	mas woman{}; creatMas(woman); inputValunInMas(woman);
	mas priorityFamily{}; creatMas(priorityFamily);
	cout << "man" << endl;
	printMas(man);
	cout << "woman" << endl;
	printMas(woman);
	unionTwoMasInOne(priorityFamily, man, woman);
	cout << "priority family" << endl;
	printMasPF(priorityFamily);
	int family[N][2]{};
	findFamily(family, priorityFamily);
	cout << "family" << endl;
	printMasFamily(family);

	system("pause");
	return 0;
}