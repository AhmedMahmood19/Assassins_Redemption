#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace std;

class Doors
{
private:
	sf::Sprite doorSpr;
	sf::Texture doorTex;
	bool isDoorOpen;
public:
	Doors();
	void moveDoors();
	void initDoor(string file);
	sf::Sprite getSprite();
	bool getisOpen();
	void setisOpen(bool d);
};

