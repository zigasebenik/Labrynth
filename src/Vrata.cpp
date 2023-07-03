#include "Vrata.h"

Vrata::Vrata()
{
    vrata.x = 0;
    vrata.y = 0;
    vrata.w = 1;
    vrata.h = 1;
}

Vrata::~Vrata()
{
    //dtor
}

void Vrata::setvrata(SDL_Rect door)
{
    vrata.x = door.x;
    vrata.y = door.y;
}

int Vrata::getposition()
{
    return vrata.x+vrata.y;
}

void Vrata::randomnov(int x,int y,int w,int h, int vrednost)
{
    int izacetek = rand()%h;
    int jzacetek = rand()%w;
    int moznost= rand()%2;
    if(moznost == 1)
    {
        if(izacetek == 0||izacetek == h-1)
            jzacetek = rand()%w;
        else
        {
            int tmp = rand()%2;
            if(tmp == 1)
                jzacetek = w-1;
            else
                jzacetek = 0;
        }
    }
    else
    {
        if(jzacetek == 0||jzacetek == w-1)
            izacetek = rand()%h;
        else
        {
            int tmp = rand()%2;
            if(tmp == 1)
                izacetek = h-1;
            else
                izacetek = 0;
        }
    }
    int kordinatex = jzacetek+x;
    int kordinatey = izacetek+y;
    vrata.x=kordinatex;
    vrata.y=kordinatey;
}
