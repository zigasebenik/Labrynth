#include "Camera.h"

Camera::Camera(SDL_Renderer* renderpass,float passw,float passh)
{
    renderer = renderpass;

    x = 0;
    y = 0;
    w = 1600;
    h = 1000;
    w = 800;
    h = 500;
    w = 1600;
    h = 1000;

    scaleX = passw / w;
    scaleY = passh / h;

    screenw = passw;
    screenh= passh;

}

Camera::~Camera()
{
    //dtor
}

void Camera::renderrect(SDL_Rect* dstrect)
{
    SDL_Rect r1;

    r1.x = (dstrect->x - x) * scaleX;
    r1.y = (dstrect->y - y) * scaleY;
    r1.w = dstrect->w * scaleX;
    r1.h = dstrect->h * scaleY;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &r1);
    SDL_RenderDrawRect(renderer,&r1);
}

void Camera::render(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect, bool mirror)
{


    r.x = (dstrect->x - x) * scaleX;
    r.y = (dstrect->y - y) * scaleY;
    r.w = dstrect->w * scaleX;
    r.h = dstrect->h * scaleY;

    //SDL_RenderDrawRect(renderer,&r);

    if(mirror == false)
        SDL_RenderCopy(renderer, texture, srcrect, &r);

    else
        SDL_RenderCopyEx(renderer, texture, srcrect, &r,0,NULL,SDL_FLIP_HORIZONTAL);
}

void Camera::camerawh(int wpass,int hpass)
{
    w = wpass;
    h = hpass;
    x=0;
    y=0;
    scaleX = screenw / w;
    scaleY = screenh / h;

}

void Camera::cameraCoordinates(int xpass,int ypass)
{
    x=xpass-w/2;
    y=ypass-h/2;
}


