#include "Enemy.h"

///////////////////////     ACCESSORS      ///////////////
Enemy::Enemy(sf::Vector2f pos, sf::Vector2f Ppos) :angle(0), patrolmagnitude(0), magnitude(0), collides(false), stopPatrol(false)
{
    isWalker = true;
    spawnPos = pos;
    patrolPos = Ppos;
    eSpr.setPosition(pos);
}
Enemy::Enemy(sf::Vector2f pos) :angle(0), patrolmagnitude(0), magnitude(0), collides(false), stopPatrol(true)
{
    isWalker = false;
    spawnPos = pos;
    eSpr.setPosition(pos);
}
void Enemy::setSprite(string file) {
    if (!eTex.loadFromFile(file))
        return;
    eSpr.setScale(2, 2);
    eSpr.setTexture(eTex);
    eSpr.setTextureRect(sf::IntRect(0, 0, 32, 32));
    eSpr.setOrigin(16.f, 12.f);
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
float Enemy::getAngle() {
    return angle;
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

void Enemy::calcPath(sf::Vector2f dest, sf::Vector2f& Dir, float& Mag, sf::Vector2f& Norm) {
    Dir = sf::Vector2f((dest.x - getEnemyPos().x), (dest.y - getEnemyPos().y));
    Mag = static_cast<float>(sqrt(pow(Dir.x, 2) + pow(Dir.y, 2)));
    Norm = sf::Vector2f((Dir.x / Mag), (Dir.y / Mag));
}

void Enemy::lookAtPlayer(sf::Vector2f player) {
    // We have both the player position and the Enemy position 
    // This calculation will make Enemy face the player

    const float PI = 3.14159265f;

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

void Enemy::patrol() {
    //Enemy walks in a path from spawnPos to end and back, till a player is detected
    
    if (getEnemyPos() == spawnPos) {
        //look at angle
        //
        eSpr.move(patrolaimDirNorm);
        updateEnemySprite();
    }
}

void Enemy::chasePlayer() {
    if (collides==false)
    {
        //If no collision
        PosBeforeColl = eSpr.getPosition();
        eSpr.move(aimDirNorm);
        updateEnemySprite();
    }
    if (collides == true)
    {
        //If collision
        eSpr.setPosition(PosBeforeColl.x, PosBeforeColl.y);
        collides=false;
    }
}

void Enemy::detectPlayer(sf::Vector2f player) {
    calcPath(player, aimDir, magnitude, aimDirNorm);
    if (magnitude <= 200 && magnitude>=70) {
        stopPatrol = true;
        lookAtPlayer(player);
        chasePlayer();
    }
    else if (magnitude <70 )
    {
        stopPatrol = true;
        lookAtPlayer(player);
    }
    else if ((isWalker==true) && (stopPatrol==false)) {
        patrol();
    }
}