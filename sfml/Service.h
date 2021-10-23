#pragma once
#include "Repository.h"

class Service {

private:
	Repository* repository;

public:

	Service(Repository* repo) : repository(repo) {}
	~Service() { delete repository; }

	int getData() const { return repository->getData(); }

};