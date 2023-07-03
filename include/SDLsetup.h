#ifndef SDLSETUP_H
#define SDLSETUP_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


using namespace std;

class SDLsetup
{
private:
    SDL_Event *mainevent;
    SDL_Renderer *render;

public:
    SDLsetup(bool *quit, int screenw, int screenh);
    ~SDLsetup();
    SDL_Renderer* vrnirender();
    SDL_Event* vrnievent();
    void start();
    void konec();
    SDL_Window *window;
};

#endif // SDLSETUP_H
