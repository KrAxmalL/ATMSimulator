#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace sf;


class Controller {

public:

	Controller() {}
	virtual ~Controller() {}

	virtual void handleEvent(const Event& event) = 0;
	//virtual void drawView() = 0;
	virtual bool isActive() = 0;
	virtual void setActive(bool isActive) = 0;

	virtual Menu& menu() = 0;

};
