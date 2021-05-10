#include "Game.h"

using namespace std;
void Game::initVariables()
{
    this->window = nullptr;

    initStartScreen();
    //Game Logic
    playerCollide = 0;
    player.setSprite("sprPWalkMagnum_strip8.png");
    player.setPosition(350.f, 1450.f);
    if (!bgTex.loadFromFile("beachmap.png"))
        return;
    bgSpr.setTexture(bgTex);
    bgSpr.setScale(2.5,2.5);
    bgSpr.setOrigin(170,100);
    //Todo: Hardcoding a pistol
    shotgun.setSprite("sprShotgun.png");
    shotgun.getSpritePtr()->setPosition(370.f, 1390.f);

    uzi.setSprite("sprUzi.png");
    uzi.getSpritePtr()->setPosition(420.f, 1480.f);

    pistol.setSprite("sprMagnum.png");
    pistol.getSpritePtr()->setPosition(270.f, 1480.f);
    //
    initWalls();
    initEnemies();
    door.initDoor("doors.png");
}
void Game::initStartScreen()
{
    blink = 255;
    isStarted = false;
    if (!Titlefont.loadFromFile("Fonts\\Doctor Glitch.otf"))
        return;
    if (!Startfont.loadFromFile("Fonts\\Distortion Dos Analogue.otf"))
        return;
    if (!TitleBGtex.loadFromFile("screen/WaterP.png"))
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
    enemies.push_back(Enemy(sf::Vector2f(500.f, 700.f)));
    enemies.push_back(Enemy(sf::Vector2f(420.f, 1130.f), sf::Vector2f(900.f, 1130.f)));
    enemies.push_back(Enemy(sf::Vector2f(977.f, 577.f), sf::Vector2f(977.f, 1111.f)));
    enemies.push_back(Enemy(sf::Vector2f(800.f, 1370.f), sf::Vector2f(800.f, 1530.f)));
    enemies[0].setSprite("sprEWalkM16_strip8.png");
    enemies[1].setSprite("sprEWalkM16_strip8.png");
    enemies[2].setSprite("sprEWalkM16_strip8.png");
    enemies[3].setSprite("sprEWalkM16_strip8.png");
    
    //TODO Hardcode more enemies
    //enemies.push_back(Enemy(sf::Vector2f( x , y )));
    //enemies[i].setSprite("sprEWalkM16_strip8.png");
}

