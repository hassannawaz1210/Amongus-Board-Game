#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#define CELL_SIZE 50

class Player
{
public:
	sf::RectangleShape shape;
	int itemCollected=0;
	int left, right, up, down;
	sf::Vector2i currentCell;
	sf::Texture playerTexture;
	static int textureNumber;
	sf::Text scoreText;
	sf::Font font;
	
	Player()
	{
	}

	void initPlayer(const int &n, bool **occupiedCells)
	{
		font.loadFromFile("font.ttf");

		playerTexture.loadFromFile("character_" + std::to_string(textureNumber++) + ".png");
		float x, y;
		do{
			x = rand() % n;
			y = rand() % n;
		} while (occupiedCells[int(x)][int(y)] == true);

		currentCell = sf::Vector2i(x, y);
		x = x * CELL_SIZE + 1;
		y = y * CELL_SIZE + 1;

		shape = sf::RectangleShape(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
		shape.setPosition(x, y);
		shape.setTexture(&playerTexture);
		occupiedCells[currentCell.x][currentCell.y] = true;

		scoreText.setFont(font);
		scoreText.setFillColor(sf::Color::Red);
		scoreText.setCharacterSize(25);
		scoreText.setOutlineColor(sf::Color::White);
		scoreText.setOutlineThickness(2);
		scoreText.setStyle(sf::Text::Bold);
		scoreText.setLetterSpacing(2);
		scoreText.setString("Score: 0");
		scoreText.setPosition(x, y - 20);
		
	}
		

	float x()
	{
		return shape.getPosition().x;
	}
	float y()
	{
		return shape.getPosition().y;
	}

};