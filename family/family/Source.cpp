#include <iostream>
#include <cstdio>
#include <vector>
#include <time.h>

using namespace std;
using mas = vector<vector<int>>;

//создание вектора
void creatMas(mas& array, int N) {
	array.resize(N);
	for (int i{}; i < N; ++i) {
		array[i].resize(N);
	}
}

//создание вектора для таблицы приоритов
void creatMasF(mas& array, int N) {
	array.resize(N);
	for (int i{}; i < N; ++i) {
		array[i].resize(2);
	}
}

//заполнение приоритетов мущин или женцин
void inputValunInMas(mas& array, int N) {
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
void printMas(mas& array, int N) {
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
void printMasPF(mas& array, int N) {
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
void printMasFamily(mas& family, int N) {
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
void unionTwoMasInOne(mas& priorityFamily, mas& man, mas& woman, int N) {
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
void findFamily(mas& family, mas& priorityFamily, int N) {
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
		for (int i{}; i < N; ++i) priorityFamily[k][i] = 0;
	}
}

//второй способ опеделения пары
void newFindFamily(mas& family, mas& man, mas& woman, int N) {
	int num{};
	for (int k{}; k < N; ++k) 
		for (int j{}; j < N; ++j) {
			for (int i{}; i < N; ++i) {
				if (man[i][0] == -1) continue;
				if (i == woman[man[i][k]][j]) {
					family[num][0] = i;
					family[num][1] = man[i][k];
					++num;
					for (int l{}; l < N; ++l) woman[man[i][k]][l] = -1;
					for (int l{}; l < N; ++l) man[i][l] = -1;
				}
			}
			if (num == N) return;
		}
}

int main() {
	system("chcp 1251"); system("chcp 65001"); system("cls");
	srand((unsigned)time(0));
	int N{};	//количество пар
	cout << "Введите количество пар: ";
	cin >> N;
	cout << endl;
	mas man{}; creatMas(man, N); inputValunInMas(man, N);
	mas woman{}; creatMas(woman, N); inputValunInMas(woman, N);
	cout << "man" << endl;
	printMas(man, N);
	cout << "woman" << endl;
	printMas(woman, N);
	cout << "1 способ: " << endl;
	mas priorityFamily{}; creatMas(priorityFamily, N);
	mas family{}; creatMasF(family, N);
	unionTwoMasInOne(priorityFamily, man, woman, N);
	cout << endl << "priority family" << endl;
	printMasPF(priorityFamily, N);
	findFamily(family, priorityFamily, N);
	cout << "family" << endl;
	printMasFamily(family, N); 
	cout << "2 способ: " << endl;	
	newFindFamily(family, man, woman, N);
	cout << "man" << endl;
	printMas(man, N);
	cout << "woman" << endl;
	printMas(woman, N);
	cout << "family" << endl;
	printMasFamily(family, N);
	system("pause");
	return 0;
}