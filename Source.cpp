#include "Basics.h"
#include "Sort.h"
#include "User.h"
#include "Route.h"
using namespace std;
const short x_s = 1076, y_s = 1076, z_s = 31; // ðàçìåð ìàññèâà äëÿ òàáëèöû ðàññòîÿíèé
const short s_s = 1076, t_s = 5, m_s = 31; // ðàçìåð ìàññèâà äëÿ ñîîòíîøåíèÿ ãîðîäîâ è ñóáúåêòîâ ÐÔ
char AA[x_s][y_s][z_s], /* Òàáëèöà ðàññòîÿíèé */ BB[s_s][t_s][m_s], /* Ñîîòíîøåíèå ãîðîäîâ è ñóáúåêòîâ ÐÔ */ towndep[m_s], townarr[m_s]; /* Ãîðîäà îòïðàâëåíèÿ è íàçíà÷åíèÿ */
int Distances[x_s][y_s];
User user; // Ïåðåìåííàÿ õðàíèò ïîëíóþ õàðàêòåðèñòèêó àêêàóíòà
bool Kontrolname(char name[]) { // Êîíòðîëü íà äîïóñòèìîñòü íàçâàíèÿ êîìïàíèè
	if (strlen(name) >= 2 && strlen(name) <= 30) {
		if (name[0] < -64 || (name[0] >= 0 && name[0] <= 63) || (name[0] >= 91 && name[0] <= 96)) return false;
		for (int i = 1; i < strlen(name); i++) {
			if (name[i] == 59) return false;
			if (name[i] == 32) return false;
		}
		return true;
	}
	return false;
}
bool Kontrolpassword(char password[]) { // Êîíòðîëü íà äîïóñòèìîñòü ïàðîëÿ
	if (strlen(password) >= 8 && strlen(password) <= 30) {
		for (int i = 0; i < strlen(password); i++) {
			if (password[i] <= 36 || (password[i] >= 38 && password[i] <= 41) || (password[i] >= 43 && password[i] <= 44) || (password[i] >= 46 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || (password[i] >= 91 && password[i] <= 96)) return false; // Êîòîðûå èñêëþ÷àåì
		}
		bool b = false; // Ïðîâåðêà íàëè÷èÿ ñïåöèàëüíûõ ñèìâîëîâ
		for (int i = 0; i < strlen(password); i++) {
			if (password[i] >= 65 && password[i] <= 90) b = true;
		}
		if (b == false) return false;
		b = false;
		for (int i = 0; i < strlen(password); i++) {
			if (password[i] >= 97 && password[i] <= 122) b = true;
		}
		if (b == false) return false;
		b = false;
		for (int i = 0; i < strlen(password); i++) {
			if (password[i] >= 48 && password[i] <= 57) b = true;
		}
		if (b == false) return false;
		b = false;
		for (int i = 0; i < strlen(password); i++) {
			if (password[i] == 45 || password[i] == 37 || password[i] == 42) b = true;
		}
		if (b == false) return false;
		return true;
	}
	return false;
}
void Zachiv(char A[], int step) { // Øèôð Öåçàðÿ
	int C = strlen(A); bool m = false;
	for (int i = 0; i < C; i++) {
		m = false;
		if (A[i] + step == -104) {
			A[i] = -133; m = true;
		}
		else if (A[i] == -133) {
			A[i] = step - 104; m = true;
		}
		else if (A[i] + step == -96) {
			A[i] = -132; m = true;
		}
		else if (A[i] == -132) {
			A[i] = step - 96; m = true;
		}
		else if (A[i] + step == 59) {
			A[i] = -98; m = true;
		}
		else if (A[i] == -98) {
			A[i] = step + 59; m = true;
		}
		for (short j = 0, k = -131; j <= 27; j++, k++) {
			if (A[i] + step == j) {
				A[i] = k; m = true;
			}
			else if (A[i] == k) {
				A[i] = step + j; m = true;
			}
		}
		for (short j = 28, k = -103; j <= 32; j++, k++) {
			if (A[i] + step == j) {
				A[i] = k; m = true;
			}
			else if (A[i] == k) {
				A[i] = step + j; m = true;
			}
		}
		if (m == false) A[i] += step;
	}
}
void Outuser() { // Ïðîöåäóðà âûâîäèò íà ýêðàí âñþ èíôîðìàöèþ î ïîëüçîâàòåëå (ïðè íàæàòèè êíîïêè 1)
	system("cls");
	if (user.getName(0) != 0) {
		cout << "Íàçâàíèå àêêàóíòà: ";
		for (int i = 0; i < 30; i++) {
			cout << user.getName(i);
		}
		cout << endl;
		for (int i = 0; i < 30; i++) cout << "-";
		cout << endl;
		for (int i = 0; i < 5; i++) {
			if (user.getNomber(i, 0) != 0) {
				cout << "Àâòîìîáèëü ¹ " << i + 1 << endl;
				cout << "Ãîñíîìåð: ";
				for (int j = 0; j < 9; j++) cout << user.getNomber(i, j);
				cout << endl;
				cout << "Ãðóçîïîäú¸ìíîñòü: " << user.getTonnage(i) << " êã" << endl;
				cout << "Ðàñõîä òîïëèâà: " << user.getRate(i) << " ë/100 êì" << endl;
				cout << "Îáú¸ì áàêà: " << user.getTank(i) << " ë" << endl;
			}
			else if (i == 0) cout << "ÀÂÒÎÏÀÐÊ ÏÓÑÒÎÉ" << endl;
		}
	}
	else {
		cout << "Âõîä â àêêàóíò íå âûïîëíåí" << endl;
	}
	for (int i = 0; i < 30; i++) cout << "-";
	cout << endl;
	system("pause");
}
void Enter() { // Àâòîðèçàöèÿ óæå çàðåãèñòðèðîâàííûõ ïîëüçîâàòåëåé
	system("cls");
	char A[20][28][31];
	ifstream tin("Your address/Users.txt");
	int s = 0, t = 0, m = 0;
	while (tin.good()) {
		tin >> A[s][t][m];
		if (A[s][t][m] != 59) m++;
		else {
			t++; m = 0;
		}
		if (t == 28) {
			s++; t = 0;
		}
	}
	tin.close();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 28; j++) {
			short x = 0;
			if (A[i][j][1] == -52 && (j == 3 || j == 4 || j == 5 || j == 6 || j == 7)) x = 1;
			for (int k = 0; k < 31; k++) {
				if ((A[i][j][k] == -52 && (x == 1 || k >= 9 || (j != 3 && j != 4 && j != 5 && j != 6 && j != 7))) || A[i][j][k] == 59) A[i][j][k] = 0;
			}
		}
	}
	int secret_code_l[20][4];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 4; j++) {
			if (A[i][2][j] >= 48 && A[i][2][j] <= 57) secret_code_l[i][j] = A[i][2][j] - 48;
		}
	}
	int secret_code[20];
	for (int i = 0; i < 20; i++) secret_code[i] = secret_code_l[i][0] * 1000 + secret_code_l[i][1] * 100 + secret_code_l[i][2] * 10 + secret_code_l[i][3];
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 2; j++) {
			Zachiv(A[i][j], secret_code_l[i][1] + secret_code_l[i][3]);
		}
	}
	string name_s, password_s; int secret_code_s; char name[30], password[30];
	do {
		system("cls");
		cout << "Ââåäèòå íàçâàíèå ó÷¸òíîé çàïèñè: "; getline(cin, name_s);
	} while (size(name_s) == 0);
	for (int i = 0; i < size(name_s); i++) {
		if (i < 30) name[i] = name_s[i];
	}
	if (size(name_s) < 30) name[size(name_s)] = 0;
	else name[29] = 0;
	for (int i = 0; i < 20; i++) {
		if (str_copy(A[i][0], name) == true) {
			cout << "Ââåäèòå ïàðîëü: "; getline(cin, password_s);
			for (int j = 0; j < size(password_s); j++) {
				if (j < 30) password[j] = password_s[j];
			}
			if (size(password_s) < 30) password[size(password_s)] = 0;
			else password[29] = 0;
			if (str_copy(A[i][1], password) == true) {
				for (int h = 0; h < 30; h++) {
					if (name[h] == -52 && h != 0) name[h] = 0;
					user.setName(name[h], h);
				}
				for (int h = 0; h < 30; h++) user.setPassword(A[i][1][h], h);
				user.setCode(secret_code[i]);
				cout << "Âû âîøëè â àêêàóíò" << endl; system("pause");
				// Ñ÷èòûâàíèå âñåé èíôîðìàöèè îá àêêàóíòå
				for (int y = 3; y < 8; y++) { // ñ÷èòûâàåì ãîñíîìåð
					for (int z = 0; z < 9; z++) user.setNomber(A[i][y][z], y - 3, z);
				}
				for (int y = 8; y < 13; y++) { // ãðóçîïîäú¸ìíîñòü
					char tonn[5]{ 0,0,0,0,0 }; int tonnage = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) tonnage = tonn[0] - 48;
					else if (tonn[2] == 0) tonnage = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) tonnage = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) tonnage = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else tonnage = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setTonnage(tonnage, y - 8);
				}
				for (int y = 13; y < 18; y++) { // îáú¸ì áàêà
					char tonn[5]{ 0,0,0,0,0 }; int tank = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) tank = tonn[0] - 48;
					else if (tonn[2] == 0) tank = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) tank = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) tank = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else tank = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setTank(tank, y - 13);
				}
				for (int y = 18; y < 23; y++) { // ðàñõîä òîïëèâà
					char tonn[5]{ 0,0,0,0,0 }; int rate = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) rate = tonn[0] - 48;
					else if (tonn[2] == 0) rate = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) rate = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) rate = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else rate = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setRate(rate, y - 18);
				}
				for (int y = 23; y < 28; ++y) {
					string across = A[i][y];
					user.setNom(converter(across), y - 23);
				}
				for (int j = 0; j < 5; ++j) {
					if (user.getNom(j) != 0) ++user.CountCar;
				}
				return;
			}
			cout << "Ââåä¸í íåâåðíûé ïàðîëü\nÂâåäèòå ñåêðåòíûé êîä: "; (cin >> secret_code_s).get(); // ×òîáû ïîñëå getline âñ¸ íîðìàëüíî ÷èòàë
			if (secret_code[i] == secret_code_s) {
				for (int h = 0; h < 30; h++) {
					if (name[h] == -52 && h != 0) name[h] = 0;
					user.setName(name[h], h);
				}
				for (int h = 0; h < 30; h++) user.setPassword(A[i][1][h], h);
				user.setCode(secret_code[i]);
				cout << "Âû âîøëè â àêêàóíò" << endl; system("pause");
				// Ñ÷èòûâàíèå âñåé èíôîðìàöèè îá àêêàóíòå
				for (int y = 3; y < 8; y++) { // ñ÷èòûâàåì ãîñíîìåð
					for (int z = 0; z < 9; z++) user.setNomber(A[i][y][z], y - 3, z);
				}
				for (int y = 8; y < 13; y++) { // ãðóçîïîäú¸ìíîñòü
					char tonn[5]{ 0,0,0,0,0 }; int tonnage = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) tonnage = tonn[0] - 48;
					else if (tonn[2] == 0) tonnage = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) tonnage = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) tonnage = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else tonnage = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setTonnage(tonnage, y - 8);
				}
				for (int y = 13; y < 18; y++) { // îáú¸ì áàêà
					char tonn[5]{ 0,0,0,0,0 }; int tank = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) tank = tonn[0] - 48;
					else if (tonn[2] == 0) tank = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) tank = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) tank = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else tank = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setTank(tank, y - 13);
				}
				for (int y = 18; y < 23; y++) { // ðàñõîä òîïëèâà
					char tonn[5]{ 0,0,0,0,0 }; int rate = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) rate = tonn[0] - 48;
					else if (tonn[2] == 0) rate = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) rate = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) rate = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else rate = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setRate(rate, y - 18);
				}
				for (int y = 23; y < 28; ++y) {
					string across = A[i][y];
					user.setNom(converter(across), y - 23);
				}
				for (int j = 0; j < 5; ++j) {
					if (user.getNom(j) != 0) ++user.CountCar;
				}
				return;
			}
			cout << "Ââåä¸í íåâåðíûé ñåêðåòíûé êîä" << endl; system("pause"); return;
		}
	}
	cout << "Òàêîé ó÷¸òíîé çàïèñè íåò â áàçå äàííûõ" << endl; system("pause"); return;
}
void Registr() { // Ðåãèñòðàöèÿ ïîëüçîâàòåëÿ
	char A = 0, choise = 0, name[1000], password[1000];
	do {
		do {
			A = 0; choise = 0;
			system("cls");
			cout << "Íàçâàíèå ó÷¸òíîé çàïèñè äîëæíî èìåòü îò 2 äî 30 ñèìâîëîâ (âêëþ÷èòåëüíî)\nÍå äîëæíî áûòü ñèìâîëà \";\"\nÏðîáåëû íå äîïóñêàþòñÿ" << endl << "Ââåäèòå íàçâàíèå: "; cin.getline(name, 1000);
			while (Kontrolname(name) == false) {
				system("cls");
				cout << "Òàêîå íàçâàíèå íå äîïóñêàåòñÿ.\nÎíî äîëæíî èìåòü îò 2 äî 30 ñèìâîëîâ (âêëþ÷èòåëüíî)\nÍå äîëæíî áûòü ñèìâîëà \";\"\nÏðîáåëû íå äîïóñêàþòñÿ" << endl << "Ââåäèòå íàçâàíèå: "; cin.getline(name, 1000);
			}
			char B[20][28][31];
			ifstream tin("Your address/Users.txt");
			int s = 0, t = 0, m = 0;
			while (tin.good()) {
				tin >> B[s][t][m];
				if (B[s][t][m] != 59) m++;
				else {
					t++; m = 0;
				}
				if (t == 28) {
					s++; t = 0;
				}
			}
			tin.close();
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 28; j++) {
					short x = 0;
					if (B[i][j][1] == -52 && (j == 3 || j == 4 || j == 5 || j == 6 || j == 7)) x = 1;
					for (int k = 0; k < 31; k++) {
						if ((B[i][j][k] == -52 && (x == 1 || k >= 9 || (j != 3 && j != 4 && j != 5 && j != 6 && j != 7))) || B[i][j][k] == 59) B[i][j][k] = 0;
					}
				}
			}
			int secret_code_l[20][4];
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 4; j++) {
					if (B[i][2][j] >= 48 && B[i][2][j] <= 57) secret_code_l[i][j] = B[i][2][j] - 48;
				}
			}
			int secret_code[20];
			for (int i = 0; i < 20; i++) secret_code[i] = secret_code_l[i][0] * 1000 + secret_code_l[i][1] * 100 + secret_code_l[i][2] * 10 + secret_code_l[i][3];
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 2; j++) {
					Zachiv(B[i][j], secret_code_l[i][1] + secret_code_l[i][3]);
				}
			}
			name[0] = toupper(name[0]);
			short p = 0; // Êîíòðîëüíàÿ ïåðåìåííàÿ (ïîâòîð èìåíè)
			for (int i = 0; i < 20; i++) {
				if (str_copy(B[i][0], name) == true) {
					cout << "Ïîëüçîâàòåëü ñ òàêèì èìåíåì óæå ñóùåñòâóåò" << endl; p = 1; break;
				}
			}
			if (p == 1) {
				system("pause"); A = 50; continue;
			}
			cout << "Íàçâàíèå çàïèñàíî" << endl;
			system("pause"); system("cls");
			cout << "Ïàðîëü äîëæåí èìåòü îò 8 äî 30 ñèìâîëîâ (âêëþ÷èòåëüíî)\nÂñå áóêâû àíãëèéñêèå\nÕîòÿ áû 1 çàãëàâíàÿ áóêâà, 1 ïðîïèñíàÿ, 1 öèôðà, 1 ñèìâîë \"-\", \"%\" èëè \"*\"" << endl << "Ïðèäóìàéòå ïàðîëü: "; cin.getline(password, 1000);
			while (Kontrolpassword(password) == false) {
				system("cls");
				cout << "Òàêîé ïàðîëü íå äîïóñêàåòñÿ.\nÎí äîëæåí èìåòü îò 8 äî 30 ñèìâîëîâ (âêëþ÷èòåëüíî)\nÂñå áóêâû àíãëèéñêèå\nÕîòÿ áû 1 çàãëàâíàÿ áóêâà, 1 ïðîïèñíàÿ, 1 öèôðà, 1 ñèìâîë \"-\", \"%\" èëè \"*\"" << endl << "Ïðèäóìàéòå ïàðîëü: "; cin.getline(password, 1000);
			}
			cout << "Ïàðîëü çàïèñàí" << endl;
			system("pause"); system("cls");
			cout << "1. Ïîäòâåäèòü ïàðîëü" << endl << "2. Ñáðîñèòü ïîëÿ ðåãèñòðàöèè" << endl << "3. ß ïåðåäóìàë ðåãèñòðèðîâàòüñÿ" << endl << "Âûáåðèòå äåéñòâèå: "; A = _getch(); cout << endl;
			while (A != 49 && A != 50 && A != 51) {
				cout << "Îøèáêà. Ïîâòîðèòå ïîïûòêó:\n1. Ïîäòâåäèòü ïàðîëü\n2. Ñáðîñèòü ïîëÿ ðåãèñòðàöèè\n3. ß ïåðåäóìàë ðåãèñòðèðîâàòüñÿ\nÂûáåðèòå äåéñòâèå: "; A = _getch(); cout << endl;
			}
			if (A == 51) return;
		} while (A == 50);
		char cpy_password[1000];
		cout << "Ïîäòâåðäèòå ïàðîëü: "; cin.getline(cpy_password, 1000);
		while (str_copy(cpy_password, password) == false && choise != 50) {
			system("cls"); cout << "Ïàðîëè íå ñîâïàäàþò\n1. Ïîäòâåðäèòü ïàðîëü\n2. Ñáðîñèòü ïîëÿ ðåãèñòðàöèè\n3. ß ïåðåäóìàë ðåãèñòðèðîâàòüñÿ\nÂûáåðèòå äåéñòâèå: "; choise = _getch(); cout << endl;
			while (choise != 49 && choise != 50 && choise != 51) {
				system("cls"); cout << "Îøèáêà. Ïîâòîðèòå ïîïûòêó:\n1. Ïîäòâåäèòü ïàðîëü\n2. Ñáðîñèòü ïîëÿ ðåãèñòðàöèè\n3. ß ïåðåäóìàë ðåãèñòðèðîâàòüñÿ\nÂûáåðèòå äåéñòâèå: "; choise = _getch(); cout << endl;
			}
			if (choise == 51) return;
			if (choise == 49) {
				cout << "Ïîäòâåðäèòå ïàðîëü: "; cin.getline(cpy_password, 1000);
			}
		}
	} while (choise == 50);
	int secret_code[4];
	srand(time(NULL));
	for (int i = 0; i < 4; i++) {
		secret_code[i] = rand() % 9;
		if (secret_code[0] == 0) i--;
	}
	int secret_code_s = secret_code[0] * 1000 + secret_code[1] * 100 + secret_code[2] * 10 + secret_code[3];
	int step = -(secret_code[1] + secret_code[3]); // Øàã ïðè øèôðîâàíèè Öåçàðÿ ðàâåí ïðîòèâîïîëîæíîé ñóììå 1-é è 3-é öèôðû ñåêðåòíîãî êîäà (íà÷èíàÿ ñ íóëÿ)
	Zachiv(name, step); Zachiv(password, step); // +step - çàøèôðîâàòü
	ofstream lin("Your address/Users.txt", ios::app);
	lin << endl;
	for (int i = 0; i < strlen(name); i++) lin << name[i];
	lin << ";";
	for (int i = 0; i < strlen(password); i++) lin << password[i];
	lin << ";" << secret_code_s << ";";
	lin << ";;;;;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;";
	lin.close();
	system("cls");
	Zachiv(name, -step); Zachiv(password, -step); // -step - ðàñøèôðîâàòü
	cout << "Áëàãîäàðèì çà ðåãèñòðàöèþ â ïðîãðàììå \"Ëîãèñò\"" << endl << "Ïîëüçîâàòåëü ñ èìåíåì " << name << " ñîõðàí¸í." << endl << "Âàø ñåêðåòíûé êîä: " << secret_code_s << ". Èñïîëüçóéòå åãî, åñëè çàáóäåòå ïàðîëü." << endl << "Ïðåäëàãàåì âîéòè â àêêàóíò çàíîâî, ÷òîáû óáåäèòüñÿ, ÷òî Âû çíàåòå ñâîé ïàðîëü." << endl; system("pause"); Enter();
}
void Hello() { // Ñ ýòîãî íà÷èíàåòñÿ èñïîëíåíèå ïðîãðàììû (ïðèâåòñòâåííîå ñîîáùåíèå)
	char A;
	do {
		cout << "Äîáðî ïîæàëîâàòü â ïðîãðàììó \"Ëîãèñò\"" << endl << "1. Âîéòè â àêêàóíò" << endl << "2. Ðåãèñòðàöèÿ" << endl << "Âàø âûáîð: "; A = _getch(); cout << endl;
		if (A == 49) Enter();
		else if (A == 50) Registr();
		else {
			cout << "Îøèáêà. Ââåäèòå òîëüêî ÷èñëî - 1 èëè 2" << endl; system("pause");
		}
		system("cls");
	} while (A != 49 && A != 50);
}
void Files() {  // Çàãðóæàåò ñëóæåáíóþ èíôîðìàöèþ (Towns.txt, Distances.txt)
	ifstream lin("Your address/Towns.csv");
	int x = 0, y = 0, z = 0;
	while (lin.good()) {
		lin >> BB[x][y][z];
		if (BB[x][y][z] != 59) z++;
		else {
			y++; z = 0;
		}
		if (y == t_s) {
			x++; y = 0;
		}
	}
	for (int i = 0; i < s_s; i++) {
		for (int j = 0; j < t_s; j++) {
			for (int k = 0; k < m_s; k++) {
				if ((BB[i][j][k] == -52 && k != 0 && BB[i][j][k - 1] != '-') || BB[i][j][k] == 59) BB[i][j][k] = 0;
				BB[i][j][k] = tolower(BB[i][j][k]);
			}
		}
	}
	lin.close();
	ifstream in("Your address/Distances.csv");
	int s = 0, t = 0, m = 0;
	while (in.good()) {
		in >> AA[s][t][m];
		if (AA[s][t][m] != 59) m++;
		else {
			t++; m = 0;
		}
		if (t == y_s) {
			s++; t = 0;
		}
	}
	for (int i = 0; i < x_s; i++) {
		for (int j = 0; j < y_s; j++) {
			for (int k = 0; k < z_s; k++) {
				if (AA[i][j][k] == -52 || AA[i][j][k] == 59) AA[i][j][k] = 0;
				tolower(AA[i][j][k]);
			}
		}
	}
	for (int i = 0; i < x_s; ++i) {  // Ïðåâðàùàåì ìàññèâ ñèìâîëîâ â ìàññèâ ÷èñåë
		for (int j = 0; j < y_s; ++j) {
			string via = AA[i][j];
			Distances[i][j] = converter(via);
		}
	}
	in.close();
}
void Towndeparr(int x) {  // Âûáîð äâóõ ãîðîäîâ (âûïàäàþùèé ñïèñîê); 1 - îòïðàâëåíèå, 2 - ïðèáûòèå
	system("cls"); int control = 0; char a[m_s];
	do {
		for (int i = 0; i < m_s; i++) a[i] = 0;
		int s[9];
		for (int i = 0; i < 9; i++) s[i] = 0;
		for (int i = 0; i < m_s; i++) {
			cout << "Ââåäèòå ãîðîä ";
			if (x == 1) cout << "îòïðàâëåíèÿ: ";
			else if (x == 2) cout << "íàçíà÷åíèÿ: ";
			for (int m = 0; m < i; m++) {
				if (a[m] != 0) cout << a[m];
			}
			a[i] = _getch();
			system("cls");
			if (a[i] >= 49 && a[i] <= 57) {
				for (int l = 0; l < m_s; l++) {
					if (x == 1) towndep[l] = BB[s[a[i] - 49]][0][l];
					else if (x == 2) townarr[l] = BB[s[a[i] - 49]][0][l];
				}
				control = 1; break;
			}
			a[i] = tolower(a[i]);
			for (int m = 0; m < 9; m++) s[m] = 0;
			for (int y = 0, j = 0; j < s_s; j++) {
				int t = 0;
				for (int k = 0; k <= i; k++) {
					if (a[k] == BB[j][0][k]) t = 1;
					else {
						t = 0; break;
					}
				}
				if (t == 1 && y < 9) {
					cout << y + 1 << ". " << BB[j][0] << ", " << BB[j][1] << endl; s[y] = j; y++;
				}
				if (y == 0 && j == s_s - 1) {
					cout << "Ãîðîä íå íàéäåí" << endl; i = m_s; break;
				}
			}
		}
	} while (control == 0);
	cout << "Ãîðîä ";
	if (x == 1) cout << "îòïðàâëåíèÿ: " << towndep;
	else if (x == 2) cout << "íàçíà÷åíèÿ: " << townarr;
	cout << endl; system("pause"); system("cls");
}
void Body() {  // Òåëî ïðîãðàììû (ãëàâíîå ìåíþ)
	struct Car {
		int nom = 0; // óíèêàëüíûé êîä àâòîìîáèëÿ
		char nomber[9] = ""; // ãîñíîìåð (â ôîðìàòå À001ÀÀ078)
		int tonnage = 0; // ãðóçîïîäú¸ìíîñòü (â êã)
		//float sizeA = 0, sizeB = 0, sizeC = 0; // ãàáàðèòû ÒÑ (äëèíà/øèðèíà/âûñîòà, ì)
		//float vA = 0, vB = 0, vC = 0; // îáú¸ìû ãðóçîâîãî îòñåêà (äëèíà/øèðèíà/âûñîòà, ì)
		//int weight = 0; // ìàññà ïóñòîãî ÒÑ (â êã)
		//short fuel = 0; // òèï òîïëèâà (÷èñëî, îò 1 äî 6) - ïðåäîñòàâëÿåòñÿ âûáîð
		int rate = 0; // ðàñõîä òîïëèâà (ë/100 êì)
		int tank = 0; // îáú¸ì áàêà
		int priority = 0; // îñîáûé ïðèîðèòåò
	};
	//struct Driver {
	//	string surname = "", name = "", middle = "", license = "-"; // Ô, È, Î, ÂÓ
	//};
	Car car[5]{ 0,0,0,0,0 }; /*Driver driver[10]; */char ch;
	for (int i = 0; i < 5; i++) {
		car[i].nom = user.getNom(i); car[i].rate = user.getRate(i); car[i].tank = user.getTank(i); car[i].tonnage = user.getTonnage(i);
		for (int j = 0; j < 9; j++) car[i].nomber[j] = user.getNomber(i, j);
	}
	do {
		system("cls"); cout << "1. Ïîñìîòðåòü èíôîðìàöèþ îá àêêàóíòå" << endl << "2. Äîáàâèòü äàííûå â àêêàóíò" << endl /*<< "3. Óäàëèòü äàííûå èç àêêàóíòà" << endl*/ << "4. Ñîñòàâèòü ìàðøðóò" /*<< endl << "5. Íàñòðîéêè"*/ << endl << "6. Âûõîä" << endl << "Âàø âûáîð: "; ch = _getch();
		while (ch != 49 && ch != 50 && ch != 51 && ch != 52 && ch != 53 && ch != 54) {
			cout << "Íåêîððåêòíûå äàííûå. Ââåäèòå ÷èñëî - 1, 2, 3, 4, 5 èëè 6" << endl; system("pause"); cout << ""; cout << "1. Ïîñìîòðåòü èíôîðìàöèþ îá àêêàóíòå" << endl << "2. Äîáàâèòü äàííûå â àêêàóíò" /*<< endl << "3. Óäàëèòü äàííûå èç àêêàóíòà"*/ << endl << "4. Ñîñòàâèòü ìàðøðóò" /*<< endl << "5. Íàñòðîéêè"*/ << endl << "6. Âûõîä" << endl << "Âàø âûáîð: "; ch = _getch(); system("cls");
		}
		system("cls");
		if (ch == 49) Outuser();  // Ïðîñìîòð ñïðàâî÷íîé èíôîðìàöèè
		else if (ch == 50) {  // Äîáàâëåíèå äàííûõ (àâòî, âîäèòåëè)
			system("cls"); int a = 0, b = 0; // êîëè÷åñòâî ìàøèí; êîëè÷åñòâî âîäèòåëåé
			for (int i = 0; i <= 5; i++) {
				if (i == 5) {
					a = i; break;
				}
				if (car[i].tank == 0) {
					a = i; break;
				}
			}
			/*for (int i = 0; i <= 10; i++) {
				if (i == 10) {
					b = i; break;
				}
				if (driver[i].license == "-") {
					b = i; break;
				}
			}*/
			for (int i = 0; i < a; i++) {
				cout << "Ìàøèíà ¹ " << i + 1 << endl;
				cout << "Ãîñíîìåð: " << car[i].nomber << endl;
				cout << "Ãðóçîïîäú¸ìíîñòü: " << car[i].tonnage << " êã" << endl;
				cout << "Ðàñõîä òîïëèâà: " << car[i].rate << " ë/100 êì" << endl;
				cout << "Îáú¸ì áàêà: " << car[i].tank << " ë" << endl;
			}
			for (int i = a; i < 5; i++) {
				char x; cout << "Äîáàâèòü àâòîìîáèëü?\n0. Íåò\n1. Äà\nÂàø âûáîð: "; x = _getch(); cout << endl;
				if (x == 48) break;
				else {
					system("cls"); cout << "Çàïîëíÿåì äàííûå îá àâòîìîáèëå ¹ " << i + 1 << endl;
					car[i].nom = i + 1;
					cout << "Ââåäèòå ãîñíîìåð àâòîìîáèëÿ: "; cin >> car[i].nomber;
					cout << "Ââåäèòå ãðóçîïîäú¸ìíîñòü (êã): "; cin >> car[i].tonnage;
					cout << "Ââåäèòå ðàñõîä òîïëèâà (ë/100 êì): "; cin >> car[i].rate;
					cout << "Ââåäèòå îáú¸ì áàêà (ë): "; cin >> car[i].tank;
					++user.CountCar;  // ãîâîðèì ïðîãðàììå, ÷òî äîáàâèëè íîâóþ ìàøèíó
				}
				a = i + 1;
			}
			if (a == 5) cout << "Áîëüøå àâòîìîáèëåé äîáàâèòü íåëüçÿ" << endl; system("pause");
			/*for (int i = b; i < 10; i++) {
				string x; cout << "Äîáàâèòü âîäèòåëÿ?\n0. Íåò\n1. Äà\nÂàø âûáîð: "; cin >> x;
				if (x == "0") break;
				else {
					cout << "Ââåäèòå ôàìèëèþ: "; cin >> driver[i].name;
					cout << "Ââåäèòå èìÿ: "; cin >> driver[i].surname;
					cout << "Ââåäèòå îò÷åñòâî: "; cin >> driver[i].middle;
					cout << "Ââåäèòå êàòåãîðèè ÂÓ (â àëôàâèòíîì ïîðÿäêå îò A äî E): "; cin >> driver[i].license;
				}
			}*/
		}
		else if (ch == 51) {  // 3. Óäàëèòü äàííûå

		}
		else if (ch == 52) {  // 4. Ñîñòàâèòü ìàðøðóò
			Towndeparr(1);
			Towndeparr(2);
			// Çäåñü íà÷èíàåòñÿ ïîäãîòîâêà âñåõ ïåðåìåííûõ ê âûçîâó ôóíêöèè Route
			int town1 = -1, town2 = -1;
			for (int i = 0; (town1 == -1 || town2 == -1) && i < x_s; ++i) {
				if (str_copy(BB[i][0], towndep) == true) town1 = i;
				if (str_copy(BB[i][0], townarr) == true) town2 = i;				
			}
			short settings[2]{ 0,0 };
			int** car_K = new int*[user.CountCar];
			for (int i = 0; i < user.CountCar; ++i) {
				car_K[i] = new int[5];
				car_K[i][0] = car[i].nom;
				car_K[i][1] = car[i].tonnage;
				car_K[i][2] = car[i].rate;
				car_K[i][3] = car[i].tank;
				car_K[i][4] = car[i].priority;
			}
			string value[1076];
			for (int i = 0; i < 1076; ++i) {
				value[i] = BB[i][0];
			}
			Route(town1, town2, Distances, 1075, car_K, user.CountCar, settings, value);  // Âûçîâ ôóíêöèè Route (ìàðøðóò)
			system("pause");
		}
		else if (ch == 53) {  // 5. Íàñòðîéêè (â ò. ÷. - êàêèå ãîðîäà ó÷èòûâàåì ïðè ïîñòðîåíèè ìàðøðóòà)

		}
		else if (ch == 54) return;  // 6. Âûõîä èç àêêàóíòà èëè çàâåðøåíèå ðàáîòû
		for (int i = 0; i < 5; i++) {  // îáíîâëåíèå äàííûõ â ïåðåìåííîé user
			user.setRate(car[i].rate, i); user.setTank(car[i].tank, i); user.setTonnage(car[i].tonnage, i); user.setNom(car[i].nom, i);
			for (int j = 0; j < 9; j++) user.setNomber(car[i].nomber[j], i, j);
		}
	} while (true);
}
int main() {
	SetConsoleCP(1251); SetConsoleOutputCP(1251); system("color 70"); char a = 48;
	cout << "Çàãðóçêà ñëóæåáíûõ ôàéëîâ. Ïîäîæäèòå..." << endl;
	Files();
	system("cls");
	do {
		Hello();
		if (user.getName(0) != 0) {
			Body(); cout << "0. Âûéòè èç àêêàóíòà\n1. Çàâåðøèòü ðàáîòó" << endl << "Âàø âûáîð: "; a = _getch(); cout << endl;
			char A[20][28][31];  // Äàëåå ïðîãðàììà âûïîëíÿåò ïåðåçàïèñü ïîëüçîâàòåëüñêîãî ôàéëà Users.txt ñ îáíîâë¸ííîé èíôîðìàöèåé çà òåêóùóþ ñåññèþ
			ifstream tin("C:/Users/Public/Documents/IT_HAR_SKILLS/Create Projects/Ëîãèñò/Ëîãèñò/Resource/Users.txt");
			int s = 0, t = 0, m = 0;
			while (tin.good()) {
				tin >> A[s][t][m];
				if (A[s][t][m] != 59) m++;
				else {
					t++; m = 0;
				}
				if (t == 28) {
					s++; t = 0;
				}
			}
			tin.close();
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 28; j++) {
					short x = 0;
					if (A[i][j][1] == -52 && (j == 3 || j == 4 || j == 5 || j == 6 || j == 7)) x = 1;
					for (int k = 0; k < 31; k++) {
						if ((A[i][j][k] == -52 && (x == 1 || k >= 9 || (j != 3 && j != 4 && j != 5 && j != 6 && j != 7))) || A[i][j][k] == 59) A[i][j][k] = 0;
					}
				}
			}
			int secret_code_l[20][4];
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 4; j++) {
					if (A[i][2][j] >= 48 && A[i][2][j] <= 57) secret_code_l[i][j] = A[i][2][j] - 48;
				}
			}
			int secret_code[20];
			for (int i = 0; i < 20; i++) secret_code[i] = secret_code_l[i][0] * 1000 + secret_code_l[i][1] * 100 + secret_code_l[i][2] * 10 + secret_code_l[i][3];
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 2; j++) {
					Zachiv(A[i][j], secret_code_l[i][1] + secret_code_l[i][3]);
				}
			}
			char p[30]; int pp = 0; // pp - õðàíèò ¹ ïîëüçîâàòåëÿ, êîòîðîãî èçìåíÿåì
			for (int i = 0; i < 30; i++) p[i] = user.getName(i);
			for (int i = 0; i < 20; i++) {
				if (str_copy(A[i][0], p) == true) {
					pp = i; break;
				}
			}
			ofstream pin("Your address/Users.txt", ios::trunc); // Çàïèñü èíô. î ïîëüçîâàòåëå â ôàéë
			int h = 0;
			while (A[h][0][0] != 0) {
				h++;
			}
			for (int i = 0; i < 20; i++) {
				int step = -(secret_code_l[i][1] + secret_code_l[i][3]); // Øàã ïðè øèôðîâàíèè Öåçàðÿ ðàâåí ïðîòèâîïîëîæíîé ñóììå 1-é è 3-é öèôðû ñåêðåòíîãî êîäà (íà÷èíàÿ ñ íóëÿ)
				Zachiv(A[i][0], step); Zachiv(A[i][1], step); // +step - çàøèôðîâàòü
			}
			for (int i = 0; i < h; i++) {
				if (i != pp) {
					for (int j = 0; j < 28; j++) {
						for (int k = 0; k < 30; k++) {
							if (A[i][j][k] != 0) pin << A[i][j][k];
						}
						pin << ";";
					}
				}
				else {
					for (int k = 0; k < 30; k++) {
						if (A[i][0][k] != 0) pin << A[i][0][k];
					}
					pin << ";";
					for (int k = 0; k < 30; k++) {
						if (A[i][1][k] != 0) pin << A[i][1][k];
					}
					pin << ";" << user.getCode() << ";";
					for (int ii = 0; ii < 5; ii++) {
						for (int j = 0; j < 9; j++) { // Ãîñíîìåð
							if (user.getNomber(ii, j) != 0) pin << user.getNomber(ii, j);
						}
						pin << ";";
					}
					for (int ii = 0; ii < 5; ii++) pin << user.getTonnage(ii) << ";"; // Ãðóçîïîäú¸ìíîñòü
					for (int ii = 0; ii < 5; ii++) pin << user.getTank(ii) << ";"; // Îáú¸ì áàêà
					for (int ii = 0; ii < 5; ii++) pin << user.getRate(ii) << ";"; // Ðàñõîä òîïëèâà
					for (int ii = 0; ii < 5; ++ii) pin << user.getNom(ii) << ";"; // Öèôðîâîé íîìåð
				}
				pin << endl;
			}
			pin.close();
			if (a == 48) {
				cout << "Âû âûøëè èç àêêàóíòà" << endl; system("pause");
				for (int i = 0; i < 30; i++) {
					user.setName(0, i);
					user.setPassword(0, i);
				}
				user.setCode(0);
				for (int i = 0; i < 5; i++) {
					user.setRate(0, i);
					user.setTank(0, i);
					user.setTonnage(0, i);
					for (int j = 0; j < 9; j++) {
						user.setNomber(0, i, j);
					}
				}
			}
			system("cls");
		}
	} while (a == 48);
	cout << "Çàâåðøåíèå ðàáîòû..." << endl; system("pause"); return 0;
}
