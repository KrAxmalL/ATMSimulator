#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class BankCard {
private:
	int id;
	string name;
	int pin;
	int userId;
	int bankId;
	bool blocked = false;
	tm* blockStartDate = nullptr;
	tm expireDate;
public:
	const int& getId() const { return id; }
	void setId(int& newId) { id = newId; }

	const string& getName() const { return name; }
	void setName(string& newName) { name = newName; }

	const int& getPin() const { return pin; }
	void setPin(int& newPin) { pin = newPin; }

	const int& getUId() const { return userId; }
	void setUId(int& newUId) { userId = newUId; }

	const int& getBId() const { return bankId; }
	void setBId(int& newBankId) { bankId = newBankId; }

	const bool& isBlocked() const { return blocked; }
	void changeBlocking() { blocked = !blocked; }

	const tm& getBlockStartDate() const { return *blockStartDate; }
	void setBlockStartDate(tm& date) { *blockStartDate = date; }

	const tm& getExpireDay() const { return expireDate; }
	void getExpireDay(tm& newExDAy) { expireDate = newExDAy; }

};