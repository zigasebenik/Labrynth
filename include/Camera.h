#ifndef CAMERA_H
#define CAMERA_H
#include "Tile.h"
#include <SDL.h>
#include "Enemy.h"

class Enemy;
class Tile;

class Camera
{
private:


    float x,y,w,h;

    SDL_Rect kamera;
    SDL_Renderer *renderer;
    int screenw,screenh;


public:
    float scaleX, scaleY;
    SDL_Rect r;
    Camera(SDL_Renderer* renderpass, float, float);
    ~Camera();

    void render(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect,bool);
    void cameraCoordinates(int,int);
    void camerawh(int,int);
    void renderrect(SDL_Rect*);

};

#endif // CAMERA_H
