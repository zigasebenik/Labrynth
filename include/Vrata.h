#ifndef VRATA_H
#define VRATA_H
#include <SDL.h>
#include <stdlib.h>

class Vrata
{
private:

public:
    Vrata();
    ~Vrata();
    void setvrata(SDL_Rect);
    int getposition();
    void randomnov(int,int,int,int,int);
    SDL_Rect vrata;
};

#endif // VRATA_H
