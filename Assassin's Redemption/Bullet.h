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
	float maxSpd;
public:
	Bullet();
	void setSprite(string file);
	void setShotgunBulletSprite(string file);
	void setSpritePos(sf::Vector2f p);
	sf::Vector2f moveSprite();
	void rotateSprite(float a);
	void setcurrentVel(sf::Vector2f v);
	sf::Sprite getSprite();
	sf::Texture getTexture();
	float getMaxSpd()const;
	sf::Vector2f bGetPos();
};