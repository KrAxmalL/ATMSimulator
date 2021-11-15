#pragma once
#include <SFML/Graphics.hpp>
#include "Visible.h"
#include "Activatable.h"
#include "Assets.h"

#include <string>
#include <chrono>
#include <thread>
#include <future>

using std::string;
using namespace sf;

class Menu : public Drawable, public Visible, public Activatable {

private:
	bool _isActive;
	bool _isVisible;

	std::thread* errBoxDisappearThread = nullptr;
	size_t errDisappearTime;
	bool isErrDisplayedmessage = false;

public:

	Menu() 
	{
		errBox.setFont(Assets::Instance().arial);
		errBox.setScale({ 0.5, 0.5 });
		errBox.setPosition({ 400,250 });
	}
	
	virtual ~Menu() 
	{
		errDisappearTime = 0;
	}

	Text errBox;

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


	void displayErrMessage(const string& message)
	{
		errBox.setString(message);
		errDisappearTime = 100;
		isErrDisplayedmessage = true;

		if (errBoxDisappearThread == nullptr) {
			errBoxDisappearThread = new std::thread([&]() {
				while (true) {
					while (!isErrDisplayedmessage || --errDisappearTime) {
						std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });
					}

					errBox.setString("");
					isErrDisplayedmessage = false;
				}
			});
		}
	}

protected:

	virtual void setVisibleAllMembers(bool isVisible) = 0;
};

std::ostream& operator<<(std::ostream& os, const Menu& menu)
{
	//os << menu.name();
	return os;
}
