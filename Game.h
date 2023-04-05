#pragma once
#include <ctime>
#include <string>
#include "Grid.h"
#include "Player.h"
#include "MainMenu.h"
#include "Collectables.h"
#include "Soundtrack.h"
#include "Thread.h"
#include "Timer.h"
#include <queue>
#include <atomic>


#define ROLL_NO 2993
#define INPUT_DELAY 90


//------------- global variables
const int playerKeySet[4][4] = {
    {sf::Keyboard::Key::Up, sf::Keyboard::Key::Left, sf::Keyboard::Key::Down, sf::Keyboard::Key::Right}, //arrow keys
	{22, 0, 18, 3}, //wasd
	{20, 7, 9, 10} //uhjk
};

std::queue<sf::Event> eventQueue;
std::atomic<bool> messageQueueLock(false);
//-----------------

int generate_n()
{
    int n = (rand() % 90) + 10;
    n *= 3;
    n = ROLL_NO / n;
    n = n % 25;
    if (n < 10) n += 15;
    return n;
}


int Player::textureNumber = 1;


class Game
{
public:
	const unsigned int numOfPlayers;
public:
	Game(const unsigned int &playerNum):numOfPlayers(playerNum){}

    static void* thread_func (void* argument)
    {
        Thread_Arg *arg = static_cast<Thread_Arg*>(argument);
        sf::RenderWindow  *window = static_cast<sf::RenderWindow*>(argument);
        sf::Event event;
        while (window->isOpen())
        {
            while(messageQueueLock.exchange(true)) {}

                while(eventQueue.empty() == false)
            {
                event = eventQueue.front();
                eventQueue.pop();
                switch (event.type)
                {
                    case sf::Event::KeyPressed:
                    {
                        sf::Vector2f pos;
                        for (int i = 0; i < 3; i++)
                        {
							if (event.key.code == arg->player[i].left     &&      arg->player[i].x() > 1)
                            {
                                    pos = sf::Vector2f(arg->player[i].x() - CELL_SIZE, arg->player[i].y());
									arg->player[i].shape.setPosition(pos);
                                    arg->player[i].currentCell.x -= 1;
                                    arg->player[i].scoreText.setPosition(pos.x, pos.y - 20);
                                    arg->player[i].shape.setTextureRect(sf::IntRect(arg->player[i].playerTexture.getSize().x, 0, -arg->player[i].playerTexture.getSize().x, arg->player[i].playerTexture.getSize().y));

                            }
							if (event.key.code == arg->player[i].right    &&     arg->player[i].x() < arg->windowSize - CELL_SIZE - 1)
                            {
                                    pos = sf::Vector2f(arg->player[i].x() + CELL_SIZE, arg->player[i].y());
									arg->player[i].shape.setPosition(pos);
                                    arg->player[i].currentCell.x += 1;
                                    arg->player[i].scoreText.setPosition(pos.x, pos.y - 20);
                                    arg->player[i].shape.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
                                    arg->player[i].shape.setTextureRect(sf::IntRect(0, 0, arg->player[i].playerTexture.getSize().x, arg->player[i].playerTexture.getSize().y));
                            }
							if (event.key.code == arg->player[i].up       &&       arg->player[i].y() > 1)
                            {
                                    pos = sf::Vector2f(arg->player[i].x(), arg->player[i].y() - CELL_SIZE);
									arg->player[i].shape.setPosition(pos);
                                    arg->player[i].currentCell.y -= 1;
                                    arg->player[i].scoreText.setPosition(pos.x, pos.y - 20);
                            }
							if (event.key.code == arg->player[i].down     &&   arg->player[i].y() < arg->windowSize - CELL_SIZE - 1)
                            {
                                    pos = sf::Vector2f(arg->player[i].x(), arg->player[i].y() + CELL_SIZE);
									arg->player[i].shape.setPosition(sf::Vector2f(arg->player[i].x(), arg->player[i].y() + CELL_SIZE));
                                    arg->player[i].currentCell.y += 1;
                                    arg->player[i].scoreText.setPosition(pos.x, pos.y - 20);
                            }
                        }
                        break;
                    }

                    default:
                        break;
                }
        }

            messageQueueLock.exchange(false);
        }
            
        pthread_exit(0);
    }

