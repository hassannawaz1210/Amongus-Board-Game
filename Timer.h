
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define GAME_TIME 4

class Timer
{
    sf::Font font;
public:
    sf::Clock clock;
    sf::Text timerText;
    int timeLeft;
public:
    Timer()
    {
        timeLeft = GAME_TIME;
        font.loadFromFile("timerFont.ttf");
    }
    void start(sf::RenderWindow &window)
    {
        clock.restart();
        timerText.setFont(font);
        timerText.setCharacterSize(20);
        timerText.setOrigin(120, 0);
        timerText.setPosition(window.getSize().x/2, 0);
        timerText.setFillColor(sf::Color::White);
        timerText.setString("Time left: 0");
    }
    
};
