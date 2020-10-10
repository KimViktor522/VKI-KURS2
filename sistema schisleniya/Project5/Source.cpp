#include <iostream>
#include <cstdio>
#include <string.h>
#include <cmath>


using namespace std;

char str[1000] = { 0 }, intStr[1000] = { 0 }, doubleStr[1000] = { 0 };

int main() {
	int beginSof = 0, endSof = 0; // scale of notation										nachalnya i konechnaya sistema schisleniya
	cout << "string: ";
	cin >> str;
	cout << "\nbeginSof: ";
	cin >> beginSof;
	cout << "\nendSof: ";
	cin >> endSof; 
	bool point = false;
	int nPoint = 0; //poziciya tochki
	for (int i = 0; i < strlen(str); i++) {													//proverka na ne celuy chast
		if (((int)str[i] == 46) || ((int)str[i] == 44)) { //46="." 44=","
			nPoint = i;
			point = true;
			break;
		}
	}
	for (int i = 0; i < strlen(str); i++) {													//proverka
		if (point == false) {//proverka esli net '.' ili ','																
			for (int i = 0; i < strlen(str); i++) {
				if (((int)str[i] > 64) && ((int)str[i] < 91)) {// ot A...  ...Z
					if ((int)str[i] >= (beginSof + 55)) {
						cout << "NOT CORRECT!\n";
						system("pause");
						return 0;
					}
				}
				else if (((int)str[i] > 47) && ((int)str[i] < 58)){// ot 0... ...9
					if ((int)str[i] >= (beginSof + 48)) {
						cout << "NOT CORRECT!\n";
						system("pause");
						return 0;
					}
				}
					else {//neizvestni simvol
						cout << "NOT CORRECT!\n";
						system("pause");
						return 0;
					}
			}
		}
		else if (point == true) {//proverka esli est '.' ili ','	
			for (int i = 0; i < strlen(str); i++) {
				if (i < nPoint) {//celoe
					if (((int)str[i] > 64) && ((int)str[i] < 91)) {// ot A...  ...Z
						if ((int)str[i] >= (beginSof + 55)) {
							cout << "NOT CORRECT!\n";
							system("pause");
							return 0;
						}
					}
					else if (((int)str[i] > 47) && ((int)str[i] < 58)) {// ot 0... ...9
							if ((int)str[i] >= (beginSof + 48)) {
								cout << "NOT CORRECT!\n";
								system("pause");
								return 0;
							}
					}
						else {//neizvestni simvol
							cout << "NOT CORRECT!\n";
							system("pause");
							return 0;
						}
				}
				else if (i > nPoint) {//drobnoe
						if (((int)str[i] > 64) && ((int)str[i] < 91)) {// ot A...  ...Z
							if ((int)str[i] >= (beginSof + 55)) {
								cout << "NOT CORRECT!\n";
								system("pause");
								return 0;
							}
						}
						else if (((int)str[i] > 47) && ((int)str[i] < 58)) {// ot 0... ...9
							if ((int)str[i] >= (beginSof + 48)) {
								cout << "NOT CORRECT!\n";
								system("pause");
								return 0;
							}
						}
							else {//neizvestni simvol
								cout << "NOT CORRECT!\n";
								system("pause");
								return 0;
							}
						
				}
			}
		}
	}
	long double nomber = 0,doubnomber = 0; //chislo v 10 sisteme
	if (point == true)																		//perevod iz beginSof v 10 sistemu
		for (int i = 0; i < strlen(str); i++) {
			if (i < nPoint) {//do tochki
				if (((int)str[i] > 64) && ((int)str[i] < 91)) { // ot A...  ...Z
					nomber += (((long double)(str[i]) - 55) * pow((long double)beginSof, ((long double)(nPoint - 1 - i))));
				}
				if (((int)str[i] > 47) && ((int)str[i] < 58)) {// ot 0... ...9
					nomber += (((long double)(str[i]) - 48) * pow((long double)beginSof, ((long double)(nPoint - 1 - i))));
				}
				//cout << nomber << "   +" << (((long double)(str[i]) - 48) * pow((long double)beginSof, ((long double)(nPoint - 1 - i)))) << "   " << (int)str[i] << "   " << str[i] << "   " << (nPoint - 1 - i) << "   " << pow((long double)beginSof, ((long double)(nPoint - 1 - i))) << "\n";
			}
			else if (i > nPoint) {
				if (((int)str[i] > 64) && ((int)str[i] < 91)) { // ot A...  ...Z
					doubnomber += (((long double)(str[i]) - 55) * pow((long double)beginSof, ((long double)(-(i - nPoint)))));
				}
				if (((int)str[i] > 47) && ((int)str[i] < 58)) {// ot 0... ...9
					doubnomber += (((long double)(str[i]) - 48) * pow((long double)beginSof, ((long double)(-(i - nPoint)))));
				}
			}
			//cout << nomber <<  doubnomber << "   +" << (((long double)(str[i]) - 48) * pow((long double)beginSof, ((long double)(-(i - nPoint - 1))))) << "   " << (int)str[i] << "   " << str[i] << "   " << -(i - nPoint) << "   " << pow((long double)beginSof, ((long double)(-(i - nPoint)))) << "\n";
		}
	else if (point == false)
		for (int i = 0; i < strlen(str); i++) {													
			if (((int)str[i] > 64) && ((int)str[i] < 91)) { // ot A...  ...Z
				nomber += (((long double)(str[i]) - 55) * pow((long double)beginSof, (long double)(strlen(str) - i - 1)));
			}
			if (((int)str[i] > 47) && ((int)str[i] < 58)) {// ot 0... ...9
				nomber += (((long double)(str[i]) - 48) * pow((long double)beginSof, ((long double)(strlen(str) - i - 1))));
			}
			//cout << nomber << "   " << (int)str[i] << "   " << str[i] << "   " << ((strlen(str)) - i - 1) << "   " << pow((long double)beginSof, ((long double)strlen(str)) - i - 1) << "\n";
		}
	cout << "\n" << nomber << doubnomber << " [10]   .=" << nPoint << "\n\n";
	cout << str << " [" << beginSof << "]" << " = ";
	int k = 0, j = 0;
	long long int intNomber = nomber;//celoe
	while (intNomber>=1){																		//perevod iz 10 v endSof sistemu (celoe)
		if (((intNomber % endSof)>=0) && ((intNomber % endSof) < 10))
			intStr[k] = (char)((intNomber % endSof) + 48);
		if (((intNomber % endSof) >= 10) && ((intNomber % endSof) < 36))
			intStr[k] = (char)((intNomber % endSof) + 55);
		intNomber /= endSof;
		k++;
	}
	for (int i = strlen(intStr); i > 0; i--) {//vivod celogo
		cout << intStr[i-1];
	}
	if (point == true) {																		
		long long int intdoubleNomber = doubnomber * pow(10,10);//perevod drobnova v celoe dlya vivoda
		while (intdoubleNomber%10==0){//udalenie lishnix nulei
			intdoubleNomber /= 10;
			//cout << intdoubleNomber << "   " << (nomber - (int)nomber) * pow(10, 10) << "   " << pow(10, 10) << "   " << "\n";
		}
		while (intdoubleNomber >=1){
			if (((intdoubleNomber % endSof) >= 0) && ((intdoubleNomber % endSof) < 10))			//perevod iz 10 v endSof sistemu (drobnoe)
				doubleStr[j] = (char)((intdoubleNomber % endSof) + 48);
			if (((intdoubleNomber % endSof) >= 10) && ((intdoubleNomber % endSof) < 36))
				doubleStr[j] = (char)((intdoubleNomber % endSof) + 55);
			//cout << j << "   " << doubleStr << "   " << (intdoubleNomber % endSof) << "   " << (intdoubleNomber / endSof) << "   " << "\n";
			intdoubleNomber /= endSof;
			j++;
		}
		cout << ".";
		for (int i = strlen(doubleStr); i > 0; i--) {//vivod celogo
			cout << doubleStr[i-1];
		}
	}
	cout << " [" << endSof << "]" << "\n\n";
	system("pause");
	return 0;
}