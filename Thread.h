#pragma once
#include <pthread.h>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Collectables.h"

class Thread_Arg
{
public:
    Player *player;
    sf::RenderWindow *window;
    int playerNum;
    int windowSize;

public:
    Thread_Arg(){}
    void init(Player* p, sf::RenderWindow * w, const int &s, int& i)
    {
        player = p;
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
    void create(void* (*function)(void*), Thread_Arg &arg)
    {
        pthread_create(&thread, &attr, function, &arg);
        std:: cout << "Thread created." << std::endl; 
    }
};
