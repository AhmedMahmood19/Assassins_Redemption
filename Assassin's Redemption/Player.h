#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"
using namespace std;

class Player
{
private:
	//Private Data
	sf::Texture pTex;
	sf::Sprite pSpr;
	sf::Vector2i *PtrmousePos;
	sf::Vector2f aimDir;
	float magnitude;
	float angle;
	sf::Vector2f aimDirNorm;
	vector<Bullet> bullets;
	Bullet b1;
	sf::Vector2f PrevPos;
	//Private funcs:
	void lookAtMouse();
	void updatePlayerSprite();
	int shoottimer=0;

public:
	Player();
	sf::Vector2f getbulletPos(int i);
	sf::Sprite getbulletSpr(int i);
	void setSprite(string file);
	void setPtrmousePos(sf::Vector2i& mouse);
	void setPosition(float x,float y);
	sf::Sprite getSprite();
	sf::Texture getTexture();
	sf::Vector2f getPlayerPos();
	sf::Vector2f getAimDirNorm();
	vector<Bullet>* getBulletsVector();
	float getAngle();
	void updatePlayer(int flag);
	void shoot();
};