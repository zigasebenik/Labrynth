#include "Fireball.h"

Fireball::Fireball(SDLsetup* passsetup)
{
    setup = passsetup;
    ///old fireball
    //firebal = new Sprite(setup->vrnirender(),"fireorb.png",0,0,50,50,0,0,1024/8,1024/8);

    ///new fireball
    firebal = new Sprite(setup->vrnirender(),"fireorb.png",0,0,5,5,0,0,0,0);
    mouseX = 0;
    mouseY = 0;
    sirina = 0;
    visina = 0;
    premikX = 0;
    premikY = 0;

    aktivna = 0;
    initbool = 0;
}

Fireball::~Fireball()
{
    delete firebal;
}

Sprite * Fireball::fireball()
{
    if(aktivna == true && initbool == true)
    {

        firebal->setposition(firebal->x+premikX,firebal->y+premikY);
        return firebal;
    }
}

void Fireball::init(Hero* player,int herox,int heroy)
{
    /*if(aktivna == true && initbool == false)
    {
        SDL_GetMouseState(&mouseX,&mouseY);

        cout <<"mouseX "<<mouseX<<endl;
        cout <<"mouseY "<<mouseY<<endl;


        sirina = mouseX - player->cameraX;
        visina = mouseY - player->cameraY;

        float angle = atan2(visina,sirina);

        premikX = cos(angle)*2;
        premikY = sin(angle)*2;

        firebal->setposition(player->x-firebal->rect.w/2+5,player->y-firebal->rect.h/2+5);
        initbool = true;

        player->mana.w -= 200;
    }*/

    if(aktivna == true && initbool == false)
    {
        if(player->gledadesno == true)
        {
            premikX = 2;
        }
        else if(player->gledalevo == true)
        {
            premikX = -2;
        }
        else if(player->gledagor == true)
        {
            premikY= -2;
        }
        else if(player->gledadol == true)
        {
            premikY = 2;
        }

        firebal->setposition(player->x-firebal->rect.w/2+5,player->y-firebal->rect.h/2+5);
        initbool = true;

        player->mana.w -= 220;
    }

}

Sprite * Fireball::funkcije(Hero* player, int passw, int passh, int herox, int heroy)
{
    init(player,herox,heroy);
    offscreen(player,passw,passh,herox,heroy);
    return fireball();
}

void Fireball::reset(int x,int y)
{
    aktivna = false;
    initbool = false;
    firebal->setposition(x,y);
}

void Fireball::offscreen(Hero* player,int passw, int passh, int herox,int heroy)
{

    if(firebal->rect.x>passw)
    {
        reset(herox,heroy);
    }

    if(firebal->rect.x < 0)
    {
        reset(herox,heroy);
    }

    if(firebal->rect.y>passh)
    {
        reset(herox,heroy);
    }

    if(firebal->rect.y<0)
    {
        reset(herox,heroy);
    }
}
