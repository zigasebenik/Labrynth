#ifndef ENEMY_H
#define ENEMY_H
#include <SDL.h>
#include <SDLsetup.h>
#include <Sprite.h>
#include <ctime>
#include <stdlib.h>
#include "Hero.h"
#include <math.h>
#include "Camera.h"
class Fireball;
class Camera;

class Enemy
{
private:



    float x,y,w,h;

    int premikx;
    int premiky;
    int cas;
    int caspremikanja;
    int zgorajalispodaj;
    int casnapada;
    int hitrostnapada;

    SDLsetup *setup;
    SDL_Rect dir;
public:
    SDL_Rect anirect;
    bool mright;
    bool mleft;
    bool mup;
    bool mdown;

    Sprite *enemy;
    int levelheight;
    SDL_Rect life;

    int screenw;
    int screenh;
    int staticx;
    int staticy;
    int casregen;
    int casrandom;

    float zivljenje;


    bool levo;
    bool dol;
    bool gor;
    bool desno;
    bool napadanimacija;
    bool triger;
    bool ziv;
    bool animacija2;
    bool firebaldotik;
    bool slediplayerju;

    SDL_Rect staticxy;
    SDL_Rect rect;
    Enemy(SDLsetup*, int passscreenw, int passscreenh, string filepath,int width,int height,int aniw,int anih,int stw,int sth);
    ~Enemy();

    void tipkovnica(Hero*,Camera*);
    void drawanimacija(Hero*);
    void drawanimacijastatic();
    void draw();

    SDL_Rect updaterect();

    void setrectx(int);
    void setrecty(int);
    void zivljenjekazi();
    void setlife(int);
    void funkcije(Hero*,Camera*);
    int getx();
    int gety();
    void nastavix(int);
    void nastaviy(int);
    void lifebar();
    void umri();
};

#endif // ENEMY_H
