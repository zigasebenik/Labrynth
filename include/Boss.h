#ifndef BOSS_H
#define BOSS_H
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

class Boss
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
    int bonusdamage;
    int bonushp;

    SDL_Rect anirect;
    bool mright;
    bool mleft;
    bool mup;
    bool mdown;
    int tezavnost;

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
    Boss(SDLsetup*, int passscreenw, int passscreenh, string filepath,int width,int height,int aniw,int anih,int stw,int sth, int passtezavnost,int passdamage);
    ~Boss();

    void tipkovnica(Hero*,Camera*,int);
    void drawanimacija(Hero*);
    void drawanimacijastatic();
    void draw();

    SDL_Rect updaterect();

    void setrectx(int);
    void setrecty(int);
    void zivljenjekazi();
    void setlife(int);
    void funkcije(Hero*,Camera*,Fireball* firebal[40]);
    int getx();
    int gety();
    void nastavix(int);
    void nastaviy(int);
    void lifebar(int,int);
    void umri();
};
#endif // BOSS_H
