#include "Basics.h"
#include "Sort.h"
#include "User.h"
#include "Route.h"
using namespace std;
const short x_s = 1076, y_s = 1076, z_s = 31; // размер массива для таблицы расстояний
const short s_s = 1076, t_s = 5, m_s = 31; // размер массива для соотношения городов и субъектов РФ
char AA[x_s][y_s][z_s], /* Таблица расстояний */ BB[s_s][t_s][m_s], /* Соотношение городов и субъектов РФ */ towndep[m_s], townarr[m_s]; /* Города отправления и назначения */
int Distances[x_s][y_s];
User user; // Переменная хранит полную характеристику аккаунта
bool Kontrolname(char name[]) { // Контроль на допустимость названия компании
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
bool Kontrolpassword(char password[]) { // Контроль на допустимость пароля
	if (strlen(password) >= 8 && strlen(password) <= 30) {
		for (int i = 0; i < strlen(password); i++) {
			if (password[i] <= 36 || (password[i] >= 38 && password[i] <= 41) || (password[i] >= 43 && password[i] <= 44) || (password[i] >= 46 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64) || (password[i] >= 91 && password[i] <= 96)) return false; // Которые исключаем
		}
		bool b = false; // Проверка наличия специальных символов
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
void Zachiv(char A[], int step) { // Шифр Цезаря
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
void Outuser() { // Процедура выводит на экран всю информацию о пользователе (при нажатии кнопки 1)
	system("cls");
	if (user.getName(0) != 0) {
		cout << "Название аккаунта: ";
		for (int i = 0; i < 30; i++) {
			cout << user.getName(i);
		}
		cout << endl;
		for (int i = 0; i < 30; i++) cout << "-";
		cout << endl;
		for (int i = 0; i < 5; i++) {
			if (user.getNomber(i, 0) != 0) {
				cout << "Автомобиль № " << i + 1 << endl;
				cout << "Госномер: ";
				for (int j = 0; j < 9; j++) cout << user.getNomber(i, j);
				cout << endl;
				cout << "Грузоподъёмность: " << user.getTonnage(i) << " кг" << endl;
				cout << "Расход топлива: " << user.getRate(i) << " л/100 км" << endl;
				cout << "Объём бака: " << user.getTank(i) << " л" << endl;
			}
			else if (i == 0) cout << "АВТОПАРК ПУСТОЙ" << endl;
		}
	}
	else {
		cout << "Вход в аккаунт не выполнен" << endl;
	}
	for (int i = 0; i < 30; i++) cout << "-";
	cout << endl;
	system("pause");
}
void Enter() { // Авторизация уже зарегистрированных пользователей
	system("cls");
	char A[20][28][31];
	ifstream tin("C:/Users/Public/Documents/IT_HAR_SKILLS/Create Projects/Логист/Логист/Resource/Users.txt");
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
		cout << "Введите название учётной записи: "; getline(cin, name_s);
	} while (size(name_s) == 0);
	for (int i = 0; i < size(name_s); i++) {
		if (i < 30) name[i] = name_s[i];
	}
	if (size(name_s) < 30) name[size(name_s)] = 0;
	else name[29] = 0;
	for (int i = 0; i < 20; i++) {
		if (str_copy(A[i][0], name) == true) {
			cout << "Введите пароль: "; getline(cin, password_s);
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
				cout << "Вы вошли в аккаунт" << endl; system("pause");
				// Считывание всей информации об аккаунте
				for (int y = 3; y < 8; y++) { // считываем госномер
					for (int z = 0; z < 9; z++) user.setNomber(A[i][y][z], y - 3, z);
				}
				for (int y = 8; y < 13; y++) { // грузоподъёмность
					char tonn[5]{ 0,0,0,0,0 }; int tonnage = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) tonnage = tonn[0] - 48;
					else if (tonn[2] == 0) tonnage = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) tonnage = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) tonnage = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else tonnage = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setTonnage(tonnage, y - 8);
				}
				for (int y = 13; y < 18; y++) { // объём бака
					char tonn[5]{ 0,0,0,0,0 }; int tank = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) tank = tonn[0] - 48;
					else if (tonn[2] == 0) tank = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) tank = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) tank = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else tank = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setTank(tank, y - 13);
				}
				for (int y = 18; y < 23; y++) { // расход топлива
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
			cout << "Введён неверный пароль\nВведите секретный код: "; (cin >> secret_code_s).get(); // Чтобы после getline всё нормально читал
			if (secret_code[i] == secret_code_s) {
				for (int h = 0; h < 30; h++) {
					if (name[h] == -52 && h != 0) name[h] = 0;
					user.setName(name[h], h);
				}
				for (int h = 0; h < 30; h++) user.setPassword(A[i][1][h], h);
				user.setCode(secret_code[i]);
				cout << "Вы вошли в аккаунт" << endl; system("pause");
				// Считывание всей информации об аккаунте
				for (int y = 3; y < 8; y++) { // считываем госномер
					for (int z = 0; z < 9; z++) user.setNomber(A[i][y][z], y - 3, z);
				}
				for (int y = 8; y < 13; y++) { // грузоподъёмность
					char tonn[5]{ 0,0,0,0,0 }; int tonnage = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) tonnage = tonn[0] - 48;
					else if (tonn[2] == 0) tonnage = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) tonnage = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) tonnage = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else tonnage = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setTonnage(tonnage, y - 8);
				}
				for (int y = 13; y < 18; y++) { // объём бака
					char tonn[5]{ 0,0,0,0,0 }; int tank = 0;
					for (int z = 0; z < 5; z++) tonn[z] = A[i][y][z];
					if (tonn[1] == 0) tank = tonn[0] - 48;
					else if (tonn[2] == 0) tank = (10 * (tonn[0] - 48)) + (tonn[1] - 48);
					else if (tonn[3] == 0) tank = (100 * (tonn[0] - 48)) + (10 * (tonn[1] - 48)) + (tonn[2] - 48);
					else if (tonn[4] == 0) tank = (1000 * (tonn[0] - 48)) + (100 * (tonn[1] - 48)) + (10 * (tonn[2] - 48)) + (tonn[3] - 48);
					else tank = (10000 * (tonn[0] - 48)) + (1000 * (tonn[1] - 48)) + (100 * (tonn[2] - 48)) + (10 * (tonn[3] - 48)) + (tonn[4] - 48);
					user.setTank(tank, y - 13);
				}
				for (int y = 18; y < 23; y++) { // расход топлива
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
			cout << "Введён неверный секретный код" << endl; system("pause"); return;
		}
	}
	cout << "Такой учётной записи нет в базе данных" << endl; system("pause"); return;
}
void Registr() { // Регистрация пользователя
	char A = 0, choise = 0, name[1000], password[1000];
	do {
		do {
			A = 0; choise = 0;
			system("cls");
			cout << "Название учётной записи должно иметь от 2 до 30 символов (включительно)\nНе должно быть символа \";\"\nПробелы не допускаются" << endl << "Введите название: "; cin.getline(name, 1000);
			while (Kontrolname(name) == false) {
				system("cls");
				cout << "Такое название не допускается.\nОно должно иметь от 2 до 30 символов (включительно)\nНе должно быть символа \";\"\nПробелы не допускаются" << endl << "Введите название: "; cin.getline(name, 1000);
			}
			char B[20][28][31];
			ifstream tin("C:/Users/Public/Documents/IT_HAR_SKILLS/Create Projects/Логист/Логист/Resource/Users.txt");
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
			short p = 0; // Контрольная переменная (повтор имени)
			for (int i = 0; i < 20; i++) {
				if (str_copy(B[i][0], name) == true) {
					cout << "Пользователь с таким именем уже существует" << endl; p = 1; break;
				}
			}
			if (p == 1) {
				system("pause"); A = 50; continue;
			}
			cout << "Название записано" << endl;
			system("pause"); system("cls");
			cout << "Пароль должен иметь от 8 до 30 символов (включительно)\nВсе буквы английские\nХотя бы 1 заглавная буква, 1 прописная, 1 цифра, 1 символ \"-\", \"%\" или \"*\"" << endl << "Придумайте пароль: "; cin.getline(password, 1000);
			while (Kontrolpassword(password) == false) {
				system("cls");
				cout << "Такой пароль не допускается.\nОн должен иметь от 8 до 30 символов (включительно)\nВсе буквы английские\nХотя бы 1 заглавная буква, 1 прописная, 1 цифра, 1 символ \"-\", \"%\" или \"*\"" << endl << "Придумайте пароль: "; cin.getline(password, 1000);
			}
			cout << "Пароль записан" << endl;
			system("pause"); system("cls");
			cout << "1. Подтведить пароль" << endl << "2. Сбросить поля регистрации" << endl << "3. Я передумал регистрироваться" << endl << "Выберите действие: "; A = _getch(); cout << endl;
			while (A != 49 && A != 50 && A != 51) {
				cout << "Ошибка. Повторите попытку:\n1. Подтведить пароль\n2. Сбросить поля регистрации\n3. Я передумал регистрироваться\nВыберите действие: "; A = _getch(); cout << endl;
			}
			if (A == 51) return;
		} while (A == 50);
		char cpy_password[1000];
		cout << "Подтвердите пароль: "; cin.getline(cpy_password, 1000);
		while (str_copy(cpy_password, password) == false && choise != 50) {
			system("cls"); cout << "Пароли не совпадают\n1. Подтвердить пароль\n2. Сбросить поля регистрации\n3. Я передумал регистрироваться\nВыберите действие: "; choise = _getch(); cout << endl;
			while (choise != 49 && choise != 50 && choise != 51) {
				system("cls"); cout << "Ошибка. Повторите попытку:\n1. Подтведить пароль\n2. Сбросить поля регистрации\n3. Я передумал регистрироваться\nВыберите действие: "; choise = _getch(); cout << endl;
			}
			if (choise == 51) return;
			if (choise == 49) {
				cout << "Подтвердите пароль: "; cin.getline(cpy_password, 1000);
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
	int step = -(secret_code[1] + secret_code[3]); // Шаг при шифровании Цезаря равен противоположной сумме 1-й и 3-й цифры секретного кода (начиная с нуля)
	Zachiv(name, step); Zachiv(password, step); // +step - зашифровать
	ofstream lin("C:/Users/Public/Documents/IT_HAR_SKILLS/Create Projects/Логист/Логист/Resource/Users.txt", ios::app);
	lin << endl;
	for (int i = 0; i < strlen(name); i++) lin << name[i];
	lin << ";";
	for (int i = 0; i < strlen(password); i++) lin << password[i];
	lin << ";" << secret_code_s << ";";
	lin << ";;;;;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;";
	lin.close();
	system("cls");
	Zachiv(name, -step); Zachiv(password, -step); // -step - расшифровать
	cout << "Благодарим за регистрацию в программе \"Логист\"" << endl << "Пользователь с именем " << name << " сохранён." << endl << "Ваш секретный код: " << secret_code_s << ". Используйте его, если забудете пароль." << endl << "Предлагаем войти в аккаунт заново, чтобы убедиться, что Вы знаете свой пароль." << endl; system("pause"); Enter();
}
void Hello() { // С этого начинается исполнение программы (приветственное сообщение)
	char A;
	do {
		cout << "Добро пожаловать в программу \"Логист\"" << endl << "1. Войти в аккаунт" << endl << "2. Регистрация" << endl << "Ваш выбор: "; A = _getch(); cout << endl;
		if (A == 49) Enter();
		else if (A == 50) Registr();
		else {
			cout << "Ошибка. Введите только число - 1 или 2" << endl; system("pause");
		}
		system("cls");
	} while (A != 49 && A != 50);
}
void Files() {  // Загружает служебную информацию (Towns.txt, Distances.txt)
	ifstream lin("C:/Users/Public/Documents/IT_HAR_SKILLS/Create Projects/Логист/Логист/Resource/Towns.csv");
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
	ifstream in("C:/Users/Public/Documents/IT_HAR_SKILLS/Create Projects/Логист/Логист/Resource/Distances.csv");
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
	for (int i = 0; i < x_s; ++i) {  // Превращаем массив символов в массив чисел
		for (int j = 0; j < y_s; ++j) {
			string via = AA[i][j];
			Distances[i][j] = converter(via);
		}
	}
	in.close();
}
void Towndeparr(int x) {  // Выбор двух городов (выпадающий список); 1 - отправление, 2 - прибытие
	system("cls"); int control = 0; char a[m_s];
	do {
		for (int i = 0; i < m_s; i++) a[i] = 0;
		int s[9];
		for (int i = 0; i < 9; i++) s[i] = 0;
		for (int i = 0; i < m_s; i++) {
			cout << "Введите город ";
			if (x == 1) cout << "отправления: ";
			else if (x == 2) cout << "назначения: ";
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
					cout << "Город не найден" << endl; i = m_s; break;
				}
			}
		}
	} while (control == 0);
	cout << "Город ";
	if (x == 1) cout << "отправления: " << towndep;
	else if (x == 2) cout << "назначения: " << townarr;
	cout << endl; system("pause"); system("cls");
}
void Body() {  // Тело программы (главное меню)
	struct Car {
		int nom = 0; // уникальный код автомобиля
		char nomber[9] = ""; // госномер (в формате А001АА078)
		int tonnage = 0; // грузоподъёмность (в кг)
		//float sizeA = 0, sizeB = 0, sizeC = 0; // габариты ТС (длина/ширина/высота, м)
		//float vA = 0, vB = 0, vC = 0; // объёмы грузового отсека (длина/ширина/высота, м)
		//int weight = 0; // масса пустого ТС (в кг)
		//short fuel = 0; // тип топлива (число, от 1 до 6) - предоставляется выбор
		int rate = 0; // расход топлива (л/100 км)
		int tank = 0; // объём бака
		int priority = 0; // особый приоритет
	};
	//struct Driver {
	//	string surname = "", name = "", middle = "", license = "-"; // Ф, И, О, ВУ
	//};
	Car car[5]{ 0,0,0,0,0 }; /*Driver driver[10]; */char ch;
	for (int i = 0; i < 5; i++) {
		car[i].nom = user.getNom(i); car[i].rate = user.getRate(i); car[i].tank = user.getTank(i); car[i].tonnage = user.getTonnage(i);
		for (int j = 0; j < 9; j++) car[i].nomber[j] = user.getNomber(i, j);
	}
	do {
		system("cls"); cout << "1. Посмотреть информацию об аккаунте" << endl << "2. Добавить данные в аккаунт" << endl /*<< "3. Удалить данные из аккаунта" << endl*/ << "4. Составить маршрут" /*<< endl << "5. Настройки"*/ << endl << "6. Выход" << endl << "Ваш выбор: "; ch = _getch();
		while (ch != 49 && ch != 50 && ch != 51 && ch != 52 && ch != 53 && ch != 54) {
			cout << "Некорректные данные. Введите число - 1, 2, 3, 4, 5 или 6" << endl; system("pause"); cout << ""; cout << "1. Посмотреть информацию об аккаунте" << endl << "2. Добавить данные в аккаунт" /*<< endl << "3. Удалить данные из аккаунта"*/ << endl << "4. Составить маршрут" /*<< endl << "5. Настройки"*/ << endl << "6. Выход" << endl << "Ваш выбор: "; ch = _getch(); system("cls");
		}
		system("cls");
		if (ch == 49) Outuser();  // Просмотр справочной информации
		else if (ch == 50) {  // Добавление данных (авто, водители)
			system("cls"); int a = 0, b = 0; // количество машин; количество водителей
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
				cout << "Машина № " << i + 1 << endl;
				cout << "Госномер: " << car[i].nomber << endl;
				cout << "Грузоподъёмность: " << car[i].tonnage << " кг" << endl;
				cout << "Расход топлива: " << car[i].rate << " л/100 км" << endl;
				cout << "Объём бака: " << car[i].tank << " л" << endl;
			}
			for (int i = a; i < 5; i++) {
				char x; cout << "Добавить автомобиль?\n0. Нет\n1. Да\nВаш выбор: "; x = _getch(); cout << endl;
				if (x == 48) break;
				else {
					system("cls"); cout << "Заполняем данные об автомобиле № " << i + 1 << endl;
					car[i].nom = i + 1;
					cout << "Введите госномер автомобиля: "; cin >> car[i].nomber;
					cout << "Введите грузоподъёмность (кг): "; cin >> car[i].tonnage;
					cout << "Введите расход топлива (л/100 км): "; cin >> car[i].rate;
					cout << "Введите объём бака (л): "; cin >> car[i].tank;
					++user.CountCar;  // говорим программе, что добавили новую машину
				}
				a = i + 1;
			}
			if (a == 5) cout << "Больше автомобилей добавить нельзя" << endl; system("pause");
			/*for (int i = b; i < 10; i++) {
				string x; cout << "Добавить водителя?\n0. Нет\n1. Да\nВаш выбор: "; cin >> x;
				if (x == "0") break;
				else {
					cout << "Введите фамилию: "; cin >> driver[i].name;
					cout << "Введите имя: "; cin >> driver[i].surname;
					cout << "Введите отчество: "; cin >> driver[i].middle;
					cout << "Введите категории ВУ (в алфавитном порядке от A до E): "; cin >> driver[i].license;
				}
			}*/
		}
		else if (ch == 51) {  // 3. Удалить данные

		}
		else if (ch == 52) {  // 4. Составить маршрут
			Towndeparr(1);
			Towndeparr(2);
			// Здесь начинается подготовка всех переменных к вызову функции Route
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
			Route(town1, town2, Distances, 1075, car_K, user.CountCar, settings, value);  // Вызов функции Route (маршрут)
			system("pause");
		}
		else if (ch == 53) {  // 5. Настройки (в т. ч. - какие города учитываем при построении маршрута)

		}
		else if (ch == 54) return;  // 6. Выход из аккаунта или завершение работы
		for (int i = 0; i < 5; i++) {  // обновление данных в переменной user
			user.setRate(car[i].rate, i); user.setTank(car[i].tank, i); user.setTonnage(car[i].tonnage, i); user.setNom(car[i].nom, i);
			for (int j = 0; j < 9; j++) user.setNomber(car[i].nomber[j], i, j);
		}
	} while (true);
}
int main() {
	SetConsoleCP(1251); SetConsoleOutputCP(1251); system("color 70"); char a = 48;
	cout << "Загрузка служебных файлов. Подождите..." << endl;
	Files();
	system("cls");
	do {
		Hello();
		if (user.getName(0) != 0) {
			Body(); cout << "0. Выйти из аккаунта\n1. Завершить работу" << endl << "Ваш выбор: "; a = _getch(); cout << endl;
			char A[20][28][31];  // Далее программа выполняет перезапись пользовательского файла Users.txt с обновлённой информацией за текущую сессию
			ifstream tin("C:/Users/Public/Documents/IT_HAR_SKILLS/Create Projects/Логист/Логист/Resource/Users.txt");
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
			char p[30]; int pp = 0; // pp - хранит № пользователя, которого изменяем
			for (int i = 0; i < 30; i++) p[i] = user.getName(i);
			for (int i = 0; i < 20; i++) {
				if (str_copy(A[i][0], p) == true) {
					pp = i; break;
				}
			}
			ofstream pin("C:/Users/Public/Documents/IT_HAR_SKILLS/Create Projects/Логист/Логист/Resource/Users.txt", ios::trunc); // Запись инф. о пользователе в файл
			int h = 0;
			while (A[h][0][0] != 0) {
				h++;
			}
			for (int i = 0; i < 20; i++) {
				int step = -(secret_code_l[i][1] + secret_code_l[i][3]); // Шаг при шифровании Цезаря равен противоположной сумме 1-й и 3-й цифры секретного кода (начиная с нуля)
				Zachiv(A[i][0], step); Zachiv(A[i][1], step); // +step - зашифровать
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
						for (int j = 0; j < 9; j++) { // Госномер
							if (user.getNomber(ii, j) != 0) pin << user.getNomber(ii, j);
						}
						pin << ";";
					}
					for (int ii = 0; ii < 5; ii++) pin << user.getTonnage(ii) << ";"; // Грузоподъёмность
					for (int ii = 0; ii < 5; ii++) pin << user.getTank(ii) << ";"; // Объём бака
					for (int ii = 0; ii < 5; ii++) pin << user.getRate(ii) << ";"; // Расход топлива
					for (int ii = 0; ii < 5; ++ii) pin << user.getNom(ii) << ";"; // Цифровой номер
				}
				pin << endl;
			}
			pin.close();
			if (a == 48) {
				cout << "Вы вышли из аккаунта" << endl; system("pause");
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
	cout << "Завершение работы..." << endl; system("pause"); return 0;
}
