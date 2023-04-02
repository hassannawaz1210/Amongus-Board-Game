#pragma once
#include <pthread.h>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Collectables.h"

class Thread_Arg
{
public:
    Player *player;
    Collectable *collectable;
    sf::RenderWindow *window;
    int playerNum;
    int windowSize;

public:
    Thread_Arg(){}
    void init(Player* p, Collectable *c, sf::RenderWindow * w, const int &s, int& i)
    {
        player = p;
        collectable = c;
        window = w;
        playerNum = i;
        windowSize = s;
    }
};

class Thread
{
    pthread_t thread;
    pthread_attr_t attr;
public:
    Thread()
    {
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    }
    void create(void* (*function)(void*), sf::RenderWindow &window)
    {
        pthread_create(&thread, &attr, function, &window);
        std:: cout << "Thread created." << std::endl; 
    }
};
