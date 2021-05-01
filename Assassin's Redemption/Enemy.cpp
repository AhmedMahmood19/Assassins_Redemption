#include "Enemy.h"

///////////////////////     ACCESSORS      ///////////////
void Enemy::setSprite(string file) {
    if (!eTex.loadFromFile(file))
        return;
    eSpr.setScale(2, 2);
    eSpr.setTexture(eTex);
    eSpr.setTextureRect(sf::IntRect(0, 0, 32, 32));
    eSpr.setOrigin(16.f, 12.f);
    //set sprite for bullet
    b1.setSprite("sprM16Shell.png");
}
Enemy::Enemy(sf::Vector2f pos) {
    collides = 0;
    eSpr.setPosition(pos);
}
void Enemy::setEnemyPos(float x, float y)
{
    this->eSpr.setPosition(x, y);
}
void Enemy::setCollides(bool c) {
    collides = c;
}
bool Enemy::getCollides(){
    return collides;
}
sf::Sprite Enemy::getSprite() {
    return eSpr;
}
sf::Texture Enemy::getTexture() {
    return eTex;
}
sf::Vector2f Enemy::getEnemyPos() {
    return eSpr.getPosition();
}
sf::Vector2f Enemy::getAimDirNorm() {
    return aimDirNorm;
}
vector<Bullet>* Enemy::getBulletsVector() {
    return &bullets;
}
float Enemy::getAngle() {
    return angle;
}
void Enemy::setPtrmousePos(sf::Vector2i& mouse) {
    PtrmousePos = &mouse;
}
//////////////////////////////////////////////////////////

void Enemy::updateEnemySprite() {
    static int i = 0;
    i += 32;
    if (i == 256)
        i = 0;
    eSpr.setTexture(eTex);
    eSpr.setTextureRect(sf::IntRect(i, 0, 32, 24));
}
void Enemy::calcDir(sf::Vector2f player) {
    aimDir = sf::Vector2f((player.x - getEnemyPos().x), (player.y - getEnemyPos().y));
    magnitude = static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
    aimDirNorm = sf::Vector2f((aimDir.x / magnitude), (aimDir.y / magnitude));
}
void Enemy::lookAtPlayer(sf::Vector2f player) {
    // We have both the player position and the Enemy position 
    // This calculation will make Enemy face the player

    const float PI = 3.14159265f;
    calcDir(player);
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
    eSpr.setRotation(angle);
}

void Enemy::chasePlayer() {
    if (collides==false)
    {
        //If no collision
        PrevPos = eSpr.getPosition();
        eSpr.move(aimDirNorm);
        updateEnemySprite();
    }
    if (collides == true)
    {
        //If collision
        eSpr.setPosition(PrevPos.x, PrevPos.y);
        collides=false;
    }
}

int Enemy::detectPlayer(sf::Vector2f player) {
    calcDir(player);
    if (magnitude <= 200 && magnitude>=70) {
        lookAtPlayer(player);
        chasePlayer();

        return 1;
    }
    else if (magnitude <70 )
    {
        lookAtPlayer(player);
        stop();
    }
    else {
        //cout << "Player is not close!\n";
        return 0;
    }
}

void Enemy::shoot() {
    b1.rotateSprite(angle);
    

        b1.setSpritePos(this->getEnemyPos());
        b1.setcurrentVel(b1.getMaxSpd() * aimDirNorm);
        bullets.push_back(Bullet(b1));
    
    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i].moveSprite();
    }
}

void Enemy::stop()
{
    eSpr.move(oldpos.x, oldpos.y);
}
