#include "Weapon.h"

sf::Sprite Weapon::getSprite()
{
    return wSpr;
}

sf::Texture Weapon::getTexture()
{
    return wTex;
}

void Weapon::setSprite(std::string file)
{
    if (!wTex.loadFromFile(file))
        return;
    wSpr.setScale(2, 2);
    wSpr.setTexture(wTex);
    wSpr.setTextureRect(sf::IntRect(0, 0, 32, 32));
    wSpr.setOrigin(16.f, 16.f);

    //bullet sprite;
    b1.setSprite("sprM16Shell.png");
}

sf::Vector2f Weapon::getbulletPos(int i)
{

    return bullets[i].bGetPos();
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

Bullet Weapon::getbullet()
{
    return b1;
}

Bullet Weapon::getbullet_at_I(int i)
{
    return bullets[i];
}

Weapon::~Weapon()
{
}
