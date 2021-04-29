#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace std;

class Bullet
{
private:
	sf::Texture bTex;
	sf::Sprite	bSpr;
	sf::Vector2f currentVel;
	const float maxSpd;
public:
	Bullet();
	void setSprite(string file);
	void setSpritePos(sf::Vector2f p);
	void moveSprite();
	void rotateSprite(float a);
	void setcurrentVel(sf::Vector2f v);
	sf::Sprite getSprite();
	sf::Texture getTexture();
	float getMaxSpd()const;
};