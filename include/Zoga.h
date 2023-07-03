#ifndef ZOGA_H
#define ZOGA_H


#include "Sprite.h"
#include "Hero.h"
#include "SDLsetup.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>

class Zoga
{
private:
    SDLsetup* setup;
    int init;
    int premikX;
    int premikY;
    int cas;
    int caspremikanja;

public:
    Sprite* zoga;
    int aktivna;

    void premikanje();
    void smer(int);

    Zoga(SDLsetup*);
    ~Zoga();
    void funkcije();

};
#endif // ZOGA_H
