#include "Doors.h"

Doors::Doors():isDoorOpen(false)
{}
void Doors::initDoor(string file)
{
	if (!doorTex.loadFromFile(file))
		return;
	doorSpr.setTexture(doorTex);
	doorSpr.setTextureRect(sf::IntRect(0, 0, 31, 130));
	doorSpr.setPosition(445,1310);
	doorSpr.setScale(2,2.5);
}

sf::Sprite Doors::getSprite()
{
	return doorSpr;
}

bool Doors::getisOpen()
{
	return isDoorOpen;
}

void Doors::setisOpen(bool d)
{
	isDoorOpen = d;
}

void Doors::moveDoors()
{
	static int k = 0;
	static int i = 0;	
	static int j = 0;
	k++;
	if (isDoorOpen == true && (k%2!=0) ) {
		j = 279;
		i += 31;
		if (i <= 279)
		{
			doorSpr.setTextureRect(sf::IntRect(i, 0, 31, 130));
		}
	}
	else if(k % 2 != 0)
	{		
		i = 0;
		if (j >= 31)
		{
			j -= 31;
			doorSpr.setTextureRect(sf::IntRect(j, 0, 31, 130));
		}
	}
}