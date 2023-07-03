#ifndef SOBA_H
#define SOBA_H
#include <MainClass.h>
#include "Vrata.h"
#include "Enemy.h"
#include "SDLsetup.h"
#include "Camera.h"
#include "Fireball.h"

#include <iostream>
//class Vrata;
class Camera;
class Enemy;
class soba
{
private:

public:
    int stenemy;
    bool initcoordinates;

    SDLsetup* setup;
    Enemy *grunt[100];

    SDL_Rect dungeon;

    soba(SDLsetup *,int,int,int);
    ~soba();

    int getx();
    int gety();
    int getw();
    int geth();
    void setsize(int w, int h);
    SDL_Rect getrect();

    void randomnov();
    Vrata *stvrat[10];
    int boss;

    void funkcije(Hero*,Camera*,Fireball* firebal[20]);
    void enemyinit();
    void enemymovement(Hero*);
    void enemycollision();

    bool vsimrtvi();
};

#endif // SOBA_H
