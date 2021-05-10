#include "Player.h"


Player::Player():PtrmousePos(0),angle(0),magnitude(0),pDead(0){
    wep = &pistol;
}

///////////////////////     ACCESSORS      ///////////////
void Player::setSprite(string file) {
    if (!pTex.loadFromFile(file))
        return;
    pSpr.setScale(2, 2);
    pSpr.setTexture(pTex);
    pSpr.setTextureRect(sf::IntRect(0, 0, 44, 32));
    pSpr.setOrigin(16.f, 16.f);
    wep->getb1ptr()->setSprite("sprM16Shell.png");
}
void Player::setPosition(float x, float y)
{
    this->pSpr.setPosition(x,y);
}
sf::Sprite Player::getSprite() {
    return pSpr;
}
sf::Texture Player::getTexture() {
    return pTex;
}
sf::Vector2f Player::getPlayerPos() {
    return pSpr.getPosition();
}
sf::Vector2f Player::getAimDirNorm() {
    return aimDirNorm;
}

Weapon* Player::getWeaponptr()
{
    return wep;
}

float Player::getAngle() {
    return angle;
}

void Player::setPtrmousePos(sf::Vector2i& mouse) {
    PtrmousePos = &mouse;
}
//////////////////////////////////////////////////////////

void Player::updatePlayerSprite() {
    static int i = 0;
    i += 44;
    if (i == 352)
        i = 0;
    pSpr.setTexture(pTex);
    pSpr.setTextureRect(sf::IntRect(i, 0, 44, 32));
}
void Player::lookAtMouse() {
    // We have both the mouse position and the player position 
    // This calculation will make player face the position of the mouse

    const float PI = 3.14159265f;
    sf::Vector2f viewPos= sf::Vector2f(400.f,240.f);
    aimDir = sf::Vector2f((PtrmousePos->x - viewPos.x), (PtrmousePos->y - viewPos.y));
    magnitude = static_cast<float>( sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
    aimDirNorm = sf::Vector2f((aimDir.x / magnitude), (aimDir.y / magnitude));
    angle = static_cast<float> (atan(aimDir.y / aimDir.x) * 180.0 / PI);

    if (aimDir.x < 0)
    {
        if (aimDir.y < 0)
        {
            angle += 180;
        }
        else if (aimDir.y > 0)
        {
            angle += 180;
        }
    }
    else if (aimDir.x > 0)
    {
        if (aimDir.y < 0)
        {
            angle += 360;
        }
        else if (aimDir.y > 0)
        {
            angle += 0;
        }
    }
    pSpr.setRotation(angle);
}

void Player::updatePlayer(int flag) {
    lookAtMouse();
    if (flag != 1)
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            PrevPos = pSpr.getPosition();
            pSpr.move(-3.f,-3.f);
            updatePlayerSprite();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            PrevPos = pSpr.getPosition();
            pSpr.move(3.f, -3.f);
            updatePlayerSprite();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            PrevPos = pSpr.getPosition();
            pSpr.move(-3.f, 3.f);
            updatePlayerSprite();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            PrevPos = pSpr.getPosition();
            pSpr.move(3.f, 3.f);
            updatePlayerSprite();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
            PrevPos=pSpr.getPosition();
            pSpr.move(-3.f, 0.f);
            updatePlayerSprite();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
            PrevPos = pSpr.getPosition();
            pSpr.move(3.f, 0.f);
            updatePlayerSprite();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
            PrevPos = pSpr.getPosition();
            pSpr.move(0.f, -3.f);
            updatePlayerSprite();
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
            PrevPos = pSpr.getPosition();
            pSpr.move(0.f, 3.f);
            updatePlayerSprite();
        }
    }
    if (flag == 1)
    {
        pSpr.setPosition(PrevPos.x, PrevPos.y);
        flag = 0;
    }
}
void Player::shoot() {   
    
    wep->getb1ptr()->rotateSprite(angle);
    if (shoottimer < wep->getWepTimer() )
    {
        shoottimer++;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shoottimer >= wep->getWepTimer())
    {
        shoottimer = 0;
        wep->getb1ptr()->setSpritePos(this->getPlayerPos());
        wep->getb1ptr()->setcurrentVel(wep->getb1ptr()->getMaxSpd() * aimDirNorm);
       
        wep->getBulletsVector()->push_back(Bullet(wep->getb1()));
    }
    for (size_t i = 0; i < wep->getBulletsVector()->size(); i++) {
        wep->getBulletsVector()->at(i).moveSprite();
    }
}

void Player::setWeapon(Weapon* a)
{
    wep = a;
}

int Player::playerWeaponColl(sf::Sprite x)
{
    int flag;
    if (pSpr.getGlobalBounds().contains(x.getPosition()))
    {
        flag = 1;
    }
    else
        flag = 0;
    return flag;
}

bool Player::getpDead() {
    return pDead;
}

void Player::playerDies() {
    setSprite("sprPDead.png");
    pDead=true;
}
