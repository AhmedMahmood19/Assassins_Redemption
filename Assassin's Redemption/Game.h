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
	//Class that acts as the game engine/Wrapper class
private:
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::View* view;
	void initVariables();
	void initStartScreen();
	void initWindow();
	void initWalls();
	void initEnemies();
	void updateView();

	//Game Logic
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
	//TitleScreen
	int blink;
	sf::Sprite TitleBGspr;
	sf::Texture TitleBGtex;
	sf::Font Titlefont;
	sf::Font Startfont;
	sf::Text Titletext;
	sf::Text Starttext;
	sf::Text GameoverText;
	sf::Text EscText;
	bool isStarted;
		//Funcs:
	void GameOver();
	void pollEvents();
	void updateMousePositions();
	void updateCharacters();
	void collisions();
	void windowbounds();
	void bulletWallColl();
	void senseDoors();
	int wepCheck();
	void enembullColl();
	//void floatWeapons();//Floating Weapons Prototype
public:

	//Constructors/Destructor
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void update();
	void render();
};