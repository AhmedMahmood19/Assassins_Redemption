#include "Weapon.h"

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
    if (!wTex.loadFromFile(file))
        return;
    wSpr.setScale(1, 1);
    wSpr.setTexture(wTex);
    wSpr.setTextureRect(sf::IntRect(0, 0, 72, 32));
    wSpr.setOrigin(16.f, 16.f);

    //bullet sprite;
    b1.setSprite("sprM16Shell.png");
}

sf::Sprite Weapon::getbulletSpr(int i)
{
    return bullets[i].getSprite();
}

vector<Bullet>* Weapon::getBulletsVector() {
    return &bullets;
}

int Weapon::P_WepColl(sf::Sprite)
{
    return 0;
}

Bullet* Weapon::getb1ptr()
{
    return &b1;
}

Bullet Weapon::getb1() {
    return b1;
}