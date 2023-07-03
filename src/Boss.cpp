#include "Boss.h"

Boss::Boss(SDLsetup* passsetup, int passscreenw, int passscreenh, string filepath,int width,int height,int aniw,int anih,int stw,int sth, int passtezavnost,int passdamage)
{
    tezavnost = passtezavnost;
    mright = false;
    mleft = false;
    mup = false;
    mdown = false;
    zgorajalispodaj = rand()%2;
    triger = false;
    animacija2 = false;
    firebaldotik = false;
    slediplayerju = true;

    casnapada = SDL_GetTicks();
    casrandom = SDL_GetTicks();
    hitrostnapada  = 500;

    casregen = SDL_GetTicks();

    zivljenje = 100;


    levo=false;
    desno=false;
    gor=false;
    dol=false;
    napadanimacija = false;
    ziv = true;

    life.x = 90;
    life.y = 12;

    if(tezavnost == 3)
        life.w = 1500;
    else if(tezavnost == 2)
        life.w = 1000;
    else
        life.w = 500;

    life.h = 20;

    anirect.x = 0;
    anirect.y = 0;
    anirect.w = aniw/stw ;
    anirect.h = anih/sth;

    premikx = anirect.w -1;
    premiky = anirect.h -1;

    cas = SDL_GetTicks();

    setup = passsetup;

    //to je kockica
    //hero = new Sprite(setup->vrnirender(),"vrata.png",rand()%8*100+20,rand()%6*100+10,10,10,0,0,0,0);

    //to je stricek
    enemy = new Sprite(setup->vrnirender(),filepath,800,500,width,height,0,0,0,0);

    rect = enemy->rect;

    levelheight=0;

    screenw = passscreenw;
    screenh = passscreenh;


    staticxy.x=(screenw/2) + 20;
    staticxy.y=(screenh/2) + 20;
    staticxy.w=70;
    staticxy.h=85;

    caspremikanja = SDL_GetTicks();


    bonusdamage = 0;
    bonushp = 0;
}

Boss::~Boss()
{
    delete enemy;
}

void Boss::lifebar(int liferegen,int maxlife)
{
    if(SDL_GetTicks()-casregen>2000)
    {
        casregen = SDL_GetTicks();

        if(life.w<maxlife)
            life.w += liferegen;
    }
}

void Boss::funkcije(Hero *player, Camera* kamera,Fireball* firebal[40])
{

    //drawanimacija(player);
    //draw();
    if(life.w <= 0)
        ziv = false;

    if(tezavnost == 3)
    {
        if(ziv == true)
        {
            tipkovnica(player,kamera,80);
            lifebar(3,1500);
            if(life.w > 150)
                SDL_SetRenderDrawColor(setup->vrnirender(), 0, 255, 0, 255);
            else
                SDL_SetRenderDrawColor(setup->vrnirender(), 255, 0, 0, 255);

            SDL_RenderFillRect(setup->vrnirender(), &life);
            SDL_RenderDrawRect(setup->vrnirender(),&life);
        }
        else
            umri();
    }
    else if(tezavnost == 2)
    {
        if(ziv == true)
        {
            tipkovnica(player,kamera,40);
            lifebar(2,1000);
            if(life.w > 150)
                SDL_SetRenderDrawColor(setup->vrnirender(), 0, 255, 0, 255);
            else
                SDL_SetRenderDrawColor(setup->vrnirender(), 255, 0, 0, 255);

            SDL_RenderFillRect(setup->vrnirender(), &life);
            SDL_RenderDrawRect(setup->vrnirender(),&life);
        }
        else
            umri();
    }
    else if(tezavnost == 1)
    {
        if(ziv == true)
        {
            tipkovnica(player,kamera,20);
            lifebar(1,500);
            if(life.w > 150)
                SDL_SetRenderDrawColor(setup->vrnirender(), 0, 255, 0, 255);
            else
                SDL_SetRenderDrawColor(setup->vrnirender(), 255, 0, 0, 255);

            SDL_RenderFillRect(setup->vrnirender(), &life);
            SDL_RenderDrawRect(setup->vrnirender(),&life);
        }
        else
            umri();
    }

    // zivljenjekazi();

    for(int j =0 ; j<40; j++)
        if(firebal[j]->firebal->rect.x + firebal[j]->firebal->rect.w > enemy->rect.x&&
                enemy->rect.x + enemy->rect.w - firebal[j]->firebal->rect.w> firebal[j]->firebal->rect.x&&
                firebal[j]->firebal->rect.y + firebal[j]->firebal->rect.h > enemy->rect.y&&
                enemy->rect.y + enemy->rect.h - firebal[j]->firebal->rect.h> firebal[j]->firebal->rect.y &&
                firebal[j]->aktivna == true)
        {
            life.w -=30;
            firebal[j]->aktivna = false;
        }
}

