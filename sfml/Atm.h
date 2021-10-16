#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class ATM {
private:
	int atmId;
	string name;
public:
	int getAtmId() const { return atmId; };

	const string& getName() const { return name; };
	void setName(const string& newName) { name = newName; };
};