#ifndef HERO_H
#define HERO_H
#include <SDL.h>
#include <SDLsetup.h>
#include <Sprite.h>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <SDL_ttf.h>

class Hero
{
private:

    TTF_Font *font;
    SDL_Color color;
    SDL_Surface *textSurface;
    SDL_Texture *text;
    SDL_Rect textRect;

    int cas;

    int casodpiranja;
    int casstreljaj;
    int casnapad;
    int casnapadpritisk;
    int casregen;
    bool zemljevid;


    Sprite *lifesl;

    SDLsetup *setup;
public:
    int premikx;
    int premiky;
    float x,y,w,h;
    float cameraX,cameraY;


    SDL_Rect herorect;

    int bonusdamage;
    int bonushpregen;
    int bonusmanaregen;


    bool mright;
    bool mleft;
    bool mup;
    bool mdown;
    bool odpri;
    int streljaj;
    bool gledalevo,gledadesno,gledadol,gledagor;

    int orozja[10];
    int menjavaorozja;
    int casmenjava;
    bool napadanimacija;

    bool aleft, aup, aright,adown;

    Sprite *hero;
    int levelheight;
    SDL_Rect life;
    SDL_Rect mana;

    int screenw;
    int screenh;
    int staticx;
    int staticy;


    int resetzemljevid;
    bool viewmap();


    bool levo;
    bool dol;
    bool gor;
    bool desno;

    SDL_Rect staticxy;
    SDL_Rect rect;
    Hero(SDLsetup*, int passscreenw, int passscreenh);
    ~Hero();

    void tipkovnica();
    void drawanimacija();
    void drawanimacijastatic();
    void draw();


    void bosssobacollision();

    void bonuschesti(int,int,int);


    SDL_Rect updaterect();

    SDL_Rect setrectx(int);
    SDL_Rect setrecty(int);
    bool funkcije();
    void straniokna();
    int getx();
    int gety();
    void nastavix(int);
    void nastaviy(int);
    void napadzmecem(bool);
    void lifebar();
    void pisi(string,int,int,int);
    void sporocilo(int,int,int);
    int cassporocilo;
    bool initsporocilo;
    int bonusst;
    int xsporocilo;
    int ysporocilo;
    int predprejsni;

};

#endif // HERO_H
