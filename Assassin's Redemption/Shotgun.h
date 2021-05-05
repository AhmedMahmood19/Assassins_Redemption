#pragma once
#include "Weapon.h"
class Shotgun :
    public Weapon
{
    int wep_timer = 40;
    void ab_class();
    virtual int getWepTimer();

};

