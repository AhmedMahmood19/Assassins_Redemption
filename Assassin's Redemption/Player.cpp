#include "Player.h"




sf::Vector2f Player::sendbulletPos(int i)
{
    
    return bullets[i].bGetPos();
}

sf::Sprite Player::send_bSpr(int i)
{
    return bullets[i].getSprite();
}

///////////////////////     ACCESSORS      ///////////////
void Player::setSprite(string file) {
    if (!pTex.loadFromFile(file))
        return;
    pSpr.setScale(2, 2);
    pSpr.setTexture(pTex);
    pSpr.setTextureRect(sf::IntRect(0, 0, 32, 32));
    pSpr.setOrigin(16.f, 16.f);
    //set sprite for bullet
    b1.setSprite("sprM16Shell.png");
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
vector<Bullet>* Player::getBulletsVector() {
    return &bullets;
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
    i += 32;
    if (i == 256)
        i = 0;
    pSpr.setTexture(pTex);
    pSpr.setTextureRect(sf::IntRect(i, 0, 32, 32));
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
    b1.rotateSprite(angle);
    if (shoottimer < 10 )
    {
        shoottimer++;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shoottimer >= 10)
    {
        shoottimer = 0;
        b1.setSpritePos(this->getPlayerPos());
        b1.setcurrentVel(b1.getMaxSpd() * aimDirNorm);
       
        bullets.push_back(Bullet(b1));
        
   
    }
    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i].moveSprite();
        
    }
}