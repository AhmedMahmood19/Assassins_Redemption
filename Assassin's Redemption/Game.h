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
	Player player;
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
	void drawWalls();
	void windowbounds();
	void bulletWallColl();
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