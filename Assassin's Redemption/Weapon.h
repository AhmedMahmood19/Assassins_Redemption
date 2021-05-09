#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"
class Weapon
{
protected:
	sf::Texture wTex;
	sf::Sprite wSpr;
	int bsize;
	vector<Bullet> bullets;
	Bullet b1;

public:
	sf::Sprite getSprite();
	sf::Sprite* getSpritePtr();
	sf::Texture getTexture();
	sf::Vector2f getbulletPos(int i);
	sf::Sprite getbulletSpr(int i);
	void setSprite(std::string file);
	vector<Bullet>* getBulletsVector();
	int P_WepColl(sf::Sprite);
	virtual int getWepTimer()=0;
	Bullet* getb1ptr();
	Bullet getb1();
};

