#pragma once
#include <SFML/Audio.hpp>

class Soundtrack
{
public:
	sf::Music music;
	Soundtrack()
	{}
	void play()
	{
		music.openFromFile("music.ogg");
		music.setLoop(true);
		music.play();
	}
};
