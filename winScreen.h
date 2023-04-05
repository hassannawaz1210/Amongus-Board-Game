#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#define windowWidth 800
#define windowHeight 600

class winScreen
{
public:
    sf::Font font;
    sf::Text text;
    
    winScreen()
    {
        if(!font.loadFromFile("font.ttf"))
        {
            std::cout << "Error loading font" << std::endl;
        }
        initText();
    }
    void initText()
    {
       //text in the middle of the screen
        text.setFont(font);
        text.setCharacterSize(100);
        text.setString("Player 1 wins!");
        float x = windowWidth / 2 - text.getGlobalBounds().width / 2;
        float y = windowHeight / 2 - text.getGlobalBounds().height / 2;
        text.setPosition(sf::Vector2f(x, y));

    }
    void display(int playerNum)
    {
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game Over");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            text.setString("Player " + std::to_string(playerNum) + " wins!");
            window.clear();
            window.draw(text);
            window.display();
        }
    }
};