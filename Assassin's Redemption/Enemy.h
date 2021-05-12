#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "Uzi.h"

using namespace std;

class Enemy
{
private:
	//Private Data
	int i=0;//used in update sprite
	sf::Texture eTex;
	sf::Sprite eSpr;
	sf::Vector2f dest;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	sf::Vector2f patrolaimDir;
	sf::Vector2f patrolaimDirNorm;
	sf::Vector2f spawnPos; //where enemy is spawned
	sf::Vector2f patrolPos; //where enemy is supposed to turn back during patrol
	float magnitude=0;
	float patrolmagnitude=0;
	float angle=0;
	int Spriteflag;
	sf::Vector2f PosBeforeColl;
	bool collides= false;
	bool stopPatrol;
	bool isWalker= false;
	bool eDead = false;
	int shoottimer=0;
	bool startShooting = false;
	bool hasUzi = false;
	bool hasPistol = false;
	bool hasShotgun = false;
	Pistol pistol;
	Shotgun shotgun;
	Uzi uzi;
	//Private funcs:
	void lookAt(sf::Vector2f& aimDir);
	void updateEnemySprite();
	void patrol();
	void chasePlayer();
	void calcPath(sf::Vector2f dest, sf::Vector2f& Dir, float& Mag, sf::Vector2f& Norm);
public:
	
	int SpriteCheck();
	Enemy(sf::Vector2f pos, sf::Vector2f Ppos, int a);
	Enemy(sf::Vector2f pos,int a);
	void setSprite(string file);
	void setEnemyPos(float x, float y);
	void setCollides(bool);
	bool getCollides();
	sf::Sprite getSprite();
	sf::Vector2f getEnemyPos();
	bool geteDead();
	void enemyDies();
	void detectPlayer(sf::Vector2f player);
	void enemyshoot();
	Weapon* getWeapon();
	void dropWeapon(sf::Vector2f);
};