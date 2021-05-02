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
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	sf::Vector2f patrolaimDir;
	sf::Vector2f patrolaimDirNorm;
	sf::Vector2f spawnPos; //where enemy is spawned
	sf::Vector2f patrolPos; //where enemy is supposed to turn back during patrol
	float magnitude;
	float patrolmagnitude;
	float angle;
	sf::Vector2f PosBeforeColl;
	bool collides;
	bool stopPatrol;
	bool isWalker;
	//Private funcs:
	void lookAtPlayer(sf::Vector2f player);
	void updateEnemySprite();

public:
	Enemy(sf::Vector2f pos, sf::Vector2f Ppos);
	Enemy(sf::Vector2f pos);
	void setSprite(string file);
	void setEnemyPos(float x, float y);
	void setCollides(bool);
	bool getCollides();
	sf::Sprite getSprite();
	sf::Texture getTexture();
	sf::Vector2f getEnemyPos();
	sf::Vector2f getAimDirNorm();
	float getAngle();
	void patrol();
	void detectPlayer(sf::Vector2f player);
	void chasePlayer();
	void calcPath(sf::Vector2f dest, sf::Vector2f& Dir, float& Mag, sf::Vector2f& Norm);
};