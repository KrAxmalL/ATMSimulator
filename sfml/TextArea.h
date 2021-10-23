#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace sf;

class TextArea: public Drawable {
public:

	TextArea() {}

	TextArea(const std::string& t, const sf::Vector2f& size, int charSize, const sf::Color& bgColor, const sf::Color& textColor, const sf::Texture& texture) {
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

		float xPos = (pos.x + button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
		float yPos = (pos.y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
		text.setPosition({ xPos, yPos });
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(button);
	}

	void setVisible(bool b) {
		if (b) {
			setPosition(position);
		}
		else {
			button.setPosition({ 3000,3000 });

			float xPos = (3000 + button.getGlobalBounds().width / 3) - (text.getGlobalBounds().width / 2);
			float yPos = (3000 + button.getGlobalBounds().height / 3) - (text.getGlobalBounds().height / 2);
			text.setPosition({ xPos, yPos });
		}
	}

	void setText(const std::string& t) {
		text.setString(t);
	}

private:
	sf::Vector2f position;
	sf::RectangleShape button;
	sf::Text text;
};
