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

//определение пар и запись в отдельный массив краткий анализ
void shortFindFamily(mas& family, mas& priorityFamily, int N) {
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

//определение пар и запись в отдельный массив полный анализ
int fullFindFamily(mas& family, mas& priorityFamily, int priority, bool check, bool checkRec, int N) {
	int max{}, m{}, w{}, numFamily{}, sumMax{}, sumPriority{ priority };
	for (int n{}; n < N; ++n) {
		max = 0;
		for (int i{}; i < N; ++i) {
			for (int j{}; j < N; ++j) {
				if ((priorityFamily[i][j] == max) && (check)) ++sumMax;
				if (priorityFamily[i][j] > max) {
					max = priorityFamily[i][j];
					sumMax = 0;
					m = i;
					w = j;
				}
			}
		}
		cout << sumMax << endl;
		if (sumMax > 1) {
			int* array = new int [sumMax + 1];
			int maxArray{}, numI{};
			vector<mas> masCopFamily{};	masCopFamily.resize(sumMax + 1);	//создаем трехмерный массив с копиями массива priorityFamily		
			vector<mas> masCopPriorityFamily{}; masCopPriorityFamily.resize(sumMax + 1);
			for (int k{}; k < N; ++k) {
				creatMasF(masCopFamily[k], N);
				creatMas(masCopPriorityFamily[k], N);
				masCopFamily[k] = family; 
				masCopPriorityFamily[k] = priorityFamily;
				for (int i{}; i < N; ++i) {
					for (int j{}; j < N; ++j) {
						printMasPF(masCopPriorityFamily[k], N);
						if (masCopPriorityFamily[k][i][j] == max) {
							m = i;
							w = j;
							masCopFamily[k][numFamily][0] = m;
							masCopFamily[k][numFamily][1] = w;
							++numFamily;
							for (int i{}; i < N; ++i) masCopPriorityFamily[k][i][w] = 0;
							for (int i{}; i < N; ++i) masCopPriorityFamily[k][m][i] = 0; 
							printMasPF(priorityFamily, N);
							printMasPF(masCopPriorityFamily[k], N);
							array[k] = fullFindFamily(masCopFamily[k], masCopPriorityFamily[k], sumPriority + max, false, false, N); //доделать(
							if (array[k] > maxArray) {
								maxArray = array[k];
								numI = k;
							}
							++k;
							creatMasF(masCopFamily[k], N);
							creatMas(masCopPriorityFamily[k], N);
							masCopFamily[k] = family;
							masCopPriorityFamily[k] = priorityFamily;
						}
					}
				}
				priorityFamily = masCopPriorityFamily[numI];
				family = masCopFamily[numI];
				return maxArray;
			}
			family = masCopFamily[numI];
			priorityFamily = masCopPriorityFamily[numI];
		}
		else {
			sumPriority += max;
			family[numFamily][0] = m;
			family[numFamily][1] = w;
			++numFamily;
			for (int i{}; i < N; ++i) priorityFamily[i][w] = 0;
			for (int i{}; i < N; ++i) priorityFamily[m][i] = 0;
		}
		if (numFamily == N) return sumPriority;
		if (checkRec) check = true;
	}
	return sumPriority;
}


//второй способ опеделения пары
void newFindFamily(mas& family, mas& man, mas& woman, int N) {
	int numFamily{};
	for (int k{}; k < N; ++k) 
		for (int j{}; j < N; ++j) {
			for (int i{}; i < N; ++i) {
				if (man[i][0] == -1) continue;
				if (i == woman[man[i][k]][j]) {
					family[numFamily][0] = i;
					family[numFamily][1] = man[i][k];
					++numFamily;
					for (int l{}; l < N; ++l) woman[man[i][k]][l] = -1;
					for (int l{}; l < N; ++l) man[i][l] = -1;
				}
			}
			if (numFamily == (N - 1))
				for (int i{}; i < N; ++i) 
					if (man[i][0] != -1)
						for (int p{}; p < N; ++p) 
							if (woman[p][0] != -1) {
								family[numFamily][0] = i;
								family[numFamily][1] = p;
								++numFamily;
								for (int l{}; l < N; ++l) woman[p][l] = -1;
								for (int l{}; l < N; ++l) man[i][l] = -1;
								return;
							}						
			if (numFamily == N) return; 
			if ((k + 1) == j) break;
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
	//shortFindFamily(family, priorityFamily, N);
	fullFindFamily(family, priorityFamily, 0, false, true, N);
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