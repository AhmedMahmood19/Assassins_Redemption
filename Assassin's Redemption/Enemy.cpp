#include "Enemy.h"



///////////////////////     ACCESSORS      ///////////////
Enemy::Enemy(sf::Vector2f pos, int a) :angle(0), patrolmagnitude(0), magnitude(0), shoottimer(0), collides(false), stopPatrol(true), eDead(false), i(0)
{
    isWalker = false;
    spawnPos = pos;
    eSpr.setPosition(pos);
    cout << a;
    if (a == 1)
        hasPistol = true;
    else if (a == 2)
        hasUzi = true;
    else if (a == 3)
        hasShotgun = true;

}
Enemy::Enemy(sf::Vector2f pos, sf::Vector2f Ppos, int a) : angle(0), patrolmagnitude(0), magnitude(0), shoottimer(0), collides(false), stopPatrol(false), eDead(false), i(0)
{
    isWalker = true;
    spawnPos = pos;
    patrolPos = Ppos;
    eSpr.setPosition(pos);
    cout << a;
    if (a == 1)
        hasPistol = true;
    else if (a == 2)
        hasUzi = true;
    else if (a == 3)
        hasShotgun = true;
    
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

int Enemy::enemy_bulletColl(sf::Vector2f Pos)
{
    int flag = 0;
    if (eSpr.getGlobalBounds().contains(Pos))
    {
        flag = 1;
    }

    return flag;
}

void Enemy::enemyshoot()
{
    if (hasPistol)
    {

        b2.rotateSprite(angle);
        if (shoottimer < 22)
            shoottimer++;
        if (shoottimer >= 22)
        {
            shoottimer = 0;
            b2.setSpritePos(this->getEnemyPos());
            b2.setcurrentVel(b2.getMaxSpd() * aimDirNorm);
            bullets.push_back(Bullet(b2));
            cout << "Shooting Pistol";
        }
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].moveSprite();

        }
    }
    else if (hasUzi)
    {
        b2.rotateSprite(angle);
        if (shoottimer < 10)
            shoottimer++;
        if (shoottimer >= 10)
        {
            shoottimer = 0;
            b2.setSpritePos(this->getEnemyPos());
            b2.setcurrentVel(b2.getMaxSpd() * aimDirNorm);
            bullets.push_back(Bullet(b2));
            cout << "Shooting Uzi";
        }
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].moveSprite();

        }
    }
    else if (hasShotgun)
    {
            b2.rotateSprite(angle);
            if (shoottimer < 50)
                shoottimer++;
            if (shoottimer >= 50)
            {
                shoottimer = 0;
                b2.setSpritePos(this->getEnemyPos());
                b2.setcurrentVel(b2.getMaxSpd() * aimDirNorm);
                bullets.push_back(Bullet(b2));
                cout << "Shooting Shotgun";
            }
            for (size_t i = 0; i < bullets.size(); i++) 
            {
                bullets[i].moveSprite();

            }
    }
}

void Enemy::lookAt(sf::Vector2f &aimDir) {
    
    const float PI = 3.14159265f;

    angle = static_cast<float> (atan(aimDir.y / aimDir.x) * 180.0 / PI);
 
    if (aimDir.x < 0)
    {
        if (aimDir.y <= 0)
        {
            angle += 180;
        }
        else if (aimDir.y > 0)
        {
            angle += 180;
        }
    }
    else if (aimDir.x >= 0)
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
    //Enemy walks in a path from spawnPos to patrolPos and back, till a player is detected
    if (getEnemyPos() == spawnPos) {
        dest = patrolPos;
    }
    else if (getEnemyPos() == patrolPos) {
        dest = spawnPos;
    }
    calcPath(dest, patrolaimDir,patrolmagnitude, patrolaimDirNorm);
    lookAt(patrolaimDir);
    eSpr.move(patrolaimDirNorm);
    updateEnemySprite();
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
    if (magnitude <= 200 && magnitude >= 70) {
        stopPatrol = true;
        lookAt(aimDir);
        chasePlayer();
        enemyshoot();
    }
    else if (magnitude < 70)
    {
        stopPatrol = true;
        lookAt(aimDir);
        enemyshoot();
    }
    else if ((isWalker == true) && (stopPatrol == false)) {
        patrol();
    }
}
bool Enemy::geteDead() {
    return eDead;
}

void Enemy::enemyDies() {
    setSprite("sprEDead.png");
    eDead = true;
}