void Game::GameOver() {
    sf::Vector2f offset(-320,-200);
    GameoverText.setPosition(player.getPlayerPos()+offset);
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

void Game::updateView() {
    this->view = new sf::View(sf::Vector2f(player.getPlayerPos()), sf::Vector2f(800.f, 480.f));
    window->setView(*view);
}


//Constructors and Destructor
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

//Functions
void Game::collisions()
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
            if (walls[i].wallcolCont(enemies[j].getEnemyPos())) {
                enemies[j].setCollides(true);
                break;
            }
            else enemies[j].setCollides(false);
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
}
void Game::bulletWallColl()
{
    for (size_t i = 0; i < walls.size(); i++) {
        for (size_t j = 0; j < player.getWeaponptr()->getBulletsVector()->size(); j++)
        {
            if (walls[i].wallcolInter(player.getWeaponptr()->getbulletSpr(j))==1  )
            {
                player.getWeaponptr()->getBulletsVector()->erase(player.getWeaponptr()->getBulletsVector()->begin()+j);   
            }
        }
        
    }

}
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
            if (this->ev.key.code == sf::Keyboard::X){
                isStarted = true;
            break;
            }
            //Player dying todo
            if (this->ev.key.code == sf::Keyboard::P) {
                player.playerDies();
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
        if(!enemies[j].geteDead())
            enemies[j].detectPlayer(player.getPlayerPos());
    }
}
void Game::update()
{
    this->pollEvents();
    //Player dying todo
    if (isStarted) {
        if (player.getpDead()) {
            this->GameOver();
        }
        else
        {
            this->updateView();
            this->updateMousePositions();
            this->updateCharacters();
            this->windowbounds();
            this->collisions();
            this->enembullColl();
            this->bulletWallColl();
            this->wepCheck();
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
    else{
        //Draw Background
        this->window->draw(bgSpr);

        //Draw Walls
        for (auto i : walls) {
            window->draw(i.getwall());
        }

        //Draw Doors
        this->window->draw(door.getSprite());

        //Draw Enemy and their bullets(todo)
        for (size_t j = 0; j < enemies.size(); j++) {
            this->window->draw(enemies[j].getSprite());
        }

        //Todo: Hardcoding Guns
        //floatWeapons(); //Floating Weapons Prototype
        this->window->draw(shotgun.getSprite());
        this->window->draw(uzi.getSprite());
        this->window->draw(pistol.getSprite());

        //Draw Player and their bullets
        this->window->draw(player.getSprite());
        for (size_t i = 0; i < player.getWeaponptr()->getBulletsVector()->size(); i++) {
            this->window->draw(player.getWeaponptr()->getBulletsVector()->at(i).getSprite());
        }
        //TODO 
        if (player.getpDead()) {
            this->window->draw(GameoverText);
            this->window->draw(EscText);
        }
    }
    //Display frame
    this->window->display();
    
}
void Game::senseDoors(){
    sf::Vector2f sensor;
    if (player.getPlayerPos().x >= 377 && player.getPlayerPos().x <= 600) {
        if (player.getPlayerPos().y >= 1345 && player.getPlayerPos().y <= 1625) {
            door.setisOpen(true);
            walls[30].disappear();
            walls[31].disappear();
            door.moveDoors();
        }
    }
    else {
        door.setisOpen(false);
        walls[30].appear(12,90);
        walls[31].appear(12,90);
        door.moveDoors();
    }
}

int Game::wepCheck()
{
    if (player.playerWeaponColl(uzi.getSprite()) == 1 || ev.type==sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::Space)
        {
            //sets weapon and updates playersprite with the player sprite containing this gun 
            player.setWeapon(&uzi);
            player.setSprite(uziTex);
            player.getWeaponptr()->getb1ptr()->setSprite("sprUziShell.png");
            

        }
    }
    if (player.playerWeaponColl(pistol.getSprite()) == 1 || ev.type==sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::Space)
        {
            //sets weapon and updates playersprite with the player sprite containing this gun 
            player.setWeapon(&pistol);
            player.setSprite(pistolTex);
            player.getWeaponptr()->getb1ptr()->setSprite("sprM16Shell.png");
        }
    }
    if (player.playerWeaponColl(shotgun.getSprite()) == 1 || ev.type == sf::Event::KeyPressed)
    {
        
        if (ev.key.code == sf::Keyboard::Space)
        {
            //sets weapon and updates playersprite with the player sprite containing this gun 
            player.setWeapon(&shotgun);
            player.setSprite(shotgunTex);
            player.getWeaponptr()->getb1ptr()->setShotgunBulletSprite("sprShot.png");
        }
    }
    return 0;
}

void Game::enembullColl()
{
    for (size_t i = 0; i < enemies.size(); i++) {
        for (size_t j = 0; j < player.getWeaponptr()->getBulletsVector()->size(); j++)
        {
            if (enemies[i].enemy_bulletColl(player.getWeaponptr()->getbulletSpr(j).getPosition()) == 1 && !enemies[i].geteDead())
            {
                if (1) {
                    enemies[i].enemyDies();
                    player.getWeaponptr()->getBulletsVector()->erase(player.getWeaponptr()->getBulletsVector()->begin() + j);
                }
            }
        }

    }
}
//Floating Weapons Prototype
//void Game::floatWeapons()
//{
//    static int i = 0;
//    if (i < 10) {
//        shotgun.getSpritePtr()->move(0, 0.5);
//        i++;
//    }
//    else if (i >= 10 && i < 20) {
//        shotgun.getSpritePtr()->move(0,-0.5);
//        i++;
//    }
//    else if (i == 20) {
//        i = 0;
//    }
//}
