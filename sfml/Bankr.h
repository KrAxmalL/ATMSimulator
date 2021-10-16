#pragma once
#include <iostream>
using namespace std;

class Bank {
private:
	int id;
	string name;
public:
	const int& getId() const { return id; }
	void setId(int& newId) { id = newId; }

	const string& getName() const { return name; }
	void setName(string& newName) { name = newName; }
};