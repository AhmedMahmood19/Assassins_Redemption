#include "Game.h"

using namespace std;
void Game::initVariables()
{
    this->window = nullptr;

    //Game Logic
    flag = 0;
    player.setSprite("sprPWalkUnarmed2_strip8.png");
    if (!bgTex.loadFromFile("beachmap.png"))
        return;
    bgSpr.setTexture(bgTex);
    bgSpr.setScale(2.5,2.5);
    bgSpr.setOrigin(170,100);

    //Hardcoding Walls
    walls.push_back(Wall(10, 715, -260, -110));
    walls.push_back(Wall(808, 10, -260, -120));
    walls.push_back(Wall(10, 60, 543, -115));
    walls.push_back(Wall(10, 78, 543, 40));
    walls.push_back(Wall(1280, 10, 545, 120));
    walls.push_back(Wall(1358, 12, 465, 1560));
    walls.push_back(Wall(10, 60, 465, 1320));
    walls.push_back(Wall(1015, 12, -165, 1320));
    walls.push_back(Wall(10, 715, -178, 610));
    walls.push_back(Wall(80, 12, -255, 595));
    walls.push_back(Wall(60, 12, -170, 1080));
    walls.push_back(Wall(310, 12, -10, 1080));
    walls.push_back(Wall(10, 240, 300, 1080));
    walls.push_back(Wall(540, 12, -15, 605));
    walls.push_back(Wall(540, 12, -15, 605));
    walls.push_back(Wall(10, 60, -15, 600));
    walls.push_back(Wall(10, 75, -15, 845));
    walls.push_back(Wall(885, 12, -10, 920));
    walls.push_back(Wall(10, 390, 868, 525));
    walls.push_back(Wall(220, 12, 715, 520));
    walls.push_back(Wall(10, 155, 700, 360));
    walls.push_back(Wall(160, 12, 540, 440));
    walls.push_back(Wall(10, 60, 545, 440));
    walls.push_back(Wall(10, 385, 1182, 130));
    walls.push_back(Wall(160, 12, 1025, 520));
    walls.push_back(Wall(10, 55, 705, 120));
    walls.push_back(Wall(10, 205, 1100, 530));
    walls.push_back(Wall(10, 395, 1100, 920));
    walls.push_back(Wall(165, 12, 940, 1315));
    walls.push_back(Wall(10, 230, 1022, 1330));
};

void Game::initWindow()
{
    this->videoMode.height = 480;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "My game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
};

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

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

//Functions
int Game::collisions()
{
    for (size_t i = 0; i < walls.size(); i++) {
        if (walls[i].wallcoll(player.getSprite())) {
            flag = 1;
            break;
        }
        else flag = 0;
    }
    return flag;
}



void Game::drawWalls()
{
    for (auto i : walls) {
        window->draw(i.getwall());
    }
}

void Game::windowbounds()
{

    //player 
    
    //left
    if (player.getPlayerPos().x <= -415.f)
        player.setPosition(-415,player.getPlayerPos().y);
    //right
    if (this->player.getPlayerPos().x >= 1825.f)
        this->player.setPosition(1825, player.getPlayerPos().y);
    //up
    if (this->player.getPlayerPos().y <= -255.f)
        this->player.setPosition(player.getPlayerPos().x,-255.f);
    //down
    if (this->player.getPlayerPos().y >= 1625.f)
        this->player.setPosition(player.getPlayerPos().x, 1625.f);
   

}

void Game::bulletWallColl()
{
    for (size_t i = 0; i < walls.size(); i++) {
        for (size_t j = 0; j < player.getBulletsVector()->size(); j++)
        {
            if (walls[i].wallCollision(player.sendbulletPos(j)) == 1 || walls[i].wallcoll(player.send_bSpr(j)) || collisions()==1 )
            {
                
                player.getBulletsVector()->erase(player.getBulletsVector()->begin()+j);
                
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
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
    
    player.updatePlayer(flag);
    player.shoot();
}


void Game::updateMousePositions() {
    //Updates the mouse position, relative to window(vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::update()
{
    this->windowbounds();
    this->collisions();
    this->bulletWallColl();

    this->updateView();
    this->updateMousePositions();

    this->pollEvents();

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
    //Draw Background
    this->window->draw(bgSpr);

    //Draw Walls
    drawWalls();
    
    //Draw game objects
    this->window->draw(player.getSprite());
    for (size_t i = 0; i < player.getBulletsVector()->size(); i++)
        this->window->draw(player.getBulletsVector()->at(i).getSprite());
    
    //Display frame
    this->window->display();
}