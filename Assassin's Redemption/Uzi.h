#pragma once
#include "Weapon.h"
class Uzi : public Weapon
{
private:
    int wep_timer = 22;
public:
    virtual int getWepTimer();
};