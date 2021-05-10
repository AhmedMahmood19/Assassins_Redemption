#pragma once
#include "Weapon.h"
class Shotgun : public Weapon
{
private:
	int wep_timer = 50;
public:
	virtual int getWepTimer();
};