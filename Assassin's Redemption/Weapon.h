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
	vector<Bullet> bullets;
	Bullet b1;
	bool isDropped = false;
public:
	void setisDropped(bool a);
	bool getisDropped();
	sf::Sprite getSprite();
	sf::Sprite* getSpritePtr();
	sf::Texture getTexture();
	sf::Sprite getbulletSpr(int i);
	void setSprite(std::string file);
	vector<Bullet>* getBulletsVector();
	int PlayerWepColl(sf::Sprite);
	virtual int getWepTimer()=0;
	Bullet* getb1ptr();
};