#pragma once
class User {
	char m_name[30], m_password[30]; 
	char m_nomber[5][9];
	int m_secret_code_s;
	int m_rate[5], m_tank[5], m_tonnage[5], m_nom[5];
public:	
	static int CountCar;
	void setName(char name, int i);
	void setPassword(char password, int i);
	void setCode(int secret_code_s);
	void setRate(int rate, int i);
	void setTank(int tank, int i);
	void setTonnage(int tonnage, int i);
	void setNomber(char nomber, int i, int j);
	void setNom(int nom, int i);
	char getName(int i);
	char getPassword(int i);
	int getCode();
	int getRate(int i);
	int getTank(int i);
	int getTonnage(int i);
	char getNomber(int i, int j);
	int getNom(int i);
};