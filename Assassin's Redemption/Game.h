#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Wall.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Pistol.h"
#include "Doors.h"
#include "Uzi.h"
#include "Shotgun.h"
class Game
{
private:
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::View* view;
	//init and update
	void initVariables();
	void initStartScreen();
	void initWindow();
	void initWalls();
	void initEnemies();
	void updateView();
	//Data:
	const string uziTex = "sprPWalkUzi_strip8.png";
	const string pistolTex = "sprPWalkMagnum_strip8.png";
	const string shotgunTex = "sprPWalkDoubleBarrel_strip8.png";
	Player player;
	Doors door;
	Uzi uzi;
	Pistol pistol;
	Shotgun shotgun;
	vector<Enemy> enemies;
	vector<Wall> walls;
	bool playerCollide;
	sf::Vector2i mousePosWindow;
	sf::Texture bgTex;
	sf::Sprite bgSpr;
	int blink;
	sf::Sprite TitleBGspr;
	sf::Texture TitleBGtex;
	sf::Font Titlefont;
	sf::Font Startfont;
	sf::Text Titletext;
	sf::Text Starttext;
	sf::Text GameoverText;
	sf::Text EscText;
	sf::Text ProgressText;
	sf::Music music;
	bool isStarted;
	//Funcs:
	void GameOver();
	void pollEvents();
	void updateMousePositions();
	void updateCharacters();
	void updateProgress();
	void wallColl();
	void windowbounds();
	void bulletWallColl();
	void senseDoors();
	int weaponPickup();
	void enemybulletColl();
	void playerbulletColl();
	//void floatWeapons();//Floating Weapons Prototype
public:
	Game();
	virtual ~Game();
	
	const bool running() const;
	void update();
	void render();
};