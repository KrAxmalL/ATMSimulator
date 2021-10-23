#pragma once
#include <SFML/Graphics.hpp>
#include "Visible.h"
#include "Activatable.h"
#include "string.h"

using namespace sf;

class Menu : public Drawable, public Visible, public Activatable {

private:
	bool _isActive;
	bool _isVisible;

public:

	Menu() {}
	virtual ~Menu() {}

	bool isActive() override
	{
		return _isActive;
	}

	void setActive(bool isActive) override
	{
		_isActive = isActive;
	}

	bool isVisible() override
	{
		return _isVisible;
	}

	void setVisible(bool isVisible) override
	{
		_isVisible = isVisible;
		setVisibleAllMembers(_isVisible);
	}

	//virtual std::string name() const = 0;

protected:

	virtual void setVisibleAllMembers(bool isVisible) = 0;
};

std::ostream& operator<<(std::ostream& os, const Menu& menu)
{
	//os << menu.name();
	return os;
}
