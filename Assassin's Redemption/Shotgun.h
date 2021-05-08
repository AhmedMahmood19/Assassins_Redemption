#pragma once
#include "Weapon.h"
class Shotgun :
    public Weapon
{
    int wep_timer = 50;
    void ab_class();
    virtual int getWepTimer();

};

