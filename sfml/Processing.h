#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class BankCard {
private:
	int id;
	int atmId;
	int bankId;
	tm date;
public:
	const int& getId() const { return id; }
	void setId(int& newId) { id = newId; }

	const int& getAtmId() const { return atmId; }
	void setAtmId(int& newUId) { atmId = newUId; }

	const int& getBankId() const { return bankId; }
	void setBankId(int& newUId) { bankId = newUId; }

	const tm& getDate() const { return date; }
	void setDate(tm& newDate) { date = newDate; }

};