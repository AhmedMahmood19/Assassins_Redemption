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
	
	int wallCollision(sf::Vector2f Pos);
	int wallcoll(sf::Sprite a);
	Wall(float w1 , float w2,float xPos,float yPos);
	sf::RectangleShape getwall();
};

