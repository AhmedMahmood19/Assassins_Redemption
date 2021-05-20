#include "Game.h"

using namespace std;
Game::Game()
{
	this->initVariables();
	this->initWindow();
	player.setPtrmousePos(mousePosWindow);
}

Game::~Game()
{
	delete this->window;
	delete this->view;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::initVariables()
{
	this->window = nullptr;
	srand((unsigned int)time(0));
	initStartScreen();
	//Game Logic
	playerCollide = 0;
	player.setSprite("Images/sprPWalkMagnum_strip8.png");
	player.setPosition(350.f, 1450.f);
	player.inithealthBar();
	if (!bgTex.loadFromFile("Images/beachmap.png"))
		return;
	bgSpr.setTexture(bgTex);
	bgSpr.setScale(2.5, 2.5);
	bgSpr.setOrigin(170, 100);
	//music
	music.openFromFile("Sounds/03. M.O.O.N. - Paris.wav");
	music.play();
	music.setLoop(true);
	//sfx
	if (!pickupbuff.loadFromFile("Sounds/PickupWeapon.wav"))
		return;
	pickupsfx.setBuffer(pickupbuff);
	if (!hitbuff.loadFromFile("Sounds/Hit.wav"))
		return;
	hitsfx.setBuffer(hitbuff);
	if (!bikebuff.loadFromFile("Sounds/BikeStart.wav"))
		return;
	bikesfx.setBuffer(bikebuff);
	//Enemies left progress
	ProgressText.setFont(Startfont);
	ProgressText.setCharacterSize(25);
	ProgressText.setFillColor(sf::Color(216, 0, 0));
	ProgressText.setOutlineColor(sf::Color::White);
	ProgressText.setOutlineThickness(.75);
	//Get to the Car
	BikeText.setFont(Titlefont);
	BikeText.setCharacterSize(20);
	BikeText.setFillColor(sf::Color::White);
	BikeText.setOutlineColor(sf::Color::Black);
	BikeText.setOutlineThickness(1);
	BikeText.setString("Press Space to Drive");
	BikeText.setPosition(700.f, -88.f);
	//You win
	if (!winTex.loadFromFile("Images/WinScreen.png"))
		return;
	winSpr.setTexture(winTex);
	//Credits
	if (!creditsTex.loadFromFile("Images/sprCredits.png"))
		return;
	creditsSpr.setTexture(creditsTex);
	creditsSpr.setScale(0.8f, 0.8f);

	initWalls();
	initEnemies();
	door.initDoor("Images/doors.png");
}

void Game::initStartScreen()
{
	blink = 255;
	isStarted = false;
	if (!Titlefont.loadFromFile("Fonts\\Doctor Glitch.otf"))
		return;
	if (!Startfont.loadFromFile("Fonts\\Distortion Dos Analogue.otf"))
		return;
	if (!TitleBGtex.loadFromFile("Images/WaterP.png"))
		return;
	Titletext.setPosition(40, 20);
	Starttext.setPosition(220, 270);
	Titletext.setFont(Titlefont);
	Starttext.setFont(Startfont);
	Titletext.setString("Assassin's Redemption");
	Starttext.setString("Press  X  to Start");
	Titletext.setCharacterSize(52);
	Starttext.setCharacterSize(42);
	Titletext.setFillColor(sf::Color::Black);
	Starttext.setFillColor(sf::Color(255, 255, 255, 200));
	TitleBGspr.setTexture(TitleBGtex);
}

void Game::initWindow()
{
	this->videoMode.height = 480;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Assassin's Redemption", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
};

void Game::initWalls() {
	//Hardcoding Walls
	walls.push_back(Wall(20, 715, -260, -110));
	walls.push_back(Wall(808, 20, -260, -120));
	walls.push_back(Wall(20, 60, 543, -115));
	walls.push_back(Wall(20, 78, 543, 40));
	walls.push_back(Wall(1280, 20, 545, 120));
	walls.push_back(Wall(1358, 22, 465, 1560));
	walls.push_back(Wall(20, 60, 465, 1320));
	walls.push_back(Wall(1015, 22, -165, 1320));
	walls.push_back(Wall(20, 715, -178, 610));
	walls.push_back(Wall(80, 22, -255, 595));
	walls.push_back(Wall(60, 22, -170, 1080));
	walls.push_back(Wall(310, 22, -10, 1080));
	walls.push_back(Wall(20, 240, 300, 1080));
	walls.push_back(Wall(540, 22, -15, 605));
	walls.push_back(Wall(540, 22, -15, 605));
	walls.push_back(Wall(20, 60, -15, 600));
	walls.push_back(Wall(20, 75, -15, 845));
	walls.push_back(Wall(885, 22, -10, 920));
	walls.push_back(Wall(20, 390, 868, 525));
	walls.push_back(Wall(220, 22, 715, 520));
	walls.push_back(Wall(20, 155, 700, 360));
	walls.push_back(Wall(160, 22, 540, 440));
	walls.push_back(Wall(20, 60, 545, 440));
	walls.push_back(Wall(20, 385, 1182, 130));
	walls.push_back(Wall(160, 22, 1025, 520));
	walls.push_back(Wall(20, 55, 705, 120));
	walls.push_back(Wall(20, 205, 1100, 530));
	walls.push_back(Wall(20, 395, 1100, 920));
	walls.push_back(Wall(165, 22, 940, 1315));
	walls.push_back(Wall(20, 230, 1022, 1330));
	//Pushback a door 30 and 31 index
	walls.push_back(Wall(12, 90, 460, 1380));//Upper door
	walls.push_back(Wall(12, 90, 460, 1470));//Lower door
}

void Game::initEnemies() {
	enemies.push_back(Enemy(sf::Vector2f(500.f, 700.f), rand() % 3 + 1));
	//bathroom
	enemies.push_back(Enemy(sf::Vector2f(-88.f, 1246.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(191.f, 1246.f), rand() % 3 + 1));

	//drawing room
	enemies.push_back(Enemy(sf::Vector2f(1271.f, 331.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(1671.f, 331.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(1256.f, 1456.f), sf::Vector2f(1631.f, 1456.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(1337.f, 1234.f), sf::Vector2f(1337.f, 462.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(1517.f, 466.f), sf::Vector2f(1517.f, 1234.f), rand() % 3 + 1));

	//office
	enemies.push_back(Enemy(sf::Vector2f(968.f, 187.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(740.f, 283.f), sf::Vector2f(998.f, 283.f), rand() % 3 + 1));

	//lounge
	enemies.push_back(Enemy(sf::Vector2f(461.f, 295.f), sf::Vector2f(-124.f, 295.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(-169.f, -26.f), sf::Vector2f(290.f, -26.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(-82.f, 762.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(242.f, 160.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(650.f, 490.f), sf::Vector2f(650.f, 871.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(420.f, 1130.f), sf::Vector2f(900.f, 1130.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(900.f, 1050.f), sf::Vector2f(420.f, 1050.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(977.f, 577.f), sf::Vector2f(977.f, 1111.f), rand() % 3 + 1));
	enemies.push_back(Enemy(sf::Vector2f(800.f, 1370.f), sf::Vector2f(800.f, 1530.f), rand() % 3 + 1));

	for (size_t  i = 0; i < enemies.size(); i++)
	{
		if(enemies[i].gethasWeapon()==1)
		enemies[i].setSprite("Images/sprEPistol.png");
		else if(enemies[i].gethasWeapon()== 2)
		enemies[i].setSprite("Images/sprEUzi.png");
		else if (enemies[i].gethasWeapon()== 3)
		enemies[i].setSprite("Images/sprEShotgun.png");
	}
	enemiesleft = (int)enemies.size();
}

void Game::GameOver() {
	sf::Vector2f offset(-320, -200);
	GameoverText.setPosition(player.getPlayerPos() + offset);
	GameoverText.setFont(Titlefont);
	GameoverText.setString("GAME OVER");
	GameoverText.setCharacterSize(100);
	GameoverText.setFillColor(sf::Color(255, 26, 255, 220));
	GameoverText.setOutlineColor(sf::Color(0, 204, 255));
	GameoverText.setOutlineThickness(3);
	sf::Vector2f offsetEsc(-120, 100);
	EscText.setPosition(player.getPlayerPos() + offsetEsc);
	EscText.setFont(Titlefont);
	EscText.setString("Press Esc to Exit");
	EscText.setCharacterSize(25);
	EscText.setFillColor(sf::Color(255, 26, 255, 220));
	EscText.setOutlineColor(sf::Color(0, 204, 255));
	EscText.setOutlineThickness(1);
}

void Game::GameWon() {
	static int i = 0;
	static int j = 0;
	//Winning Screen
	if (i == 3360)
		i = 0;
	winSpr.setTextureRect(sf::IntRect(0, i, 800, 480));
	i += 480;
	//Credits
	if (j <= 15)
		creditsSpr.setTextureRect(sf::IntRect(0, 0, 1000, 100));
	else if (j <= 30)
		creditsSpr.setTextureRect(sf::IntRect(0, 100, 1000, 100));
	else if (j <= 45)
		creditsSpr.setTextureRect(sf::IntRect(0, 200, 1000, 100));
	else if (j <= 60)
		creditsSpr.setTextureRect(sf::IntRect(0, 300, 1000, 100));
	else if (j <= 75)
		creditsSpr.setTextureRect(sf::IntRect(0, 400, 1000, 100));
	else
		creditsSpr.setTextureRect(sf::IntRect(0, 500, 1000, 100));
	j += 1;
}

void Game::updateView() {
	if (this->hasWon) {
		this->view = new sf::View(sf::Vector2f(400, 240), sf::Vector2f(800.f, 480.f));
		window->setView(*view);
		this->window->setFramerateLimit(10);
	}
	else
	{
		this->view = new sf::View(sf::Vector2f(player.getPlayerPos()), sf::Vector2f(800.f, 480.f));
		window->setView(*view);
	}
}

//Collision Functions
void Game::wallColl()
{
	for (size_t i = 0; i < walls.size(); i++) {
		if (walls[i].wallcolCont(player.getPlayerPos())) {
			playerCollide = 1;
			break;
		}
		else playerCollide = 0;
	}
	for (size_t j = 0; j < enemies.size(); j++) {
		for (size_t i = 0; i < walls.size(); i++)
		{
			if (walls[i].wallcolInter(enemies[j].getSprite())) {
				enemies[j].setCollides(true);
				break;
			}
			else enemies[j].setCollides(false);
		}
	}

}

void Game::enemybulletColl()
{
	for (size_t i = 0; i < enemies.size(); i++) {
		for (size_t j = 0; j < player.getWeaponptr()->getBulletsVector()->size(); j++)
		{
			if (player.getWeaponptr()->getBulletsVector()->at(j).bulletColl(enemies[i].getSprite()) == 1 && !enemies[i].geteDead())
			{
				enemiesleft--;
				hitsfx.play();
				enemies[i].enemyDies();
				player.getWeaponptr()->getBulletsVector()->erase(player.getWeaponptr()->getBulletsVector()->begin() + j);
				break;
			}
		}
	}

}

void Game::playerbulletColl()
{
	if (hit)
	{
		player.healthbarGlow();
		hit = false;
	}
	for (size_t i = 0; i < enemies.size(); i++) {
		for (size_t j = 0; j < enemies[i].getWeapon()->getBulletsVector()->size(); j++)
		{
			if (enemies[i].getWeapon()->getBulletsVector()->at(j).bulletColl(player.getSprite()) == 1)
			{
				hitsfx.play();
				player.takeDamage();
				hit = true;
				enemies[i].getWeapon()->getBulletsVector()->erase(enemies[i].getWeapon()->getBulletsVector()->begin() + j);
			}
		}
	}
}

void Game::bulletWallColl()
{
	//Enemy's Bullets
	for (size_t i = 0; i < walls.size(); i++) {
		for (size_t j = 0; j < enemies.size(); j++) {
			for (size_t k = 0; k < enemies[j].getWeapon()->getBulletsVector()->size(); k++)
			{
				if (walls[i].wallcolInter(enemies[j].getWeapon()->getBulletsVector()->at(k).getSprite()) == 1)
				{
					enemies[j].getWeapon()->getBulletsVector()->erase(enemies[j].getWeapon()->getBulletsVector()->begin() + k);
				}
			}
		}
	}
	//Player's Bullets
	for (int i = 0; i < walls.size(); i++) {
		for (int j = 0; j < player.getWeaponptr()->getBulletsVector()->size(); j++)
		{
			if (walls[i].wallcolInter(player.getWeaponptr()->getbulletSpr(j)) == 1)
			{
				player.getWeaponptr()->getBulletsVector()->erase(player.getWeaponptr()->getBulletsVector()->begin() + j);
			}
		}
	}
}

void Game::windowbounds()
{
	//For Enemies
	for (size_t j = 0; j < enemies.size(); j++)
	{
		//left
		if (this->enemies[j].getEnemyPos().x <= -415.f)
			this->enemies[j].setEnemyPos(-415, enemies[j].getEnemyPos().y);
		//right
		if (this->enemies[j].getEnemyPos().x >= 1825.f)
			this->enemies[j].setEnemyPos(1825, enemies[j].getEnemyPos().y);
		//up
		if (this->enemies[j].getEnemyPos().y <= -255.f)
			this->enemies[j].setEnemyPos(enemies[j].getEnemyPos().x, -255.f);
		// down
		if (this->enemies[j].getEnemyPos().y >= 1625.f)
			this->enemies[j].setEnemyPos(enemies[j].getEnemyPos().x, 1625.f);
	}
	//For Player
   //left
	if (this->player.getPlayerPos().x <= -415.f)
		this->player.setPosition(-415, player.getPlayerPos().y);

	//right
	if (this->player.getPlayerPos().x >= 1825.f)
		this->player.setPosition(1825, player.getPlayerPos().y);
	//up
	if (this->player.getPlayerPos().y <= -255.f)
		this->player.setPosition(player.getPlayerPos().x, -255.f);
	//down
	if (this->player.getPlayerPos().y >= 1625.f)
		this->player.setPosition(player.getPlayerPos().x, 1625.f);
	//Player's Bullets
	for (size_t j = 0; j < player.getWeaponptr()->getBulletsVector()->size(); j++)
	{
		if (player.getWeaponptr()->getBulletsVector()->at(j).bGetPos().x >= 1825.f || player.getWeaponptr()->getBulletsVector()->at(j).bGetPos().x <= -415.f)
		{
			player.getWeaponptr()->getBulletsVector()->erase(player.getWeaponptr()->getBulletsVector()->begin() + j);
		}
		else if (player.getWeaponptr()->getBulletsVector()->at(j).bGetPos().y >= 1625.f || player.getWeaponptr()->getBulletsVector()->at(j).bGetPos().y <= -255.f)
		{
			player.getWeaponptr()->getBulletsVector()->erase(player.getWeaponptr()->getBulletsVector()->begin() + j);
		}
	}
}

void Game::senseDoors() {
	for (size_t i = 0; i < enemies.size(); i++) {
		if (enemies[i].getEnemyPos().x >= 377 && enemies[i].getEnemyPos().x <= 600) {
			if (enemies[i].getEnemyPos().y >= 1345 && enemies[i].getEnemyPos().y <= 1625) {
				door.setisOpen(true);
				walls[30].disappear();
				walls[31].disappear();
				door.moveDoors();
				return;
			}
		}
	}
	if (player.getPlayerPos().x >= 377 && player.getPlayerPos().x <= 600 && player.getPlayerPos().y >= 1345 && player.getPlayerPos().y <= 1625) {
		door.setisOpen(true);
		walls[30].disappear();
		walls[31].disappear();
		door.moveDoors();
		return;
	}
	door.setisOpen(false);
	walls[30].appear(12, 90);
	walls[31].appear(12, 90);
	door.moveDoors();
	return;
}

int Game::weaponPickup()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i].geteDead() || !enemies[i].getWeapon()->getisDropped()) {
			continue;
		}
		if (player.playerWeaponColl(enemies[i].getSprite()) == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			player.pickWeapon(enemies[i].gethasWeapon());
			pickupsfx.play();
			enemies[i].getWeapon()->setisDropped(false);
		}
	}
	return 0;
}

//Update Functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
				break;
			}
			if (this->ev.key.code == sf::Keyboard::X) {
				isStarted = true;
				break;
			}
		}
	}
}

void Game::updateMousePositions() {
	//Updates the mouse position, relative to window(vector2i)
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateCharacters() {
	player.updatePlayer(playerCollide);
	player.shoot();
	for (size_t j = 0; j < enemies.size(); j++) {
		enemies[j].enemyshoot();
		if (!enemies[j].geteDead())
			enemies[j].detectPlayer(player.getPlayerPos());
		else
			enemies[j].floatWeapons();
	}
}

void Game::updateProgress() {
	sf::Vector2f offsetProgress(180, 200);
	if (enemiesleft > 0) {
		ProgressText.setString("Enemies Left: " + to_string(enemiesleft));
		ProgressText.setPosition(player.getPlayerPos() + offsetProgress);
	}
	else if (enemiesleft == 0) {
		offsetProgress.x -= 20;
		ProgressText.setString("Get to the Bike");
		ProgressText.setPosition(player.getPlayerPos() + offsetProgress);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.getPlayerPos().x >= 750.f && player.getPlayerPos().x <= 950.f && player.getPlayerPos().y >= -80.f && player.getPlayerPos().y <= 11.f) {
			bikesfx.play();
			hasWon = true;
		}
	}
}

void Game::update()
{
	this->pollEvents();
	if (isStarted) {
		if (player.getpDead()) {
			this->GameOver();
		}
		else if (this->hasWon) {
			this->updateView();
			this->GameWon();
		}
		else
		{
			
			this->updateView();
			this->updateMousePositions();
			this->updateProgress();
			this->updateCharacters();
			this->windowbounds();
			this->wallColl();
			this->enemybulletColl();
			this->playerbulletColl();
			this->bulletWallColl();
			this->weaponPickup();
			this->senseDoors();
		}
	}
}

void Game::render()
{
	/*
		-clear old frame
		-render all objects
		-display new frame in window
		Renders the game objects
	*/
	this->window->clear();

	if (!isStarted) {
		if (blink < 0) {
			blink = 255;
		}
		Starttext.setFillColor(sf::Color(255, 255, 255, blink));
		blink -= 10;
		this->window->draw(TitleBGspr);
		this->window->draw(Titletext);
		this->window->draw(Starttext);
	}
	else if (hasWon) {
		this->window->draw(winSpr);
		this->window->draw(creditsSpr);
	}
	else {
		//Draw Background
		this->window->draw(bgSpr);

		//Draw Walls
		for (auto i : walls) {
			window->draw(i.getwall());
		}
		//Draw Doors
		this->window->draw(door.getSprite());

		//Draw Enemy,their bullets and dropped weapons
		for (size_t i = 0; i < enemies.size(); i++) {
			this->window->draw(enemies[i].getSprite());

			if (enemies[i].getWeapon()->getisDropped())
				this->window->draw(enemies[i].getWeapon()->getSprite());

			for (size_t j = 0; j < enemies[i].getWeapon()->getBulletsVector()->size(); j++)
			{
				this->window->draw(enemies[i].getWeapon()->getBulletsVector()->at(j).getSprite());
			}
		}

		//Draw Player and their bullets
		this->window->draw(player.getSprite());
		for (size_t i = 0; i < player.getWeaponptr()->getBulletsVector()->size(); i++) {
			this->window->draw(player.getWeaponptr()->getBulletsVector()->at(i).getSprite());
		}

		//Draw Progress Text
		this->window->draw(this->ProgressText);

		//Draw Bike Text
		if (enemiesleft == 0) {
			if (blink < 0) {
				blink = 255;
			}
			BikeText.setFillColor(sf::Color(255, 255, 255, blink));
			blink -= 10;
			this->window->draw(this->BikeText);
		}

		//Draw Health
		if (!player.getpDead())
			this->window->draw(player.getHealthSprite());

		//Draw Gameover screen
		if (player.getpDead()) {
			this->window->draw(GameoverText);
			this->window->draw(EscText);
		}
	}
	//Display frame
	this->window->display();

}