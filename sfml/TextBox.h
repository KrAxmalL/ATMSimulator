#pragma once 
#include <iostream> 
#include <SFML/Graphics.hpp> 
#include <sstream> 

#define DELETE_KEY 8 
#define ENTER_KEY 13 
#define ESCAPE_KEY 27 

class Textbox {
public:
	Textbox() { }

	Textbox(int size, sf::Color color, bool sel,sf::Texture &texture) {
		
		form.setTexture(&texture);

		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		form.setFillColor(sf::Color::White);
		setlimit(true, 5);
		isSelected = sel;
		if (sel) {
			textbox.setString("_");
		}
		else {
			textbox.setString("");
		}
	}
	void setFont(sf::Font& font) {
		textbox.setFont(font);
	}
	void setPosition(sf::Vector2f pos) {
		this->position = pos;
		textbox.setPosition({ float(pos.x + 10) ,pos.y + 10});
		form.setPosition(pos);
	}
	void setlimit(bool ToF) {
		hasLimit = ToF;
	} 
	void setSecret(bool ToF) {
		isSecret = ToF;
	}
	void setlimit(bool ToF, int lim) {
		hasLimit = ToF;
		limit = lim - 1;
		form.setSize({ float(lim * 20), 50 });
	}
	void setSelected(bool sel) {
		isSelected = sel;
		if (!sel) {
			std::string t = text.str();;
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
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
	void drawTo(sf::RenderWindow& window) {
		window.draw(form);
		window.draw(textbox);
	}
	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit) {
					if (text.str().length() <= limit) {
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY) {
						deletelastChar();
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}
	void clear() {
		while (text.str().length() > 0) {
			deletelastChar();
		}
		textbox.setString(text.str() + "_");
	}

private:
	sf::Vector2f position;
	sf::Text textbox;
	sf::RectangleShape form;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	bool isSecret = false;
	int limit;

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			if (isSecret) {
				charTyped = '*';
			}
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deletelastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}
	
	void deletelastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i]; 
		}
		text.str("");
		text << newT;
		textbox.setString(text.str());
	}
};
