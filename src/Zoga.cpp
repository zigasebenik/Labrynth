#include "Zoga.h"

Zoga::Zoga(SDLsetup* passsetup)
{
    setup = passsetup;

    zoga = new Sprite(setup->vrnirender(),"zoga.png",0,0,5,5,0,0,0,0);
    aktivna = false;
    init = false;
    premikX = 1;
    premikY = -1;
    cas = SDL_GetTicks();

    caspremikanja = SDL_GetTicks();
}

Zoga::~Zoga()
{
    delete zoga;
}

void Zoga::premikanje()
{
    cout << "premikanje"<<endl;
    if(zoga->rect.x<0)
    {
        cout << "1" <<endl;
        //smer(rand()%4);
        premikX = 1;
    }
    else if(zoga->rect.x+zoga->rect.w >180)
    {
        cout << "2" <<endl;
        //smer(rand()%4);
        premikX = -1;
    }
    else if(zoga->rect.y<0)
    {
        cout << "3" <<endl;
        //smer(rand()%4);
        premikY = 1;
    }
    else if(zoga->rect.y +zoga->rect.h>120)
    {
        cout << "4" <<endl;
        //smer(rand()%4);
        premikY = -1;
    }
    else if(init == false)
    {
        cout << "init == false" <<endl;
        smer(rand()%4);
        init = true;
        zoga->rect.x = rand()%165;
        zoga->rect.y = rand()%105;
    }else if(SDL_GetTicks()- cas > 4000)
    {
        smer(rand()%4);
        cas = SDL_GetTicks();
    }

    cout << "premikX " << premikX <<endl;
    cout << "premikY " << premikY <<endl;
    zoga->rect.x += premikX;
    zoga->rect.y += premikY;
}

void Zoga::funkcije()
{
    if(aktivna == true && SDL_GetTicks()- caspremikanja>20)
        {premikanje(); caspremikanja = SDL_GetTicks();}
}

void Zoga::smer(int n)
{
    if(n == 0)
    {
        ///gor
        premikY = -1;
    }
    if(n == 1)
    {
        ///dol
        premikY = 1;
    }
    if(n == 2)
    {
        ///levo
        premikX = -1;
    }
    if(n == 3)
    {
        ///desno
        premikX = 1;
    }
}
