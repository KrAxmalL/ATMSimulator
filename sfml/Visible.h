#pragma once


//todo - implement nvi
class Visible {

public:

	Visible() {};
	virtual ~Visible() {};

	virtual bool isVisible() = 0;
	virtual void setVisible(bool isVisible) = 0;

};
