#ifndef FIREBALL_H
#define FIREBALL_H
#include "Sprite.h"
#include "Hero.h"
#include "SDLsetup.h"
#include <iostream>

class Fireball
{
private:
    SDLsetup* setup;

public:
    Sprite* firebal;
    bool aktivna;
    bool initbool;
    int mouseX;
    int mouseY;
    int sirina;
    int visina;
    int premikX;
    int premikY;
    Fireball(SDLsetup*);
    ~Fireball();
    Sprite* fireball();

    void init(Hero*,int,int);

    Sprite * funkcije(Hero*,int,int,int,int);
    void reset(int,int);
    void offscreen(Hero*,int,int,int,int);
};

#endif // FIREBALL_H
