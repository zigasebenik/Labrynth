#ifndef CHEST_H
#define CHEST_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"
#include "SDLsetup.h"
#include <ctime>
#include <stdlib.h>
#include "hero.h"

using namespace std;

class Hero;
class Chest
{
private:


    int cas;


    SDLsetup *setup;

public:

    int animacije;
    bool odpri;
    bool zapri;
    bool skrita;
    bool bonus;
    int xkamera;
    int ykamera;

    Sprite *zaklad;
    SDL_Rect rect;

    Chest(SDLsetup*,int,int);
    ~Chest();

    void drawAni();
    void draw();
    void resetZakladani();
    bool zakladCollision(Hero*);
};

#endif // CHEST_H
