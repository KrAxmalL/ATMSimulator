#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class Customer {
private:
	int id;
	string firstName, secondName;
	tm birthDate;
public:

	Customer(int customerId): id(customerId) {}

	const int& getId() const { return id; }
	void setId(int newId) { id = newId; }

	const string& getFName() const { return firstName; }
	void setFName(const string& name) { firstName = name; }

	const string& getSName() const { return secondName; }
	void setSName(const string& name) { secondName = name; }

	const tm& getBDay() const { return birthDate; }
	void setBDay(tm& date) { birthDate = date; }
};