	int launch()
	{
        std::cout << "Number of players: " << numOfPlayers << std::endl;
        const int n = generate_n();
        std::cout << "Value of n: " << n << std::endl;
        
        Soundtrack soundtrack;
        soundtrack.play();
        //-----------------
        sf::Sound itemPickUpSound;
        sf::SoundBuffer pickUpSoundBuffer;
        pickUpSoundBuffer.loadFromFile("itemPickUpSound.ogg");
        itemPickUpSound.setBuffer(pickUpSoundBuffer);
        itemPickUpSound.setVolume(150);


        Grid grid(n); //------- n x n grid
        grid.create();

        //occupiedCells is used to keep track of which cell is occupied by player or collectable
        bool** occupiedCells = new bool* [n];
        for (int i = 0; i < n; i++) occupiedCells[i] = new bool[n];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				occupiedCells[i][j] = false;
        //--
        
        Player *player = new Player[numOfPlayers];
        for (int i = 0; i < numOfPlayers; i++)
        {
            player[i].initPlayer(n, occupiedCells);
            player[i].up = playerKeySet[i][0];
            player[i].left = playerKeySet[i][1];
            player[i].down = playerKeySet[i][2];
            player[i].right = playerKeySet[i][3];
        }
        
        const int numOfCollectables = n / 2;
        collectableContainer collectableCont(numOfCollectables);
        collectableCont.update(n, occupiedCells);
        

        const int windowSize = n * CELL_SIZE + 2;//+2 is for accommodating grid's outline
        sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "OS_A2");
        window.setFramerateLimit(60);

        //-----
        Timer timer;
        timer.start(window);

        //------------- threads
        Thread_Arg arg[numOfPlayers];
        Thread thread[numOfPlayers];
        for (int i = 0; i < numOfPlayers; i++)
        {
            arg[i].init(player, &window, windowSize, i);
            thread[i].create(thread_func, arg[i]);
        }
        
        while (window.isOpen())
        {
            sf::Event event;
            

            //------- handling events
            while(messageQueueLock.exchange(true)) {}
            if(window.pollEvent(event))
            {
                eventQueue.push(event);
                if(event.type == sf::Event::Closed)
                    {
                        window.close();
                        return -1;
                    }
            }
            messageQueueLock.exchange(false);
            

            //------- updating frame
            if(timer.clock.getElapsedTime().asSeconds() > 60) 
            {
                timer.timeLeft -= 1;
                timer.clock.restart();
            }
            if(timer.timeLeft == 0)
            {
                int maxScore = 0;
                int playerIndex = 0;
                for (int  i = 0; i < numOfPlayers; i++)
                {
                    if(player[i].itemCollected > maxScore)
                    {
                        maxScore = player[i].itemCollected;
                        playerIndex = i;
                    }
                }
                return playerIndex;
            }
            timer.timerText.setString("Time left: " + std::to_string(timer.timeLeft) + " mins");

            //-------    
            for (int i = 0; i < numOfPlayers; i++)
            {
                for (int j = 0; j < collectableCont.collectables.size(); j++)
                {
                    if(player[i].shape.getGlobalBounds().contains(collectableCont.collectables[j].shape.getPosition()))
                    {
                        player[i].itemCollected++;
                        collectableCont.collectables.erase(collectableCont.collectables.begin() + j);
                        occupiedCells[player[i].currentCell.x][player[i].currentCell.y];
                        player[i].scoreText.setString("Score: " + std::to_string(player[i].itemCollected));
                        itemPickUpSound.play();
                    }
                }
                
            }
            collectableCont.update(n, occupiedCells);
            

            //------- clearing previous screen
            window.clear(sf::Color::Black);

            //----------- Rendering
            //drawing grid
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    window.draw(grid.Rects[i][j]);

            //drawing collectables
            for (int i = 0; i < collectableCont.collectables.size(); i++)
            {
                window.draw(collectableCont.collectables[i].shape);
            }

            //drawing players
            for (int i = 0; i < numOfPlayers; i++)
            {
                window.draw(player[i].shape);
                window.draw(player[i].scoreText);
            }

            //drawing timer
            window.draw(timer.timerText);


            window.display();

        }
        return 0;
	}
};