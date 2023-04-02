#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#define windowWidth 800
#define windowHeight 600
#define MainMenuItems 3
#define playerSelectionMenuItems 5
#define playerLimit 3

class MainMenu
{
	sf::Font font;
	sf::Text menuText[MainMenuItems];
	sf::Text playerSelectionText[playerSelectionMenuItems];
	
public:
	unsigned int numOfPlayers = 2;
	
public:
	MainMenu()
	{
		if(!font.loadFromFile("font.ttf"))
		{
			std::cout << "Error loading font" << std::endl;
		}
		initText();
	}
	void initText()
	{
		//--------------- main menu
		sf::String str[MainMenuItems] = { "OS Assignment 2", "Start", "Exit" };
		float x, y;
		int separation[MainMenuItems] = { -220, -80, 20 };
		for (int i = 0; i < MainMenuItems; i++)
		{
			menuText[i].setFont(font);
			menuText[i].setCharacterSize(100);
			menuText[i].setString(str[i]);

			x = windowWidth / 2 - menuText[i].getGlobalBounds().width / 2;
			y = windowHeight / 2 - menuText[i].getGlobalBounds().height / 2;
			
			menuText[i].setPosition(sf::Vector2f(x, y + separation[i]));
		}

		//--------------- player selection
		sf::String str2[playerSelectionMenuItems] = { "Number of players: ","2", "+1", "-1", "Press ENTER to continue"};
		float x2, y2;
		for (int i = 0; i < playerSelectionMenuItems; i++)
		{
			playerSelectionText[i].setFont(font);
			playerSelectionText[i].setCharacterSize(80);
			playerSelectionText[i].setString(str2[i]);
		}

		playerSelectionText[2].setOutlineColor(sf::Color::Green); // +1 text
		playerSelectionText[2].setOutlineThickness(3);
		playerSelectionText[3].setOutlineColor(sf::Color::Red); // -1 text
		playerSelectionText[3].setOutlineThickness(3);

		x2 = windowWidth / 2 - playerSelectionText[0].getGlobalBounds().width / 2;
		y2 = windowHeight / 2 - playerSelectionText[0].getGlobalBounds().height / 2;
		playerSelectionText[0].setPosition(sf::Vector2f(x2, y2 - 150));
		playerSelectionText[1].setPosition(sf::Vector2f(x2 + 470, y2 - 150));
		playerSelectionText[2].setPosition(sf::Vector2f(x2 + 150, y2 - 30));
		playerSelectionText[3].setPosition(sf::Vector2f(x2 + 300, y2 - 30));
		playerSelectionText[4].setPosition(sf::Vector2f(x2 - 40, y2 + 120));
		
		
	}
	bool display()
	{
		sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Main Menu");
		window.setFramerateLimit(60);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
				default:
					break;
				}
			}

			window.clear(sf::Color::Black);
			
			for (int i = 1; i < MainMenuItems; i++)
			{
				if (menuText[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					menuText[i].setFillColor(sf::Color::Red);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (i == 1)
						{
							playerSelection(window);
							return true;
						}
						else if (i == 2)
						{
							return false;
						}
					}
				}
				else
				{
					menuText[i].setFillColor(sf::Color::White);
				}
			}

			for (int i = 0; i < MainMenuItems; i++)
			{
				window.draw(menuText[i]);
			}
			//---- render here ----


			window.display();
		}
		return false;
	}

	void playerSelection(sf::RenderWindow &window)
	{
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}

				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Enter)
					{
						return;
					}
					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						for (int i = 2; i < playerSelectionMenuItems; i++)
						{
							if (playerSelectionText[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
							{
								if (i == 2)
								{
									if (numOfPlayers < playerLimit)
									{
										numOfPlayers++;
										playerSelectionText[1].setString(std::to_string(numOfPlayers));
									}
								}
								else if (i == 3)
								{
									if (numOfPlayers > 2)
									{
										numOfPlayers--;
										playerSelectionText[1].setString(std::to_string(numOfPlayers));
									}
								}
							}

						}
					}
					break;
				}
				default:
					break;
				}
			}

			window.clear(sf::Color::Black);

			for (int i = 0; i < playerSelectionMenuItems; i++)
			{
				window.draw(playerSelectionText[i]);
			}
			//---- render here ----


			window.display();
		}
	}
};