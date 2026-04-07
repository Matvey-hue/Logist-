#include <iostream>
#include "Basics.h"
char tolower(char A) { // Переводит символ в нижний регистр
	if ((A <= -33 && A >= -64) || (A <= 90 && A >= 65)) A += 32; return A;
}
char toupper(char A) { // // Переводит символ в верхний регистр
	if ((A <= -1 && A >= -32) || (A <= 122 && A >= 97)) A -= 32; return A;
}
bool str_copy(char A[], char B[]) { // Сравнение двух строк (возвращает true - если совпадают, false - если нет)
	int a = strlen(A), b = strlen(B), max_len = 0;
	if (a > b) max_len = a;
	else max_len = b;
	for (int i = 0; i < max_len; i++) {
		if (A[i] != B[i]) return false;
	}
	return true;
}
int count(std::string str, char x) { // Возвращает количество символов x в строке str
    int k = 0;
    for (char a : str) {
        if (a == x) k++;
    }
    return k;
}
std::string* split(std::string str, char sep) { // Возвращает указатель на разделённую символом sep строку str
    str += char(0);
    std::string* b = new std::string[count(str, sep) + 1];
    int k = 0, i = 0;
    while (str[i] != 0) {
        while (str[i] != sep) {
            b[k] += str[i]; i++;
            if (str[i] == 0) break;
        }
        k++; i++;
    }
    return b;
}
long long converter(std::string str) {  // переводит строку в число (возвращает число)
    int k = 0;
    for (int i = 48; i <= 57; i++) {
        k += count(str, i);
    }
    if (k != size(str) && !(k == size(str) - 1 && str[0] == '-')) return -1000000000;
    if (str[0] != '-') str = '+' + str;
    long long a = 0;
    for (int i = 1; i < size(str); i++) {
        a += (str[i] - 48) * pow(10, size(str) - i - 1);
    }
    if (str[0] == '-') return -a;
    return a;
}