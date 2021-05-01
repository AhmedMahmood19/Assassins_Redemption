#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"
using namespace std;

class Enemy
{
private:
	//Private Data
	sf::Texture eTex;
	sf::Sprite eSpr;
	sf::Vector2i* PtrmousePos;
	sf::Vector2f aimDir;
	sf::Vector2f oldpos;
	float magnitude;
	float angle;
	sf::Vector2f aimDirNorm;
	vector<Bullet> bullets;
	Bullet b1;
	sf::Vector2f PrevPos;
	bool collides;
	//Private funcs:
	void lookAtPlayer(sf::Vector2f player);
	void updateEnemySprite();

public:
	Enemy(sf::Vector2f pos);
	void setSprite(string file);
	void setPtrmousePos(sf::Vector2i& mouse);
	void setEnemyPos(float x, float y);
	void setCollides(bool);
	bool getCollides();
	sf::Sprite getSprite();
	sf::Texture getTexture();
	sf::Vector2f getEnemyPos();
	sf::Vector2f getAimDirNorm();
	vector<Bullet>* getBulletsVector();
	float getAngle();
	void calcDir(sf::Vector2f player);
	void chasePlayer();
	int detectPlayer(sf::Vector2f player);
	void shoot();
	void stop();
};