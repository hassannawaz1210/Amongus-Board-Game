#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#define CELL_SIZE 50


class Collectable
{
public:
	sf::CircleShape shape;

	Collectable() {}

	void initCollectable(const int &n, bool **occupiedCells)
	{
		float x, y;
		do{
			x = rand() % n;
			y = rand() % n;
		} while (occupiedCells[int(x)][int(y)] == true);
		
		occupiedCells[int(x)][int(y)] = true;

		x = x * CELL_SIZE + CELL_SIZE / 2;
		y = y * CELL_SIZE + CELL_SIZE / 2;
		
		shape.setRadius(CELL_SIZE / 4);
		shape.setFillColor(sf::Color(rand()%255, rand()%255,rand()%255));
		shape.setOrigin(CELL_SIZE / 4, CELL_SIZE / 4);
		shape.setPosition(x,y);
	}
	

};

class collectableContainer
{
public:
	int numOfCollectables;
	std::vector<Collectable> collectables;
public:
	collectableContainer(int n):numOfCollectables(n){}
	void update(const int &n, bool **occupiedCells)
	{
		while(collectables.size() < numOfCollectables)
		{
			Collectable newCollectable;
			newCollectable.initCollectable(n, occupiedCells);
			collectables.push_back(newCollectable);
		}

	}
};