void Boss::drawanimacijastatic()
{

    enemy->drawanistatic(anirect,staticxy);
    SDL_RenderDrawRect(setup->vrnirender(),&rect);
}

void Boss::drawanimacija(Hero * player)
{
    enemy->drawani(anirect);
}

void Boss::draw()
{
    enemy->draw();
}


void Boss::tipkovnica(Hero* player, Camera* kamera, int damage)
{
//cout <<"zgoraj spodaj"<<zgorajalispodaj;
    ///da se ustavi na levi ali desni
    //cout << "dir x "<<dir.x<<endl;

    if(slediplayerju == true)
    {
        if(zgorajalispodaj == 0)
        {
            if(player->rect.x + player->rect.w/2 == enemy->rect.x )
            {
                mleft = false;
                mright = false;
                levo = true;
                desno = false;
                napadanimacija = true;
            }
            if(enemy->rect.x + enemy->rect.w/2 == player->rect.x)
            {
                mleft = false;
                mright = false;
                desno = true;
                levo = false;
                napadanimacija = true;
            }
            else if(enemy->rect.x+enemy->rect.w <= player->x)
            {
                mright=true;
                //cout<<"desno"<<endl;
                mleft = false;
                napadanimacija = false;
            }
            else if(enemy->rect.x > player->x+player->rect.w)
            {
                mleft=true;
                //cout<<"levo"<<endl;
                mright = false;
                napadanimacija = false;
            }

            if(enemy->rect.y == player->y )
            {
                if(player->rect.x >= enemy->rect.x )
                {
                    levo = false;
                    desno = true;
                    gor = false;
                    dol = false;
                }
                else if(enemy->rect.x >= player->rect.x)
                {
                    desno = false;
                    levo = true;
                    gor = false;
                    dol = false;
                    //cout<<"levo"<<endl;
                }
                mdown = false;
                mup = false;
            }
            else if(enemy->rect.y+enemy->rect.h/2 - enemy->rect.h/4 < player->y)
            {
                mdown=true;
                //cout<<"gor"<<endl;
                mup = false;
                napadanimacija = false;
            }
            else  if(enemy->rect.y > player->y + player->rect.h/2 - enemy->rect.h/4 )
            {
                mup=true;
                //cout<<"dol"<<endl;
                mdown = false;
                napadanimacija = false;
            }

        }
        ///da se ustavi zgoraj ali spodaj

        else if(zgorajalispodaj == 1)
        {
            if(player->rect.y + player->rect.h/2 == enemy->rect.y )
            {
                mup = false;
                mdown = false;
                gor = true;
                dol = false;
                napadanimacija = true;
            }
            if(enemy->rect.y + enemy->rect.h/2 == player->rect.y)
            {
                mup = false;
                mdown = false;
                dol = true;
                gor = false;
                napadanimacija = true;
            }
            else if(enemy->rect.y+enemy->rect.h <= player->y)
            {
                mdown=true;
                //cout<<"desno"<<endl;
                mup = false;
                napadanimacija = false;
            }
            else if(enemy->rect.y > player->y+player->rect.h)
            {
                mup=true;
                //cout<<"levo"<<endl;
                mdown = false;
                napadanimacija = false;
            }

            if(enemy->rect.x == player->x )
            {
                if(player->rect.y >= enemy->rect.y )
                {
                    gor = false;
                    dol = true;
                    levo = false;
                    desno = false;
                }
                else if(enemy->rect.y >= player->rect.y)
                {
                    dol = false;
                    gor = true;
                    levo = false;
                    desno = false;
                    //cout<<"levo"<<endl;
                }
                mright = false;
                mleft = false;
            }
            else if(enemy->rect.x+enemy->rect.w/2 - enemy->rect.w/4 < player->x)
            {
                mright=true;
                //cout<<"gor"<<endl;
                mleft = false;
                desno = true;
                levo = false;
                napadanimacija = false;
            }
            else  if(enemy->rect.x > player->x + player->rect.w/2 - enemy->rect.w/4 )
            {
                mleft=true;
                //cout<<"dol"<<endl;
                mright = false;
                levo = true;
                desno = false;
                napadanimacija = false;
            }
        }




        if(SDL_GetTicks()-cas>90)
        {

            cas = SDL_GetTicks();

            if(mright && napadanimacija == false)
            {
                anirect.y = anirect.y + premiky;

                anirect.x = premikx+premikx;
                if(anirect.y >= (premiky-0)*4)
                {
                    anirect.y = 0;
                }
                /* enemy->setx( enemy->getx() +1);
                 rect=enemy->rect;*/
            }
            else if(mleft && napadanimacija == false)
            {
                anirect.y = anirect.y + premiky;

                anirect.x = premikx+premikx;
                if(anirect.y >= (premiky-0)*4)
                {
                    anirect.y = 0;
                }
                /*enemy->setx( enemy->getx() -1);
                rect=enemy->rect;*/
            }
            else if(mup && napadanimacija == false)
            {
                if(anirect.y >= premiky *5)
                    anirect.y = 0;
                anirect.x = 0;

                anirect.y += premiky+0;

                if(anirect.y >= (premiky+0)*4)
                {
                    anirect.y = 0;
                }
                /* enemy->sety( enemy->gety() -1);
                 rect=enemy->rect;*/
            }
            else if(mdown && napadanimacija == false)
            {
                if(anirect.y >= premiky *5)
                    anirect.y = 0;
                anirect.x = premikx * 4;

                if(anirect.y >= premiky*2)
                    anirect.y = anirect.y + premiky+1;
                else
                    anirect.y = anirect.y + premiky+0;

                if(anirect.y >= premiky*4)
                {
                    anirect.y = 0;
                }
                /*enemy->sety( enemy->gety() +1);
                rect=enemy->rect;*/
            }
            ///napad/////////////////////////////////////////////////////////////////
            if(anirect.y < premiky *5 && napadanimacija == true &&(desno == true || levo == true))
                anirect.y = 370;

            if(anirect.y < premiky *5 && napadanimacija == true &&(gor == true ))
                anirect.y = 370;

            if(anirect.y < premiky *5 && napadanimacija == true &&(dol == true ))
                anirect.y = 370;

            if(napadanimacija == true && SDL_GetTicks()-casnapada>hitrostnapada)
            {
                triger = true;
                casnapada = SDL_GetTicks();
            }

            if(desno && triger == true && napadanimacija == true)
            {
                anirect.y = anirect.y + premiky;
                anirect.x = premikx+premikx;
                if(anirect.y >= (premiky-0)*8)
                {
                    anirect.y = 370;
                    triger = false;
                    player->life.w -=damage + bonusdamage;
                }
            }
            else if(levo && triger == true && napadanimacija == true)
            {
                anirect.y = anirect.y + premiky;
                anirect.x = premikx+premikx;
                if(anirect.y >= (premiky-0)*8)
                {
                    anirect.y = 370;
                    triger = false;
                    player->life.w -=damage + bonusdamage;
                }
            }
            else if(gor && triger == true && napadanimacija == true)
            {
                anirect.x = 0;
                anirect.y += premiky-1;
                if(anirect.y >= premiky*8)
                {
                    anirect.y = 370;
                    triger = false;
                    player->life.w -=damage + bonusdamage;
                }
            }
            else if(dol && triger == true && napadanimacija == true)
            {
                anirect.x = premikx * 4;
                anirect.y = anirect.y + premiky;
                if(anirect.y >= premiky*8)
                {
                    anirect.y = 370;
                    triger = false;
                    player->life.w -=damage + bonusdamage;
                }
            }
        }

        ///premikanje herota

        if(SDL_GetTicks()-caspremikanja>40)
        {
            caspremikanja = SDL_GetTicks();
            if(mright && napadanimacija == false)
            {
                enemy->setx(enemy->getx() +1);
                rect=enemy->rect;
            }
            if(mleft && napadanimacija == false)
            {
                enemy->setx(enemy->getx() -1);
                rect=enemy->rect;
            }
            if(mup && napadanimacija == false)
            {
                enemy->sety(enemy->gety() -1);
                rect=enemy->rect;
            }
            if(mdown && napadanimacija == false)
            {
                enemy->sety(enemy->gety() +1);
                rect=enemy->rect;
            }
        }

        if(player->x + player->hero->rect.w > enemy->rect.x&&
                enemy->rect.x + enemy->rect.w > player->x&&
                player->y + player->hero->rect.h > enemy->rect.y&&
                enemy->rect.y + enemy->rect.h > player->y &&
                player->napadanimacija == true && player->herorect.y >= player->premiky*8)
        {
            life.w -=1 + player->bonusdamage;
        }

        if(player->rect.x + player->rect.w > enemy->rect.x &&
                enemy->rect.x +enemy->rect.w > player->rect.x&&
                player->rect.y + player->rect.h > enemy->rect.y&&
                enemy->rect.y + enemy->rect.h > player->rect.y)
        {

            napadanimacija = true;
            if( enemy->rect.x + enemy->rect.w <player->rect.x)
            {
                desno = true;
            }

            else if(player->rect.x + player->rect.w > enemy->rect.x)
            {
                levo = true;
            }

            else if(player->rect.y + player->rect.h >enemy->rect.y)
            {
                gor = true;
            }

            else if( enemy->rect.y + enemy->rect.h > player->rect.y)
            {
                dol = true;
            }
        }
        else
        {
            levo = false;
            desno = false;
            gor = false;
            dol = false;
        }

        //cout<<"levo "<<levo<<endl;
        //cout << "desno"<<desno<<endl;
        //cout << "gor"<<gor<<endl;
        //cout << "dol"<<dol<<endl;

        /*if(mright)
        {
            desno=true;
            levo=false;
            gor=false;
            dol=false;
        }
        if(mleft)
        {
            desno=false;
            levo=true;
            gor=false;
            dol=false;
        }
        if(mup)
        {
            desno=false;
            levo=false;
            gor=true;
            dol=false;
        }
        if(mdown)
        {
            desno=false;
            levo=false;
            gor=false;
            dol=true;
        }*/
    }

    else
    {
        if(SDL_GetTicks()-casrandom>4000)
        {
            casrandom = SDL_GetTicks();
            switch(rand()%4)
            {
            case 0:
                mright = true;
                mleft = false;
                mup = false;
                mdown = false;
                cout<<"case 1";
                desno = true;
                levo = false;
                gor = false;
                dol = false;
                break;
            case 1:
                mright = false;
                mleft = true;
                mup = false;
                cout<<"case 2";
                mdown = false;
                desno = false;
                levo = true;
                gor = false;
                dol = false;
                break;
            case 2:
                mright = false;
                mleft = false;
                cout<<"case 3";
                mup = true;
                mdown = false;
                desno = false;
                levo = false;
                gor = true;
                dol = false;
                break;
            case 3:
                mright = false;
                mleft = false;
                mup = false;
                cout<<"case 4";
                mdown = true;
                desno = false;
                levo = false;
                gor = false;
                dol = true;
                break;
            }

            if(mright)
            {
                desno=true;
                levo=false;
                gor=false;
                dol=false;
            }
            if(mleft)
            {
                desno=false;
                levo=true;
                gor=false;
                dol=false;
            }
            if(mup)
            {
                desno=false;
                levo=false;
                gor=true;
                dol=false;
            }
            if(mdown)
            {
                desno=false;
                levo=false;
                gor=false;
                dol=true;
            }
        }


    }

    if(SDL_GetTicks()-caspremikanja>40)
    {
        caspremikanja = SDL_GetTicks();
        if(mright && napadanimacija == false)
        {
            enemy->setx(enemy->getx() +1);
            rect=enemy->rect;
        }
        if(mleft && napadanimacija == false)
        {
            enemy->setx(enemy->getx() -1);
            rect=enemy->rect;
        }
        if(mup && napadanimacija == false)
        {
            enemy->sety(enemy->gety() -1);
            rect=enemy->rect;
        }
        if(mdown && napadanimacija == false)
        {
            enemy->sety(enemy->gety() +1);
            rect=enemy->rect;
        }
    }
    if(SDL_GetTicks()-cas>90)
    {

        cas = SDL_GetTicks();

        if(mright && napadanimacija == false)
        {
            if(anirect.y >= premiky *5)
                anirect.y = 0;
            if(anirect.y >= premiky*3)
                anirect.y = anirect.y + premiky-10;
            else
                anirect.y = anirect.y + premiky;

            anirect.x = premikx+premikx;
            if(anirect.y >= (premiky-0)*4)
            {
                anirect.y = 0;
            }
            /* enemy->setx( enemy->getx() +1);
             rect=enemy->rect;*/
        }
        else if(mleft && napadanimacija == false)
        {
            if(anirect.y >= premiky *5)
                anirect.y = 0;
            if(anirect.y >= premiky*3)
                anirect.y = anirect.y + premiky-10;
            else
                anirect.y = anirect.y + premiky;

            anirect.x = premikx+premikx;
            if(anirect.y >= (premiky-0)*4)
            {
                anirect.y = 0;
            }
            /*enemy->setx( enemy->getx() -1);
            rect=enemy->rect;*/
        }
        else if(mup && napadanimacija == false)
        {
            if(anirect.y >= premiky *5)
                anirect.y = 0;
            anirect.x = 0;

            anirect.y += premiky+0;

            if(anirect.y >= (premiky+0)*4)
            {
                anirect.y = 0;
            }
            /* enemy->sety( enemy->gety() -1);
             rect=enemy->rect;*/
        }
        else if(mdown && napadanimacija == false)
        {
            if(anirect.y >= premiky *5)
                anirect.y = 0;
            anirect.x = premikx * 4;

            if(anirect.y >= premiky*2)
                anirect.y = anirect.y + premiky+1;
            else
                anirect.y = anirect.y + premiky+0;

            if(anirect.y >= premiky*4)
            {
                anirect.y = 0;
            }
            /*enemy->sety( enemy->gety() +1);
            rect=enemy->rect;*/
        }


    }
}

