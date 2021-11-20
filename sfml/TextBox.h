#pragma once 
#include <iostream> 
#include <SFML/Graphics.hpp> 
#include <sstream> 

#define DELETE_KEY sf::Keyboard::Delete
#define ENTER_KEY sf::Keyboard::Enter
#define ESCAPE_KEY sf::Keyboard::Escape
#define BACKSPACE_KEY sf::Keyboard::BackSpace

constexpr int ZERO = 48;
constexpr int NINE = 57;

using namespace sf;

//input bugs
class Textbox: public Drawable {
public:
	Textbox() { }

	Textbox(int size, const sf::Color& color, bool sel, const sf::Texture &texture) {
		
		form.setTexture(&texture);

		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		form.setFillColor(sf::Color::White);
		setlimit(true, 5);
		isSelected = sel;
		
		text = "_";
		textbox.setString(text);
	}
	void setFont(const sf::Font& font) {
		textbox.setFont(font);
	}

	void setPosition(const sf::Vector2f& pos) {
		this->position = pos;
		textbox.setPosition({ float(pos.x + 10) ,pos.y + 10});
		form.setPosition(pos);
	}

	void setlimit(bool ToF) {
		hasLimit = ToF;
	} 

	void setlimit(bool ToF, int lim) {
		hasLimit = ToF;
		limit = lim;
		form.setSize({ float(lim * 20), 50 });
	}

	void setSecret(bool ToF) {
		isSecret = ToF;
	}

	void setSelected(bool sel) {
		// todo: why !text.empty()
		if (isSelected && !sel && !text.empty() && !isFinishedLine()) {
			text.pop_back();
			textbox.setString(text);
			//removeLastChar();
		}
		else if (!isSelected && sel && !isFinishedLine()) {
			text.push_back('_');
			textbox.setString(text);
		}
		isSelected = sel;
	}

	bool isSelecte() {
		return isSelected;
	}

	void setStartedValue(std::string s) {
		text = s;
		textbox.setString(text);
	}

	void setVisible(bool b) {
		if (b) {
			setPosition(position);
		}
		else {
			textbox.setPosition({ 3000,3000 });
			form.setPosition({ 3000,3000 });
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(form);
		target.draw(textbox);
	}

	void typedOn(const sf::Event& input) {
		if (isSelected) {
			//std::cout << input.text.unicode << std::endl;
			//std::cout << DELETE_KEY << std::endl;
			//std::cout << BACKSPACE_KEY << std::endl;
			int charTyped = input.text.unicode;
			if (Keyboard::isKeyPressed(Keyboard::Backspace) || Keyboard::isKeyPressed(Keyboard::Delete)) {
				//std::cout << "pressed delete key or backspace key!" << std::endl;
				removeLastChar();
			}
			else if (charTyped >= ZERO && charTyped <= NINE)
			{
				if (hasLimit) {
					if (text.length() <= limit + 1) {
						inputLogic(charTyped);
					}
				}
				else
				{
					inputLogic(charTyped);
				}
			}
		}
	}

	bool isMouseOver(const Event& event)
	{
		std::pair<float, float> mouseCoords = getMouseCoordinates(event);

		float btnPosX = form.getPosition().x;
		float btnPosY = form.getPosition().y;

		float btnsPosWidth = form.getPosition().x + form.getLocalBounds().width;
		float btnyPosHeight = form.getPosition().y + form.getLocalBounds().height;

		if (mouseCoords.first < btnsPosWidth && mouseCoords.first > btnPosX && mouseCoords.second < btnyPosHeight && mouseCoords.second > btnPosY) {
			return true;
		}

		return false;
	}

	void clear() {
		text.clear();
		realText.clear();
		textbox.setString(text);
		if (isSelected)
		{
			text = "_";
		}
		/*else
		{
			text.clear();
			realText.clear();
			textbox.setString(text);
		}*/
	}

	std::string getText()
	{
		return realText;
	}

private:

	sf::Vector2f position;
	sf::Text textbox;
	sf::RectangleShape form;
	std::string text;
	std::string realText;
	//todo add additional string if string is secret
	bool isSelected = false;
	bool hasLimit = false;
	bool isSecret = false;
	int limit;

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped != BACKSPACE_KEY) {
			appendChar(static_cast<char>(charTyped));
		}
		else if (charTyped == DELETE_KEY || charTyped == BACKSPACE_KEY) {
			removeLastChar();
		}
	}

	void appendChar(char ch)
	{
		if (!isFinishedLine())
		{
			if (text.length() > 0)
			{
				text.pop_back();
			}
			text.push_back(ch);
			realText.push_back(ch);
			if (text.length() < limit && hasLimit)
			{
				text.push_back('_');
			}
		}
		std::string text2(text);
		if (isSecret) {
			text2 = "";
			for (size_t i = 0; i < text.length() - 1; i++)
			{
				text2 += "*";
			}
			if (isFinishedLine()) {
				text2 += "*";
			}
		}
		std::cout << "Screen text" << text << std::endl;
		std::cout << "Real text: " << realText << std::endl;
		textbox.setString(text2);
	}

	void removeLastChar()
	{
		bool needAdditionalSpace = !isFinishedLine();

		if (text.length() > 0)
		{
			text.pop_back();
			if (realText.length() > 0)
			{
				realText.pop_back();
			}
		}
		if (text.length() > 0 && needAdditionalSpace)
		{
			text.pop_back();
		}

		text.push_back('_');
		std::string text2(text);
		if (isSecret) {
			text2 = "";
			for (size_t i = 0; i < text.length() - 1; i++)
			{
				text2 += "*";
			}
			if (isFinishedLine()) {
				text2 += "*";
			}
		}
		std::cout << "Screen text" << text << std::endl;
		std::cout << "Real text: " << realText << std::endl;
		textbox.setString(text2);
	}

	std::pair<float, float> getMouseCoordinates(const Event& event)
	{
		float mouseX = event.mouseMove.x;
		float mouseY = event.mouseMove.y;

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				mouseX = event.mouseButton.x;
				mouseY = event.mouseButton.y;
			}
		}

		return { mouseX, mouseY };
	}

	bool isFinishedLine()
	{
		return hasLimit && (text.length() == limit) && (text.back() != '_');
	}
};
