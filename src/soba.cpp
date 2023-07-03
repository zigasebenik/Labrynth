#include "soba.h"

soba::soba(SDLsetup* setuppass, int screenw, int screenh, int stenemypass)
{
    setup = setuppass;
    stenemy = stenemypass;
    initcoordinates = false;

    dungeon.w = rand()%10+5;
    dungeon.h = rand()%10+4;
    dungeon.x = rand()%(150-dungeon.w*2-1)+16;
    dungeon.y = rand()%(94-dungeon.h*2-1)+15;

    for(int i=0; i<stenemy; i++)
        grunt[i]= new Enemy(setup,screenw,screenh,"grunt.png",10,10,380,631,5,11);


    for(int i=0; i<10; i++)
        stvrat[i] = new Vrata;

    boss = 0;
}

soba::~soba()
{
    //dtor
}

int soba::getx()
{
    return dungeon.x;
}

int soba::gety()
{
    return dungeon.y;
}

int soba::getw()
{
    return dungeon.w;
}

int soba::geth()
{
    return dungeon.h;
}

SDL_Rect soba::getrect()
{
    return dungeon;
}

void soba::setsize(int w, int h)
{
    dungeon.w=w;
    dungeon.h=h;
}

void soba::randomnov()
{
    dungeon.x = rand()%109;
    dungeon.y = rand()%59;
    dungeon.w = rand()%40+10;
    dungeon.h = rand()%20+10;
}

void soba::enemymovement(Hero* player)
{
    for(int i=0; i<stenemy; i++)
    {
        if(grunt[i]->enemy->rect.x+grunt[i]->enemy->rect.w>=(dungeon.x+dungeon.w)*10)
        {
            grunt[i]->enemy->rect.x=(dungeon.x+dungeon.w)*10 -grunt[i]->rect.w-1;
            grunt[i]->enemy->setx(grunt[i]->enemy->rect.x);
            grunt[i]->mright = false;
            grunt[i]->mleft = false;
            grunt[i]->mup = false;
            grunt[i]->mdown = false;

            //cout << "desno"<<endl;
        }

        if(grunt[i]->enemy->rect.x <= dungeon.x*10)
        {
            grunt[i]->enemy->rect.x=grunt[i]->enemy->rect.x+1;
            grunt[i]->enemy->setx(grunt[i]->enemy->rect.x);
            grunt[i]->mright = false;
            grunt[i]->mleft = false;
            grunt[i]->mup = false;
            grunt[i]->mdown = false;
        }

        if(grunt[i]->enemy->rect.y+grunt[i]->rect.h>=(dungeon.y+dungeon.h)*10)
        {
            grunt[i]->enemy->rect.y=(dungeon.y+dungeon.h)*10-grunt[i]->enemy->rect.h-1;
            grunt[i]->enemy->sety(grunt[i]->enemy->rect.y);
            grunt[i]->mright = false;
            grunt[i]->mleft = false;
            grunt[i]->mup = false;
            grunt[i]->mdown = false;
        }

        if(grunt[i]->enemy->rect.y<=dungeon.y*10)
        {
            grunt[i]->enemy->rect.y+=1;
            grunt[i]->enemy->sety(grunt[i]->enemy->rect.y);
            grunt[i]->mright = false;
            grunt[i]->mleft = false;
            grunt[i]->mup = false;
            grunt[i]->mdown = false;
        }
    }
}

void soba::enemyinit()
{
    for(int i=0; i<stenemy; i++)
    {
        grunt[i]->enemy->rect.x = dungeon.x *10 + (dungeon.w *10)/2+i*10;
        grunt[i]->enemy->rect.y = dungeon.y *10 + (dungeon.h *10)/2+i*10;
    }
    initcoordinates = true;
    cout <<"init"<<endl;
}

