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
	Player player;
	Doors door;
	vector<Enemy> enemies;
	vector<Wall> walls;
	bool playerCollide;
	sf::Vector2i mousePosWindow;
	sf::Texture bgTex;
	sf::Sprite bgSpr;
	sf::Texture winTex;
	sf::Sprite winSpr;
	sf::Texture creditsTex;
	sf::Sprite creditsSpr;
	int enemiesleft;
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
	sf::Text BikeText;
	bool isStarted = false;
	bool hasWon = false;
	sf::Music music;
	sf::SoundBuffer hitbuff;
	//sf::SoundBuffer shootbuff;
	sf::SoundBuffer pickupbuff;
	sf::SoundBuffer bikebuff;
	sf::Sound hitsfx;
	//sf::Sound shootsfx;
	sf::Sound pickupsfx;
	sf::Sound bikesfx;
	//Funcs:
	void GameOver();
	void GameWon();
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
public:
	Game();
	virtual ~Game();
	
	const bool running() const;
	void update();
	void render();
};