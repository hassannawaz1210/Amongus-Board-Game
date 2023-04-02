#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#define CELL_SIZE 50

class Grid {
public:
    sf::RectangleShape** Rects;
    const int row;
    const int col;

    Grid():row(0), col(0), Rects(NULL){}

    Grid(const int n) : row(n), col(n) {}
    
    void create()
    {
        Rects = new sf::RectangleShape * [row];
        for (int i = 0; i < row; i++)
            Rects[i] = new sf::RectangleShape[col];

        float posX = 1, posY = 1;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                Rects[i][j] = sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                Rects[i][j].setPosition(sf::Vector2f(posX, posY));
                Rects[i][j].setFillColor(sf::Color::Black);
                Rects[i][j].setOutlineColor(sf::Color::White);
                Rects[i][j].setOutlineThickness(1);
                posX += CELL_SIZE;
            }
            posX = 1;
            posY += CELL_SIZE;
        }
    }
};