void Boss::setrectx(int passrect)
{
    enemy->rect.x=passrect;
    rect=enemy->rect;
}

void Boss::setrecty(int passrect)
{
    enemy->rect.y=passrect;
    rect=enemy->rect;
}

SDL_Rect Boss::updaterect()
{
    return enemy->rect;
    rect = enemy->rect;
}

int Boss::getx()
{
    return enemy->getx();
}

int Boss::gety()
{
    return enemy->gety();
}

void Boss::nastavix(int x)
{
    rect.x = x;
    enemy->rect.x = x;
}

void Boss::nastaviy(int y)
{
    rect.y = y;
    enemy->rect.y = y;
}

void Boss::umri()
{
    if(SDL_GetTicks()-cas>100)
    {

        cas = SDL_GetTicks();
        if(animacija2 == false)
        {
            if(desno)
            {
                anirect.x = premikx+premikx+premikx;
                anirect.y = 504;
                desno = true;
                levo = false;
                gor = false;
                dol = false;
            }
            else if(levo)
            {
                anirect.x = premikx+premikx+premikx;
                anirect.y = 504;
                desno = false;
                levo = true;
                gor = false;
                dol = false;
            }
            else if(gor)
            {
                anirect.x = 0;
                anirect.y = 504;
                desno = false;
                levo = false;
                gor = true;
                dol = false;
            }
            else if(dol)
            {
                anirect.x = premikx * 3;
                anirect.y = 504;
                desno = false;
                levo = false;
                gor = false;
                dol = true;
            }
            animacija2 = true;
        }
        else
        {
            {
                if(desno)
                {
                    anirect.x = premikx*0;
                    anirect.y = 568;
                    desno = true;
                    levo = false;
                    gor = false;
                    dol = false;
                }
                else if(levo)
                {
                    anirect.x = premikx*0;
                    anirect.y = 568;
                    desno = false;
                    levo = true;
                    gor = false;
                    dol = false;
                }
                else if(gor)
                {
                    anirect.x = premikx*4;
                    anirect.y = 504;
                    desno = false;
                    levo = false;
                    gor = true;
                    dol = false;
                }
                else if(dol)
                {
                    anirect.x = premikx * 0;
                    anirect.y = 568;
                    desno = false;
                    levo = false;
                    gor = false;
                    dol = true;
                }
            }
        }
    }
}
