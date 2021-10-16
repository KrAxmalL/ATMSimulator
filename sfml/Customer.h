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
	const int& getId() const { return id; }
	void setId(int& newId) { id = newId; }

	const string& getFName() const { return firstName; }
	void setFName(string& name) { firstName = name; }

	const string& getSName() const { return secondName; }
	void setSName(string& name) { secondName = name; }

	const tm& getBDay() const { return birthDate; }
	void setBDay(tm& date) { birthDate = date; }
};
