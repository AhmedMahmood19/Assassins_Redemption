#pragma once
#include "Weapon.h"
class Uzi : public Weapon
{
private:
    int wep_timer = 10;
public:
    virtual int getWepTimer();
};