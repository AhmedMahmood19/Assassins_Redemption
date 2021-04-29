#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Wall
{
private:
	sf::RectangleShape rect;

public:

	int wallCollision(sf::Vector2f PlayerPos);
	Wall(float w1 , float w2,float xPos,float yPos);
	sf::RectangleShape getwall();
};

