#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextArea.h"
using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1000, 700), "SFML works!");
    window.setKeyRepeatEnabled(true);
    Texture textureFon;
    if (!textureFon.loadFromFile("Forest.png"))
    {

    }
    Texture textureBox;
    if (!textureBox.loadFromFile("blank.png"))
    {

    }
    Texture textureLabel;
    if (!textureLabel.loadFromFile("label1.png"))
    {

    }
    //Texture textureButton;
    //if (!textureButton.loadFromFile("buttonFon.png"))
    {

    }
    Sprite background(textureFon);
    Color Grey(200, 200, 200);
    
    Font arial;
    arial.loadFromFile("arial.ttf");

    TextArea areaCard("Input card number", { 300,50 }, 20, Color::White, Color::Black, textureLabel);
    areaCard.setFont(arial);
    areaCard.setPosition({ 350,200 });
    areaCard.setVisible(false);

    Textbox boxCardNum(25, Color::Black, true, textureBox);
    boxCardNum.setFont(arial);
    boxCardNum.setPosition({ 450,300 });
    boxCardNum.setVisible(false);
    boxCardNum.setlimit(true, 5);

    Button btnStart("Start", { 200,50 }, 20, Color::White, Color::Black, textureBox);
    btnStart.setPosition({ 400, 350 });
    btnStart.setFont(arial);

    Button btnOkCard("OK", { 100,50 }, 25, Color::White, Color::Black, textureBox);
    btnOkCard.setPosition({ 450, 500 });
    btnOkCard.setFont(arial);
    btnOkCard.setVisible(false);

    Button btnOkPin("OK", { 80,50 }, 25, Color::White, Color::Black, textureBox);
    btnOkPin.setPosition({ 450, 500 });
    btnOkPin.setFont(arial);
    btnOkPin.setVisible(false);
   
    Button btnf1("func1", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf1.setPosition({ 250, 300 });
    btnf1.setFont(arial);
    btnf1.setVisible(false);

    Button btnf2("func2", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf2.setPosition({ 510, 300 });
    btnf2.setFont(arial);
    btnf2.setVisible(false);

    Button btnf3("func3", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf3.setPosition({ 250, 370 });
    btnf3.setFont(arial);
    btnf3.setVisible(false);

    Button btnf4("func4", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf4.setPosition({ 510, 370 });
    btnf4.setFont(arial);
    btnf4.setVisible(false);

    Button btnf5("func5", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf5.setPosition({ 250, 440 });
    btnf5.setFont(arial);
    btnf5.setVisible(false);

    Button btnf6("func6", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf6.setPosition({ 510, 440 });
    btnf6.setFont(arial);
    btnf6.setVisible(false);

    Button btnf7("func7", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf7.setPosition({ 250, 510 });
    btnf7.setFont(arial);
    btnf7.setVisible(false);

    Button btnf8("func8", { 240,50 }, 25, Color::White, Color::Black, textureBox);
    btnf8.setPosition({ 510, 510 });
    btnf8.setFont(arial);
    btnf8.setVisible(false);

    while (window.isOpen())
    {
        Event event;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            boxCardNum.setSelected(true);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            boxCardNum.setSelected(false);
        }
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
            case Event::TextEntered:
                boxCardNum.typedOn(event);
            case Event::MouseMoved:
               if (btnStart.isMouseOver(window)) {
                   btnStart.setBackColor(Grey);
                }
                else {
                   btnStart.setBackColor(Color::White);
                }
                if (btnOkCard.isMouseOver(window)) {
                    btnOkCard.setBackColor(Grey);
                }
                else {
                    btnOkCard.setBackColor(Color::White);
                }
                if (btnOkPin.isMouseOver(window)) {
                    btnOkPin.setBackColor(Grey);
                }
                else {
                    btnOkPin.setBackColor(Color::White);
                }
                if (btnf1.isMouseOver(window)) {
                    btnf1.setBackColor(Grey);
                }
                else {
                    btnf1.setBackColor(Color::White);
                }
                if (btnf2.isMouseOver(window)) {
                    btnf2.setBackColor(Grey);
                }
                else {
                    btnf2.setBackColor(Color::White);
                }
                if (btnf3.isMouseOver(window)) {
                    btnf3.setBackColor(Grey);
                }
                else {
                    btnf3.setBackColor(Color::White);
                }
                if (btnf4.isMouseOver(window)) {
                    btnf4.setBackColor(Grey);
                }
                else {
                    btnf4.setBackColor(Color::White);
                }
                if (btnf5.isMouseOver(window)) {
                    btnf5.setBackColor(Grey);
                }
                else {
                    btnf5.setBackColor(Color::White);
                }
                if (btnf6.isMouseOver(window)) {
                    btnf6.setBackColor(Grey);
                }
                else {
                    btnf6.setBackColor(Color::White);
                }
                if (btnf7.isMouseOver(window)) {
                    btnf7.setBackColor(Grey);
                }
                else {
                    btnf7.setBackColor(Color::White);
                }
                if (btnf8.isMouseOver(window)) {
                    btnf8.setBackColor(Grey);
                }
                else {
                    btnf8.setBackColor(Color::White);
                }
                break;
            case Event::MouseButtonPressed:
                if (btnStart.isMouseOver(window)) {
                    btnStart.setVisible(false);
                    btnOkCard.setVisible(true);
                    boxCardNum.setVisible(true);
                    areaCard.setVisible(true);
                }
                else if (btnOkCard.isMouseOver(window)) {
                    areaCard.setText("Input PIN number");
                    boxCardNum.clear();
                    boxCardNum.setSecret(true);
                    boxCardNum.setlimit(true, 4);
                    btnOkPin.setVisible(true);
                    btnOkCard.setVisible(false);
                    
                }
                else if (btnOkPin.isMouseOver(window)) {
                    boxCardNum.setVisible(false);
                    areaCard.setVisible(false);
                    btnOkCard.setVisible(false);
                    btnOkPin.setVisible(false);

                    btnf1.setVisible(true);
                    btnf2.setVisible(true);
                    btnf3.setVisible(true);
                    btnf4.setVisible(true);
                    
                    btnf5.setVisible(true);
                    btnf6.setVisible(true);
                    btnf7.setVisible(true);
                    btnf8.setVisible(true);
                }
                else if (btnf1.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func1
                }
                else if (btnf2.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func2
                }
                else if (btnf3.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func3
                }
                else if (btnf4.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func4
                }
                else if (btnf5.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func5
                }
                else if (btnf6.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func6
                }
                else if (btnf7.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func7
                }
                else if (btnf8.isMouseOver(window)) {
                    btnf1.setVisible(false);
                    btnf2.setVisible(false);
                    btnf3.setVisible(false);
                    btnf4.setVisible(false);

                    btnf5.setVisible(false);
                    btnf6.setVisible(false);
                    btnf7.setVisible(false);
                    btnf8.setVisible(false);

                    //action for button func8
                }
            }
        }

        window.clear();
        window.draw(background);
        btnStart.drawTo(window);
        btnOkCard.drawTo(window);
        btnOkPin.drawTo(window);
        boxCardNum.drawTo(window);
        areaCard.drawTo(window);
        btnf1.drawTo(window);
        btnf2.drawTo(window);
        btnf3.drawTo(window);
        btnf4.drawTo(window);
        btnf5.drawTo(window);
        btnf6.drawTo(window);
        btnf7.drawTo(window);
        btnf8.drawTo(window);
        window.display();
    }

    return 0;
}