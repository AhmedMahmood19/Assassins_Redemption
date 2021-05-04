#pragma once
#include "Weapon.h"
class Pistol :
    public Weapon
{
private:

public:
    int wep_timer=10;
    void ab_class();
    virtual int getWepTimer();
    
};

