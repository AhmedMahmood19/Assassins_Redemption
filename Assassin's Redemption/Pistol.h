#pragma once
#include "Weapon.h"
class Pistol : public Weapon
{
private:
    int wep_timer = 32;
public:
    virtual int getWepTimer();  
};