void soba::funkcije(Hero* player,Camera* kamera,Fireball* firebal[40])
{
    if(initcoordinates == false)
        enemyinit();

    enemymovement(player);

    for(int i=0; i<stenemy; i++)
    {
        if(player->x<(dungeon.x+dungeon.w)*10
                &&player->x>dungeon.x*10
                &&player->y< (dungeon.y+dungeon.h)*10
                &&player->y>dungeon.y*10)
            grunt[i]->slediplayerju = true;

        else
            grunt[i]->slediplayerju = false;

        grunt[i]->funkcije(player,kamera);
        for(int j=0; j<40; j++)
        {
            if(firebal[j]->firebal->rect.x + firebal[j]->firebal->rect.w > grunt[i]->enemy->rect.x&&
                    grunt[i]->enemy->rect.x + grunt[i]->enemy->rect.w - firebal[j]->firebal->rect.w> firebal[j]->firebal->rect.x&&
                    firebal[j]->firebal->rect.y + firebal[j]->firebal->rect.h > grunt[i]->enemy->rect.y&&
                    grunt[i]->enemy->rect.y + grunt[i]->enemy->rect.h - firebal[j]->firebal->rect.h> firebal[j]->firebal->rect.y &&
                    firebal[j]->aktivna == true)
            {
                grunt[i]->zivljenje -=15;
                firebal[j]->aktivna = false;
            }

            grunt[i]->life.w =grunt[i]->zivljenje/10;
        }

    }

    //enemycollision();

}

void soba::enemycollision()
{
    for(int i=0; i<stenemy; i++)
    {
        for(int j=0; j<stenemy; j++)
            if(i!=j)
            {
                if(grunt[j]->enemy->rect.x + grunt[j]->enemy->rect.w > grunt[i]->enemy->rect.x &&
                        grunt[i]->enemy->rect.x + grunt[i]->enemy->rect.w > grunt[j]->enemy->rect.x&&
                        grunt[j]->enemy->rect.y + grunt[j]->enemy->rect.h > grunt[i]->enemy->rect.y&&
                        grunt[i]->enemy->rect.y + grunt[i]->enemy->rect.h > grunt[j]->enemy->rect.y)
                {


                    if(grunt[j]->enemy->rect.x + grunt[j]->enemy->rect.w/1.5 > grunt[i]->enemy->rect.x)
                    {
                        grunt[j]->enemy->rect.x = grunt[j]->enemy->rect.x + 1;
                    }

                    if( grunt[i]->enemy->rect.x + grunt[i]->enemy->rect.w/1.5 > grunt[j]->enemy->rect.x)
                    {
                        grunt[j]->enemy->rect.x = grunt[j]->enemy->rect.x - 1;
                    }

                    if( grunt[j]->enemy->rect.y + grunt[j]->enemy->rect.h/1.5 > grunt[i]->enemy->rect.y)
                    {
                        grunt[j]->enemy->rect.y = grunt[j]->enemy->rect.y + 1;
                    }

                    if( grunt[i]->enemy->rect.y + grunt[i]->enemy->rect.h/1.5 > grunt[j]->enemy->rect.y)
                    {
                        grunt[j]->enemy->rect.y = grunt[j]->enemy->rect.y - 1;
                    }
                }

                /*if(grunt[j]->enemy->rect.x + grunt[j]->enemy->rect.w > grunt[i]->enemy->rect.x &&
                        grunt[i]->enemy->rect.x + grunt[i]->enemy->rect.w > grunt[j]->enemy->rect.x&&
                        grunt[j]->enemy->rect.y + grunt[j]->enemy->rect.h > grunt[i]->enemy->rect.y&&
                        grunt[i]->enemy->rect.y + grunt[i]->enemy->rect.h > grunt[j]->enemy->rect.y)
                {


                    if(grunt[j]->enemy->rect.x + grunt[j]->enemy->rect.w > grunt[i]->enemy->rect.x)
                    {
                        grunt[j]->mup = true;
                    }

                    else if( grunt[i]->enemy->rect.x + grunt[i]->enemy->rect.w > grunt[j]->enemy->rect.x)
                    {
                        grunt[j]->mdown = true;
                    }

                    else if( grunt[j]->enemy->rect.y + grunt[j]->enemy->rect.h > grunt[i]->enemy->rect.y)
                    {
                        grunt[j]->mright = true;
                    }

                    else if( grunt[i]->enemy->rect.y + grunt[i]->enemy->rect.h > grunt[j]->enemy->rect.y)
                    {
                        grunt[j]->mleft = true;
                    }
                }*/


            }
    }
}

bool soba::vsimrtvi()
{
    bool tmp = false;
    int stevec = -1;

    for(int i=0; i<stenemy; i++)
    {
        if(grunt[i]->ziv == true)
            break;
        else
            stevec = i;
    }

    if(stevec == stenemy-1)
    {
        return true;
    }
    else
        return false;


}
