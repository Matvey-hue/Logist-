#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
char tolower(char A);
char toupper(char A);
bool str_copy(char A[], char B[]);
int count(std::string str, char x);
std::string* split(std::string str, char sep);
long long converter(std::string str);