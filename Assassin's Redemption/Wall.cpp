#include "Wall.h"

Wall::Wall(float w1, float w2,float xPos,float yPos)
{
	rect.setPosition(xPos,yPos);
	rect.setSize(sf::Vector2f(w1, w2));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Transparent);
	rect.setOutlineThickness(1.f);
}



int Wall::wallcolCont(sf::Vector2f Pos)
{
	 int flag = 0;
	 if (rect.getGlobalBounds().contains(Pos))
	 {
		 flag = 1;
		 
	 }
		 
	 return flag;
}

int Wall::wallcolInter(sf::Sprite a)
{
	int flag = 0;
	if (rect.getGlobalBounds().intersects(a.getGlobalBounds()))
	{
		flag = 1;
		
	}

	return flag;
}

sf::RectangleShape Wall::getwall()
{
	return rect;
}
