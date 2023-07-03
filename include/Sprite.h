#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

using namespace std;

class Sprite
{
    //SDL_Texture *image;

    SDL_Renderer *render;

public:
    Sprite(SDL_Renderer* renderpass, string filepath, int x, int y, int w, int h, int anix, int aniy, int aniw, int anih);
    ~Sprite();

    SDL_Rect rect;
    SDL_Rect anirect;

    SDL_Texture *image;
    float x,y;
    void staticdraw(SDL_Rect*);
    void drawanistatic(SDL_Rect, SDL_Rect);
    void drawani(SDL_Rect);
    void draw();

    void setx(int x);
    void sety(int y);
    void setposition(int x, int y);

    int getx();
    int gety();
};

#endif // SPRITE_H
