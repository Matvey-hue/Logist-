#include "Route.h"
#include "Sort.h"
using namespace std;
int path[6], pathx[1000000][12]; int I = 0;  // I - количество найденных маршрутов
void F(int x, int b, int townarr, int table[][1076], int count_town, float S) {
	for (int i = b; i < 6; i++) path[i] = 0;
	path[b] = x;
	if (b == 3 || x == townarr) { // Дошли до максимума рекурсии (лимит рекурсии или финальный город)
		if (path[b] == townarr) {
			for (int i = 0; i < 6; i++) {
				pathx[I][i] = path[i];
				if (i < 5 && path[i + 1] != 0) { pathx[I][i + 6] = table[path[i]][path[i + 1]]; pathx[I][11] += pathx[I][i + 6]; }
			}
			I++; // сохраняем полученный маршрут
		}
		return;
	}
	bool OKK = false;  // Проверка на случай, если вообще никуда сделать ход невозможно (нет дороги, нет топлива) => выходим из рекурсии
	for (int i = 1; i <= count_town; i++) {
		for (int j = b + 1; j < 6; j++) path[j] = 0;
		bool OK = true;
		for (int j : path) {
			if (j == i) { OK = false; break; }
		}
		if (table[x][i] <= S && table[x][i] != -1 && OK == true) { OKK = true; F(i, b + 1, townarr, table, count_town, S); }  // если до ближайшего города можно доехать - делаем ход
	}
	if (OKK == false) return;
}
void delet() {  // Очищает path, pathx, I
	for (int i = 0; i < 6; i++) path[i] = 0;
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < 12; j++) pathx[i][j] = 0;
	}
	I = 0;
}
int* show_s(int** car, int count_car, int M) {  // Выводит на экран список автомобилей
	int fact_car = 0;
	int* error_car = new int[count_car + 1];
	for (int i = 0; i < count_car; i++) {
		if (car[i][1] >= M) {  // Такой автомобиль отправляется на рассмотрение
			cout << fact_car + 1 << ". Автомобиль " << car[i][0] << "" << endl; fact_car++;
			(i != 0) ? (error_car[i] = error_car[i - 1]) : (error_car[i] = 0);
		}
		else {
			(i != 0) ? (error_car[i] = error_car[i - 1] + 1) : (error_car[i] = 1);
		}
	}
	cout << fact_car + 1 << ". Назад" << endl;
	error_car[count_car] = fact_car;	
	return error_car;
}
void Route(int towndep, int townarr, int table[][1076], int count_town, int** car, int count_car, short* settings, std::string* value)
{ // towndep - город отправления [код], townarr - город прибытия [код], table - таблица расстояний, count_town - количество городов в таблице, car - таблица (характеристика доступных автомобилей), count_car - количество автомобилей, settings - настройки опроса
	if (towndep == townarr) return;  // Совпадение городов - отказ в составлении маршрута
	int M = 0; cout << "Введите массу груза: "; cin >> M;
	long long timedep = 0, timearr = 0;  // Дата и время отправления; прибытия с 01.01.1900 00:00
	//if (settings[0] == 1) {  // Спрашиваем дату и время отправления; прибытия
	//	cout << "Задать дату и время:" << endl << "1. Отправления" << endl << "2. Прибытия" << endl << "3. Не задавать" << endl << "Ваш выбор: "; char ch = _getch();
	//	if (ch == 1) {
	//		cout << "Введите дату отправления в формате ДД.ММ.ГГГГ:";
	//		cout << "Введите время отправления:";
	//	}
	//}
	//if (settings[1] == 1) {  // Спрашиваем: какие водители могут выполнить этот заказ (по умолчанию - все в БД);
	//	// Выбрать: 1. Какие...; 2. Все, кроме...
	//}
	// Отбор автомобилей по условию: ГП >= M	
	int ch = 0;
	int* error_car = new int[count_car + 1];
	do {
		error_car = show_s(car, count_car, M);
		cout << "Выберите: "; ch = 0; cin >> ch;
		if (ch != error_car[count_car] + 1) {
			ch += (error_car[ch] - 1);  // Конвертируем ответ пользователя в реальный индекс автомобиля
			float V = car[ch - 1][3], R = car[ch - 1][2]; float S = V / R; S *= 100;
			F(towndep, 0, townarr, table, count_town, S);
			int* ptr = &pathx[0][0];
			sort(ptr, I, 12, 1, 11);
			cout << "Нашлось " << I << " маршрутов" << endl;
			for (int i = 0, j = 1; i < I; i++, j++) {  // Вывод маршрутов на экран
				cout << j << ". ";
				int countvia = 0;
				for (int k = 0; k < 6; ++k) {
					if (pathx[i][k] == 0) { countvia = k; break; }
				}
				for (int f = 0; f < countvia - 1; ++f) cout << value[pathx[i][f]] << " -> ";
				cout << value[pathx[i][countvia - 1]] << " | ";
				for (int f = 6; f < 12; ++f) cout << pathx[i][f] << " ";
				cout << endl;
				if (j == 7 || (i + 1) == I) {
					cout << j + 1 << ". На предыдущую страницу" << endl;
					if ((i + 1) < I) cout << j + 2 << ". Ещё варианты" << endl;
					cout << "Выберите: "; char ch2 = 0; ch2 = _getch(); cout << ch2 << endl; system("cls");
					if (ch2 == j + 49) {
						if (i >= 7) i -= 7 + j;
						else {
							cout << "Возвращаемся в меню выбора автомобиля..." << endl;
							ch = error_car[count_car]; delet(); break;
						}
						j = 0;
					}
					else if (ch2 == j + 50 && (i + 1) < I) j = 0;
					else {
						cout << "Возвращаемся в меню выбора автомобиля..." << endl;
						ch = error_car[count_car]; delet(); break;
					}
				}
			}
		}
	} while (ch != error_car[count_car] + 1);
}