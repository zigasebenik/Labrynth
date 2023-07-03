#include "Chest.h"

Chest::Chest(SDLsetup* passsetup, int x, int y)
{
    srand(time(NULL));
    setup=passsetup;
    zaklad = new Sprite(setup->vrnirender(),"chests.png",x, y, 5, 5, 0,0,384/12,256/8);
    //(rand()%6+1)*100+20, (rand()%4+1)*100+10, 60, 60, 0,0,384/12,256/8

    rect=zaklad->rect;
    cas=SDL_GetTicks();
    animacije =0;

    cout<<"rect x "<<rect.x<<endl;
    cout<<"rect y "<<rect.y<<endl;
    cout<<"rect w "<<rect.w<<endl;
    cout<<"rect h "<<rect.h<<endl;

    cout<<"anirect x "<<zaklad->anirect.x<<endl;
    cout<<"anirect y "<<zaklad->anirect.y<<endl;
    cout<<"anirect w "<<zaklad->anirect.w<<endl;
    cout<<"anirect h "<<zaklad->anirect.h<<endl;

    zapri = false;
    odpri = false;

    skrita = true;
    bonus = true;

}

Chest::~Chest()
{
    delete zaklad;
}

void Chest::drawAni()
{
    zaklad->drawani(zaklad->anirect);

    if(odpri == true)
    {
        if(animacije<4)
            if(SDL_GetTicks()-cas>200)
            {
                zaklad->anirect.y= zaklad->anirect.y+32;
                if( zaklad->anirect.y>=128)
                    zaklad->anirect.y=96;
                cas=SDL_GetTicks();
                animacije++;
            }
    }
    if (zapri == true)
    {
        if(animacije>0)
            if(SDL_GetTicks()-cas>200)
            {
                zaklad->anirect.y= zaklad->anirect.y-32;
                if( zaklad->anirect.y<=0)
                    zaklad->anirect.y=0;

                cas=SDL_GetTicks();
                animacije--;
            }
    }
}

void Chest::draw()
{
    zaklad->drawani(zaklad->anirect);
    //SDL_RenderDrawRect(setup->vrnirender(),&zaklad->anirect);
}

void Chest::resetZakladani()
{
    zaklad->anirect.x=0;
    zaklad->anirect.y=0;
    animacije = 0;
}

bool Chest::zakladCollision(Hero *player)
{
    if(player->rect.x+player->rect.w+5>rect.x && player->rect.x<rect.x+rect.w+5&&
            player->rect.y+player->rect.h+5>rect.y && player->rect.y<rect.y+rect.h+5)
    {
        return true;
    }
    else
        return false;


}
