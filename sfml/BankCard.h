#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class BankCard {
private:
	int id;
	string name;
	int pin;
	bool blocked = false;
	tm blockStartDate;
	tm expireDate;
	double balance;
	int userId;
	int bankId;
public:

	BankCard() {}
	BankCard(string _name) : name(_name) {}
	BankCard(int _id): id(_id) {}

	BankCard(int _id, string _name, int _pin, bool _blocked, tm& _blockStartDate, 
		tm& _expireDate, double _balance, int _userId, int _bankId) :
		id(_id), name(_name), pin(_pin), blocked(_blocked), blockStartDate(_blockStartDate),
		expireDate(_expireDate), balance(_balance), userId(_userId), bankId(_bankId)
	{

	}

	const int& getId() const { return id; }
	void setId(int newId) { id = newId; }

	const string& getName() const { return name; }
	void setName(const string& newName) { name = newName; }

	const int& getPin() const { return pin; }
	void setPin(int newPin) { pin = newPin; }

	const int& getUId() const { return userId; }
	void setUId(int newUId) { userId = newUId; }

	const int& getBId() const { return bankId; }
	void setBId(int newBankId) { bankId = newBankId; }

	const double& getBalance() const { return balance; }
	void setBalance(double newBalance) { balance = newBalance; }

	const bool& isBlocked() const { return blocked; }
	void changeBlocking() { blocked = !blocked; }
	void setBlocked(bool _blocked) { blocked = _blocked; }

	const tm& getBlockStartDate() const { return blockStartDate; }
	void setBlockStartDate(const tm& date) { blockStartDate = date; }

	const tm& getExpireDay() const { return expireDate; }
	void setExpireDay(const tm& newExDAy) { expireDate = newExDAy; }

};

ostream& operator<<(ostream& os, const BankCard& card)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << card.getBalance();

	os << "BankCard " << card.getId() << ":\n" << "pin: " << card.getPin() << "\n"
	   << "balance: " << stream.str() << "\n" << "isBlocked: " << card.isBlocked() << "\n"
	   << "start block date: " << card.getBlockStartDate().tm_year << "\n"
	   << "end block date: " << card.getExpireDay().tm_year << "\n"
	   << "bankId: " << card.getBId() << "\n" << "ownerId: " << card.getUId();
	return os;
}