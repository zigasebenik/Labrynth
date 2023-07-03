#ifndef TILE_H
#define TILE_H
#include <MainClass.h>
#include "Hero.h"

class Tile
{
private:



public:
    SDL_Rect anirect;
    int premikX, premikY;

    SDL_Renderer *render;
    SDL_Rect rect;
    string imeSlike;
    Tile(SDL_Renderer* renderpass);
    ~Tile();
    void draw();
    void scale(int,int);
    void setposition(int x, int y);
    void init(int);
    int getx();
    int gety();
    int getw();
    int geth();
    SDL_Rect getrect();
    void setx(int x);
    void sety(int y);
    void zid();
    void pot();
    void vrata();
    void boss();
    void soba();
    void sobawinter();
    void sobawasteland();
    void zidokolisobe();
    void collisionzid(Hero*,bool,bool,bool,bool);
    void desno(Hero*);
    void levo(Hero*);
    void gor(Hero*);
    void dol(Hero*);

    void settileview(int,int);
};

#endif // TILE_H
