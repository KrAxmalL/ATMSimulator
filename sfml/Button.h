#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <utility>

using namespace sf;

class Button : public Drawable {

public:

	Button() {}

	Button(const std::string& t, const sf::Vector2f& size, int charSize, const sf::Color& bgColor, const sf::Color& textColor, const sf::Texture& texture) {
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);
		button.setSize(size);
		button.setFillColor(bgColor);
		button.setTexture(&texture);
	}

	void setFont(const sf::Font& font) {
		text.setFont(font);
	}

	void setBackColor(const sf::Color& ñolor) {
		button.setFillColor(ñolor);
	}

	void setTextColor(const sf::Color& color) {
		text.setFillColor(color);
	}

	void setPosition(const sf::Vector2f& pos) {
		this->position = pos;
		button.setPosition(pos);

		float xPos = (pos.x + button.getGlobalBounds().width / 3) - (text.getGlobalBounds().width / 2);
		float yPos = (pos.y + button.getGlobalBounds().height / 3) - (text.getGlobalBounds().height / 2);
		text.setPosition({ xPos, yPos });
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(button);
		window.draw(text);
	}

	//maybe not needed
	void setVisible(bool b) {
		if (b) {
			setPosition(position);
		}
		else {
			button.setPosition({3000,3000});

			float xPos = (3000 + button.getGlobalBounds().width / 3) - (text.getGlobalBounds().width / 2);
			float yPos = (3000 + button.getGlobalBounds().height / 3) - (text.getGlobalBounds().height / 2);
			text.setPosition({ xPos, yPos });
		}
	}

	/*bool isMouseOver(sf::RenderWindow& window) {
		
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnsPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;
		if (mouseX < btnsPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}*/

	bool isMouseOver(const Event& event)
	{
		std::pair<float, float> mouseCoords = getMouseCoordinates(event);

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnsPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseCoords.first < btnsPosWidth && mouseCoords.first > btnPosX && mouseCoords.second < btnyPosHeight && mouseCoords.second > btnPosY) {
			return true;
		}
		
		return false;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
	{
		target.draw(button);
		target.draw(text);
	}

private:

	sf::Vector2f position;
	sf::RectangleShape button;
	sf::Text text;

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
};
