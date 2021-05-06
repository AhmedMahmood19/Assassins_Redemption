#pragma once
#include <iostream>
#include <vector>
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
	void initWindow();
	void initWalls();
	void initEnemies();
	void updateView();
	int j=0;

	//Game Logic
		//Data:
	const string a = "sprPWalkUzi_strip8.png";
	const string b = "sprPWalkScorpion_strip8.png";
	const string c = "sprPWalkDoubleBarrel_strip8.png";
	Player player;
	Doors door;
	Uzi uzi;
	Pistol pistol;
	Shotgun shotgun;
	vector<Enemy> enemies;
	vector<Wall> walls;
	bool flag;
	sf::Vector2i mousePosWindow;
	sf::Texture bgTex;
	sf::Sprite bgSpr;
		//Funcs:
	void pollEvents();
	void updateMousePositions();
	void collisions();
	void windowbounds();
	void bulletWallColl();
	void senseDoors();
	int wepCheck();
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