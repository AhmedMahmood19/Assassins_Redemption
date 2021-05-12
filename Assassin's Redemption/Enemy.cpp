#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, int a) : stopPatrol(true)
{
	isWalker = false;
	spawnPos = pos;
	eSpr.setPosition(pos);
	if (a == 1)
		hasPistol = true;
	else if (a == 2)
		hasUzi = true;
	else if (a == 3)
		hasShotgun = true;

}
Enemy::Enemy(sf::Vector2f pos, sf::Vector2f Ppos, int a) : stopPatrol(false)
{
	isWalker = true;
	spawnPos = pos;
	patrolPos = Ppos;
	eSpr.setPosition(pos);
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
	eSpr.setOrigin(16.f, 16.f);
	if (hasPistol) {
		pistol.getb1ptr()->setSprite("sprM16Shell.png");
		pistol.setSprite("sprMagnum.png");
	}
	else if (hasUzi) {
		uzi.getb1ptr()->setSprite("sprM16Shell.png");
		uzi.setSprite("sprUzi.png");
	}
	else if (hasShotgun) {
		shotgun.getb1ptr()->setSprite("sprShot.png");
		shotgun.setSprite("sprShotgun.png");
	}
}

void Enemy::setEnemyPos(float x, float y)
{
	this->eSpr.setPosition(x, y);
}

void Enemy::setCollides(bool c) {
	collides = c;
}

bool Enemy::getCollides() {
	return collides;
}

sf::Sprite Enemy::getSprite() {
	return eSpr;
}

sf::Vector2f Enemy::getEnemyPos() {
	return eSpr.getPosition();
}

bool Enemy::geteDead() {
	return eDead;
}

Weapon* Enemy::getWeapon() {
	if (hasPistol)
		return &pistol;
	else if (hasUzi)
		return &uzi;
	else if (hasShotgun)
		return &shotgun;
	else {
		cout << "\nError in Enemy::getWeapon";
		return NULL;
	}
}

void Enemy::updateEnemySprite() {
	i += 32;
	if (i == 256)
		i = 0;
	eSpr.setTexture(eTex);
	eSpr.setTextureRect(sf::IntRect(i, 0, 32, 24));
}

///////////////////////////////////////////
void Enemy::calcPath(sf::Vector2f dest, sf::Vector2f& Dir, float& Mag, sf::Vector2f& Norm) {
	Dir = sf::Vector2f((dest.x - getEnemyPos().x), (dest.y - getEnemyPos().y));
	Mag = static_cast<float>(sqrt(pow(Dir.x, 2) + pow(Dir.y, 2)));
	Norm = sf::Vector2f((Dir.x / Mag), (Dir.y / Mag));
}

void Enemy::enemyshoot()
{
	if (startShooting)
	{
		getWeapon()->getb1ptr()->rotateSprite(angle);
		if (shoottimer < getWeapon()->getWepTimer())
			shoottimer++;
		if (shoottimer >= getWeapon()->getWepTimer())
		{
			shoottimer = 0;
			getWeapon()->getb1ptr()->setSpritePos(this->getEnemyPos());
			getWeapon()->getb1ptr()->setcurrentVel(getWeapon()->getb1ptr()->getMaxSpd() * aimDirNorm);
			getWeapon()->getBulletsVector()->push_back(Bullet(*getWeapon()->getb1ptr()));
		}
	}
	for (size_t i = 0; i < getWeapon()->getBulletsVector()->size(); i++) {
		getWeapon()->getBulletsVector()->at(i).moveSprite();
	}
}

void Enemy::lookAt(sf::Vector2f& aimDir) {

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
	calcPath(dest, patrolaimDir, patrolmagnitude, patrolaimDirNorm);
	lookAt(patrolaimDir);
	eSpr.move(patrolaimDirNorm);
	updateEnemySprite();
}

void Enemy::chasePlayer() {
	if (collides == false)
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
		collides = false;
	}
}

void Enemy::detectPlayer(sf::Vector2f player) {
	calcPath(player, aimDir, magnitude, aimDirNorm);
	if (magnitude <= 200 && magnitude >= 70) {
		stopPatrol = true;
		lookAt(aimDir);
		chasePlayer();
		startShooting = true;
	}
	else if (magnitude < 70)
	{
		stopPatrol = true;
		lookAt(aimDir);
		startShooting = true;
	}
	else if ((isWalker == true) && (stopPatrol == false)) {
		patrol();
		startShooting = false;
	}
	else
	{
		startShooting = false;
	}
}

void Enemy::enemyDies() {
	startShooting = false;

	setSprite("sprEDead.png");
	dropWeapon(getEnemyPos());
	eDead = true;
}

void Enemy::dropWeapon(sf::Vector2f dropPos) {
	getWeapon()->getSpritePtr()->setPosition(dropPos);
	getWeapon()->setisDropped(true);
	//Todo when user picks up the gun setisDropped(false) and make the sprite disappear
	//Also check in wepPickup when user collides with weapon if getisDropped==true
	//Also while drawing check if each enemy's weapon is dropped or not
}