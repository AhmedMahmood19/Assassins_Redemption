#include "Bullet.h"

Bullet::Bullet()
	:currentVel(0, 0), maxSpd(15.f)
{}
void Bullet::setSprite(string file) {
	if (!bTex.loadFromFile(file))
		return;
	bSpr.setScale(4, 4);
	bSpr.setTexture(bTex);
}
void Bullet::setShotgunBulletSprite(string file){
	if (!bTex.loadFromFile(file))
		return;
	bSpr.setScale(1.5, 1.5);
	bSpr.setTexture(bTex);
	bSpr.setTextureRect(sf::IntRect(0, 0, 4, 12));
}
void Bullet::setSpritePos(sf::Vector2f p) {
	bSpr.setPosition(p);
}
sf::Vector2f Bullet::moveSprite() {
	bSpr.move(currentVel);
	return bSpr.getPosition();
}
void Bullet::rotateSprite(float a) {
	bSpr.setRotation(a);
}
void Bullet::setcurrentVel(sf::Vector2f v) {
	currentVel = v;
}

sf::Sprite Bullet::getSprite() {
	return bSpr;
}
sf::Texture Bullet::getTexture() {
	return bTex;
}
float Bullet::getMaxSpd()const {
	return maxSpd;
}

sf::Vector2f Bullet::bGetPos()
{
	return bSpr.getPosition();
}

int Bullet::bulletColl(sf::Sprite Spr)
{
	int flag = 0;
	if (Spr.getGlobalBounds().contains(bSpr.getPosition()))
	{
		flag = 1;
	}
	return flag;
}