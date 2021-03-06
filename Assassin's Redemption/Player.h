#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Bullet.h"
#include "Pistol.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "Uzi.h"

using namespace std;

class Player
{
private:
	//Private Data
	sf::Texture healthTex;
	sf::Sprite healthSpr;
	sf::Texture pTex;
	sf::Sprite pSpr;
	sf::Vector2i* PtrmousePos;
	sf::Vector2f aimDir;
	float magnitude;
	float angle;
	int health = 5;
	sf::Vector2f aimDirNorm;
	sf::Vector2f PrevPos;
	bool pDead;
	Pistol pistol;
	Shotgun shotgun;
	Uzi uzi;
	//Private funcs:
	void lookAtMouse();
	void updatePlayerSprite();
	int shoottimer = 0;

public:
	Player();
	Weapon* wep;
	sf::SoundBuffer shootbuff;
	sf::Sound shootsfx;
	void setSprite(string file);
	void setSound();
	void setPtrmousePos(sf::Vector2i& mouse);
	void setPosition(float x, float y);
	sf::Sprite getSprite();
	sf::Texture getTexture();
	sf::Vector2f getPlayerPos();
	sf::Vector2f getAimDirNorm();
	Weapon* getWeaponptr();
	float getAngle();
	void updatePlayer(int flag);
	void shoot();
	void pickWeapon(int hasWeapon);
	int playerWeaponColl(sf::Sprite x);
	bool getpDead();
	void playerDies();
	void inithealthBar();
	sf::Sprite getHealthSprite();
	void updatehealthSpr();
	void takeDamage();
	void healthbarGlow();
};