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
#include "Enemy.h"
#include "Bullet.h"
#include "Wall.h"

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
	void updateView();

	//Game Logic
		//Data:
	Player player;
	Enemy enemy;
	vector<Wall> walls;
	bool flag;
	bool flagE;
	
	sf::Vector2i mousePosWindow;
	sf::Texture bgTex;
	sf::Sprite bgSpr;
		//Funcs:
	void pollEvents();
	void updateMousePositions();
	void collisions();
	void drawWalls();
	void windowbounds();
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