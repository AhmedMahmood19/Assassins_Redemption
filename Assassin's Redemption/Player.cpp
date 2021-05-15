#include "Player.h"


Player::Player() :PtrmousePos(0), angle(0), magnitude(0), pDead(0) {
	wep = &pistol;
}

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
	this->pSpr.setPosition(x, y);
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

void Player::updatePlayerSprite() {
	static int i = 0;
	i += 44;
	if (i == 352)
		i = 0;
	pSpr.setTexture(pTex);
	pSpr.setTextureRect(sf::IntRect(i, 0, 44, 32));
}

//////////////////////////////////////////////////////////
void Player::lookAtMouse() {
	// We have both the mouse position and the player position 
	// This calculation will make player face the position of the mouse

	const float PI = 3.14159265f;
	sf::Vector2f viewPos = sf::Vector2f(400.f, 240.f);
	aimDir = sf::Vector2f((PtrmousePos->x - viewPos.x), (PtrmousePos->y - viewPos.y));
	magnitude = static_cast<float>(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
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
	updatehealthSpr();
	lookAtMouse();
	if (flag != 1)
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
			PrevPos = pSpr.getPosition();
			pSpr.move(-3.f, -3.f);
			updatePlayerSprite();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
			PrevPos = pSpr.getPosition();
			pSpr.move(3.f, -3.f);
			updatePlayerSprite();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
			PrevPos = pSpr.getPosition();
			pSpr.move(-3.f, 3.f);
			updatePlayerSprite();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
			PrevPos = pSpr.getPosition();
			pSpr.move(3.f, 3.f);
			updatePlayerSprite();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			PrevPos = pSpr.getPosition();
			pSpr.move(-3.f, 0.f);
			updatePlayerSprite();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			PrevPos = pSpr.getPosition();
			pSpr.move(3.f, 0.f);
			updatePlayerSprite();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			PrevPos = pSpr.getPosition();
			pSpr.move(0.f, -3.f);
			updatePlayerSprite();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
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
	if (shoottimer < wep->getWepTimer())
	{
		shoottimer++;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		shoottimer = 0;
		wep->getb1ptr()->setSpritePos(this->getPlayerPos());
		wep->getb1ptr()->setcurrentVel(wep->getb1ptr()->getMaxSpd() * aimDirNorm);
		wep->getBulletsVector()->push_back(Bullet(*wep->getb1ptr()));
	}
	for (size_t i = 0; i < wep->getBulletsVector()->size(); i++) {
		wep->getBulletsVector()->at(i).moveSprite();
	}
}

void Player::pickWeapon(int hasWeapon)
{
	if (hasWeapon == 1) {
		wep = &pistol;
		setSprite("sprPWalkMagnum_strip8.png");
	}
	else if (hasWeapon == 2) {
		wep = &uzi;
		setSprite("sprPWalkUzi_strip8.png");
	}
	else if (hasWeapon == 3) {
		wep = &shotgun;
		setSprite("sprPWalkDoubleBarrel_strip8.png");
		wep->getb1ptr()->setShotgunBulletSprite("sprShotShell.png");
	}
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
	pDead = true;
}

void Player::inithealthBar(){
	if (!healthTex.loadFromFile("sprHealthBar1.png"))
		return;
	healthSpr.setScale(0.5, 0.5);
	healthSpr.setTexture(healthTex);
	healthSpr.setTextureRect(sf::IntRect(0, 0, 367, 80));
}

sf::Sprite Player::getHealthSprite()
{
	return healthSpr;
}

void Player::updatehealthSpr() {
	sf::Vector2f offsetHealth(-400, 200);
	healthSpr.setPosition(getPlayerPos() + offsetHealth);
}

void Player::takeDamage()
{
	static int x = 0;
	health--;
	x += 80;
	healthSpr.setTextureRect(sf::IntRect(0, x, 367, 80));
	if (health == 0) {
		setSprite("sprPDead.png");
		pDead = true;
	}
}
