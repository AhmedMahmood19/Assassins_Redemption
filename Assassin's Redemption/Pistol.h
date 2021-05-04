#pragma once
#include "Weapon.h"
class Pistol :
    public Weapon
{
private:

public:
    int wep_timer=30;
    void ab_class();
    virtual int getWepTimer();
    
};

