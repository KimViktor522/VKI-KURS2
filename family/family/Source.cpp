#include <iostream>
#include <cstdio>
#include <vector>
#include <time.h>

using namespace std;
using mas = vector<vector<int>>;

const int N{ 5 };

void creatMas(mas& array) {
	array.resize(N);
	for (int i{}; i < N; ++i) {
		array[i].resize(N);
	}
}

void inputValunInMas(mas& array) {
	int j{}, p{};
	for (int i{}; i < N; ++i) {
		p = 4;
		while (p!=0) {
			j = rand() % N;
			if (array[i][j] == 0) {
				array[i][j] = p;
				--p;
			}
		}
	}

}

void printMas(mas& array) {
	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			cout << array[i][j] << "\t";
		}
		cout << endl;
	}
}

void unionTwoMasInOne(mas& family, mas& man, mas& woman) {
	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			//family[i][j] = man[i][j] + woman[i][j];
		}
	}
}

int main() {
	system("chcp 1251"); system("chcp 65001"); system("cls");
	srand((unsigned)time(0));
	mas man{}; creatMas(man); inputValunInMas(man);
	mas woman{}; creatMas(woman); inputValunInMas(woman);
	mas family{}; creatMas(family);
	printMas(man);
	cout << endl;
	printMas(woman);
	cout << endl; 
	unionTwoMasInOne(family, man, woman);
	printMas(family);

	system("pause");
	return 0;
}