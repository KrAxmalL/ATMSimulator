#pragma once

//todo - implement nvi
class Activatable {

public:

	Activatable() {};
	virtual ~Activatable() {};

	virtual bool isActive() = 0;
	virtual void setActive(bool isActive) = 0;
	
};
