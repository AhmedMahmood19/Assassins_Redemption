#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"

class Wall
{
private:
	sf::RectangleShape rect;

public:
	void disappear();
	void appear(float w1, float w2);
	int wallcolCont(sf::Vector2f Pos);
	int wallcolInter(sf::Sprite a);
	Wall(float w1 , float w2,float xPos,float yPos);
	sf::RectangleShape getwall();
};

