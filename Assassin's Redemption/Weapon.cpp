#include "Weapon.h"

void Weapon::setisDropped(bool a)
{
    isDropped = a;
}

bool Weapon::getisDropped()
{
    return isDropped;
}

sf::Sprite Weapon::getSprite()
{
    return wSpr;
}

sf::Sprite* Weapon::getSpritePtr()
{
    return &wSpr;
}

sf::Texture Weapon::getTexture()
{
    return wTex;
}

void Weapon::setSprite(std::string file)
{
    //Sets Sprite of Weapon, used for pick and drop
    if (!wTex.loadFromFile(file))
        return;
    wSpr.setScale(1, 1);
    wSpr.setTexture(wTex);
    wSpr.setTextureRect(sf::IntRect(0, 0, 72, 32));
    wSpr.setOrigin(16.f, 16.f);
}

sf::Sprite Weapon::getbulletSpr(int i)
{
    return bullets[i].getSprite();
}

vector<Bullet>* Weapon::getBulletsVector() {
    return &bullets;
}

int Weapon::PlayerWepColl(sf::Sprite)
{
    return 0;
}

Bullet* Weapon::getb1ptr()
{
    return &b1;
}