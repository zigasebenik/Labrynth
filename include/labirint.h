#ifndef LABIRINT_H
#define LABIRINT_H
#include <MainClass.h>
#include "Tile.h"
#include "soba.h"
#include "Vrata.h"
#include "Hero.h"
#include <math.h>
#include <iomanip>
#include "Enemy.h"
#include "Camera.h"
#include "Chest.h"
#include "SDLsetup.h"
#include "Fireball.h"
#include <SDL_ttf.h>
#include <Boss.h>
#include <fstream>
#include <Zoga.h>

class Camera;
class soba;
class Tile;
class Enemy;
class SDLsetup;
class Chest;
class Boss;
class Zoga;

class labirint

{

private:
    Camera *kamera;
    TTF_Font *font;
    SDL_Color color;
    SDL_Surface *textSurface;
    SDL_Texture *text;
    SDL_Rect textRect;

    int caszadetekzoge;

    int aktivnezoge;
    Zoga *zoga[10];
    Fireball* firebal[200];
    Chest *chesti[20];
    soba *tabelasob[50];
    soba *bosstabela[10];
    Tile *tabela[100][160];
    int nacrt[100][160];
    int nacrtArena[100][160];
    Tile *tArena[100][160];
    bool arenazbosom;
    string str;
    stringstream ss;
    Boss *bos;
    bool zemljevid;
    int caszemljevid;
    bool pavza;

    SDL_Renderer *render;
    int screenw;
    int screenh;
    int stsob;
    int stskrinj;
    int stbosov;
    bool primerjajvrata(int,int,char);
    int xkonec;
    int konec;


    Hero *player;
    SDLsetup *setup;

    int casodpiranja;
    bool initherocoordinates;
    bool startscreen;
    bool izberitezavnost;
    int tezavnost;


    int casigranja;
    int caszacetek;
    int maxcas;
    bool vnoshighscore;
    int trenutnicasigranja;
    int zemljevidcooldown;


    bool survival;

public:

    int izhod;
    int zmaga;
    labirint(SDL_Renderer* renderpass, int screenwpass, int screenhpass, SDLsetup*);
    ~labirint();
    void randomnacrt();
    void randomlabirint();
    void drawlabirint();
    bool collision(SDL_Rect,SDL_Rect);
    void zacetek(int,int,int,int, int);
    void test();
    SDL_Rect nastavivrata(int,int,int,int, int);
    void settiles();

    void povezivrata(Tile* tabela[100][160],int);

    void pisi(string,int,int,int);

    void setarena();

    void gameover();


};

#endif // LABIRINT_H
