#include "User.h"
void User::setName(char name, int i) {
	m_name[i] = name;
}
void User::setPassword(char password, int i) {
	m_password[i] = password;
}
void User::setCode(int secret_code_s) {
	m_secret_code_s = secret_code_s;
}
void User::setRate(int rate, int i) {
	m_rate[i] = rate;
}
void User::setTank(int tank, int i) {
	m_tank[i] = tank;
}
void User::setTonnage(int tonnage, int i) {
	m_tonnage[i] = tonnage;
}
void User::setNomber(char nomber, int i, int j) {
	m_nomber[i][j] = nomber;
}
void User::setNom(int nom, int i) { 
	m_nom[i] = nom;
}
char User::getName(int i) {
	return m_name[i];
}
char User::getPassword(int i) {
	return m_password[i];
}
int User::getCode() {
	return m_secret_code_s;
}
int User::getRate(int i) {
	return m_rate[i];
}
int User::getTank(int i) {
	return m_tank[i];
}
int User::getTonnage(int i) {
	return m_tonnage[i];
}
char User::getNomber(int i, int j) {
	return m_nomber[i][j];
}
int User::getNom(int i) {
	return m_nom[i];
}
int User::CountCar = 0;