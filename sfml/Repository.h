#pragma once

class Repository {

private:
	int data;

public:
	Repository(int val) : data(val) {}
	~Repository() {}

	int getData() const { return data; }
};