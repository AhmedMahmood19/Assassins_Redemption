#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
class Weapon
{
protected:
	sf::Texture wTex;
	sf::Sprite wSpr;


public:
	sf::Sprite getSprite();
	sf::Texture getTexture();
	void setSprite(std::string file);
	virtual void shooting()=0;
	int PWcoll(sf::Sprite);
};

