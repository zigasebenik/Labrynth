#include "Hero.h"

Hero::Hero(SDLsetup* passsetup, int passscreenw, int passscreenh)
{

    TTF_Init();

    mright = false;
    mleft = false;
    mup = false;
    mdown = false;
    odpri = false;
    streljaj = 0;
    gledalevo = false;
    gledagor = false;
    gledadol = false;
    gledadesno = false;
    napadanimacija = false;
    casregen = SDL_GetTicks();
    bonusdamage = 0;
    bonushpregen = 0;
    bonusmanaregen = 0;
    bonusst = -1;

    cassporocilo = SDL_GetTicks();
    initsporocilo = false;
    bonusdamage = 0;

    resetzemljevid = SDL_GetTicks();


    aup = false;
    aright  =false;
    adown = false;
    aleft = false;
    menjavaorozja = 0;

    levo=false;
    desno=false;
    gor=false;
    dol=false;

    x = 0;
    y = 0;
    //w = 13;
    //h = 16;
    w=9;
    h=9;

    ///hero
    //herorect.x = 0;
    //herorect.y = 0;
    //herorect.w = 96/3;
    //herorect.h = 128/4;
    //premikx = 96/3;
    //premiky = 128/4;

    ///wc2 hero
    herorect.x = 0;
    herorect.y = 0;
    herorect.w = 370/5;
    herorect.h = 624/11;
    premikx = herorect.w;
    premiky = herorect.h;

    cout<<"premikX "<<premikx<<endl;
    cout<<"premiky "<<premiky<<endl;

    cas = SDL_GetTicks();
    casodpiranja = SDL_GetTicks();
    casstreljaj = SDL_GetTicks();
    casmenjava = SDL_GetTicks();
    casnapad = SDL_GetTicks();
    casnapadpritisk = SDL_GetTicks();

    setup = passsetup;

    //to je kockica
    //hero = new Sprite(setup->vrnirender(),"vrata.png",rand()%8*100+20,rand()%6*100+10,10,10,0,0,0,0);

    //to je stricek
    //hero = new Sprite(setup->vrnirender(),"hero.png",rand()%8*100+20,rand()%6*100+10,w,h,0,0,0,0);

    ///wc2 knight
    hero = new Sprite(setup->vrnirender(),"knight.png",rand()%8*100+20,rand()%6*100+10,w,h,0,0,0,0);

    rect = hero->rect;

    levelheight=0;

    screenw = passscreenw;
    screenh = passscreenh;


    staticxy.x=(screenw/2) + 20;
    staticxy.y=(screenh/2) + 20;
    staticxy.w=70;
    staticxy.h=85;

    cameraX = 0;
    cameraY = 0;

    life.w = 600;
    life.h = 50;

    mana.w = 600;
    mana.h = 25;
}

Hero::~Hero()
{
    delete hero;
    TTF_Quit();
}

bool Hero::funkcije()
{

    //drawanimacijastatic();
    //drawanimacija();
    //draw();
    tipkovnica();
    straniokna();

    sporocilo(bonusst,cameraX,cameraY);
    napadzmecem(orozja[0]);
    // zivljenjekazi();
    return zemljevid;
    zemljevid = false;
}

void Hero::drawanimacijastatic()
{

    hero->drawanistatic(herorect,staticxy);
    SDL_RenderDrawRect(setup->vrnirender(),&rect);
}

void Hero::drawanimacija()
{
    hero->drawani(herorect);
}

void Hero::draw()
{
    hero->draw();
}

void Hero::straniokna()
{
    if(hero->rect.x+hero->rect.w>1600)
    {
        hero->rect.x=1600-hero->rect.w-2;
        hero->setx(hero->rect.x);


        //cout << "desno"<<endl;
    }

    if(hero->rect.x < 0)
    {
        hero->rect.x=hero->rect.x+2;
        hero->setx(hero->rect.x);
    }

    if(hero->rect.y+hero->rect.h>1000)
    {
        hero->rect.y=1000-hero->rect.h-2;
        hero->sety(hero->rect.y);
    }

    if(hero->rect.y<0)
    {
        hero->rect.y=2;
        hero->sety(hero->rect.y);
    }
}

void Hero::tipkovnica()
{
    switch(setup->vrnievent()->type)
    {
    case SDL_KEYDOWN:

        switch(setup->vrnievent()->key.keysym.sym)
        {
        case SDLK_a:
            mleft=true;
            gledalevo = true;
            gledadesno = false;
            gledagor = false;
            gledadol = false;
            break;

        case SDLK_s:
            mdown=true;
            gledalevo = false;
            gledadesno = false;
            gledagor = false;
            gledadol = true;
            break;

        case SDLK_d:
            mright=true;
            gledalevo = false;
            gledadesno = true;
            gledagor = false;
            gledadol = false;
            break;

        case SDLK_w:
            mup=true;
            gledalevo = false;
            gledadesno = false;
            gledagor = true;
            gledadol = false;
            break;

        case SDLK_r:
            zemljevid = viewmap();
            break;

        case SDLK_e:
            if(SDL_GetTicks()-casodpiranja>500)
            {
                odpri = true;
                casodpiranja = SDL_GetTicks();
            }
            break;

        case SDLK_SPACE:

            if(menjavaorozja == 0 && napadanimacija == false && mup == false && mright == false && mdown == false && mleft == false)
            {
                if(SDL_GetTicks()-casnapadpritisk>300)
                {
                    orozja[0]=true;
                    casnapadpritisk = SDL_GetTicks();
                }
            }
            else if(menjavaorozja==1 && mana.w > 219)
                if(SDL_GetTicks()-casstreljaj>300)
                {
                    streljaj++;
                    orozja[1] = true;
                    casstreljaj = SDL_GetTicks();
                    if(streljaj >= 35)
                        streljaj = 0;

                }
            break;

        case SDLK_q:
            if(SDL_GetTicks()-casmenjava>100)
            {
                menjavaorozja++;
                casmenjava = SDL_GetTicks();
                if(menjavaorozja >= 2)
                    menjavaorozja = 0;
                cout << "menjavaorozja"<<menjavaorozja<<endl;

            }
            break;

        default:
            break;
        }

        break;

    case SDL_KEYUP:
        switch(setup->vrnievent()->key.keysym.sym)
        {
        case SDLK_a:
            mleft=false;
            break;

        case SDLK_s:
            mdown=false;
            break;

        case SDLK_d:
            mright=false;
            break;

        case SDLK_w:
            mup=false;
            break;

        case SDLK_e:
            odpri = false;
            break;

        case SDLK_r:
            zemljevid = false;
            break;

        case SDLK_SPACE:
            for(int i=0; i<10; i++)
                orozja[i] = 0;
            break;
        }
    default:
        break;
    }

    ///stari hero
    /*if(cas+ 5 < SDL_GetTicks())
    {

        cas = SDL_GetTicks();

        if(mright)
        {
            hero->setx( hero->getx() +2);
            herorect.y = premiky * 2;
            herorect.x = herorect.x + premikx;
            if(herorect.x >= 96)
            {
                herorect.x = 0;
            }
            rect=hero->rect;
            x=rect.x;
        }
        if(mleft)
        {
            hero->setx( hero->getx() -2);
            herorect.y = 32;
            herorect.x = herorect.x + premikx;
            if(herorect.x >= 96)
            {
                herorect.x = 0;
            }
            rect=hero->rect;
            x=rect.x;
        }
        if(mup)
        {
            hero->sety( hero->gety() -2);
            herorect.y = premiky * 3;
            herorect.x = herorect.x + premikx;
            if(herorect.x >= 96)
            {
                herorect.x = 0;
            }
            rect=hero->rect;
            y=rect.y;
        }
        if(mdown)
        {
            hero->sety( hero->gety() +2);
            herorect.y = 0;
            herorect.x = herorect.x + premikx;
            if(herorect.x >= 96)
            {
                herorect.x = 0;
            }
            rect=hero->rect;
            y=rect.y;
        }
        cas = SDL_GetTicks();*/


    ///novi hero
    if(SDL_GetTicks()-cas>50)
    {

        cas = SDL_GetTicks();

        if(mright && napadanimacija == false)
        {
            if(herorect.y == (premiky+0)*3)
                herorect.y += premiky-5;
            else
                herorect.y += premiky+0;

            herorect.x = premikx+premikx;
            if(herorect.y >= (premiky-0)*4)
            {
                herorect.y = 0;
            }
        }
        else if(mleft && napadanimacija == false)
        {
            if(herorect.y == (premiky+0)*3)
                herorect.y += premiky-5;
            else
                herorect.y += premiky+0;
            herorect.x = premikx+premikx;
            if(herorect.y >= (premiky-0)*4)
            {
                herorect.y = 0;
            }
        }
        else if(mup && napadanimacija == false)
        {
            herorect.x = 0;
            if(herorect.y == (premiky+0)*1)
                herorect.y += premiky+2;
            else
                herorect.y += premiky+0;

            if(herorect.y >= (premiky+0)*5)
            {
                herorect.y = 0;
            }
        }
        else if(mdown && napadanimacija == false)
        {
            herorect.x = premikx * 4;

            if(herorect.y == premiky*0)
                herorect.y = herorect.y + premiky+2;
            else if(herorect.y == premiky*3)
                herorect.y = herorect.y + premiky-9;
            else
                herorect.y = herorect.y + premiky+0;

            if(herorect.y >= premiky*5)
            {
                herorect.y = 0;
            }
        }
    }

    ///premikanje herota

    if(mright && napadanimacija == false)
    {
        hero->setx( hero->getx() +1);
        rect=hero->rect;
        x=rect.x;
    }
    if(mleft && napadanimacija == false)
    {
        hero->setx( hero->getx() -1);
        rect=hero->rect;
        x=rect.x;
    }
    if(mup && napadanimacija == false)
    {
        hero->sety( hero->gety() -1);
        rect=hero->rect;
        y=rect.y;
    }
    if(mdown && napadanimacija == false)
    {
        hero->sety( hero->gety() +1);
        rect=hero->rect;
        y=rect.y;
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



SDL_Rect Hero::setrectx(int passrect)
{

    hero->rect.x=passrect;
    rect=hero->rect;
    x=rect.x;
}

SDL_Rect Hero::setrecty(int passrect)
{
    hero->rect.y=passrect;
    rect=hero->rect;
    y= rect.y;
}

SDL_Rect Hero::updaterect()
{
    return hero->rect;
    rect = hero->rect;
}

int Hero::getx()
{
    return x;
    return hero->getx();
}

int Hero::gety()
{
    return hero->gety();
}

void Hero::nastavix(int x)
{
    rect.x = x;
    hero->rect.x = x;
}

void Hero::nastaviy(int y)
{
    rect.y = y;
    hero->rect.y = y;
}

void Hero::napadzmecem(bool triger)
{

    if(triger)
    {
        napadanimacija = true;
        herorect.y = premiky *5;
    }

    if(napadanimacija)
        if(SDL_GetTicks()-casnapad>100)
        {

            casnapad = SDL_GetTicks();

            if(gledadesno)
            {
                herorect.y = herorect.y + premiky;
                herorect.x = premikx+premikx;
                if(herorect.y >= (premiky-0)*9)
                {
                    herorect.y = premiky*0;
                    napadanimacija=false;
                }
            }
            else if(gledalevo)
            {
                herorect.y = herorect.y + premiky;
                herorect.x = premikx+premikx;
                if(herorect.y >= (premiky-0)*9)
                {
                    herorect.y = premiky*0;
                    napadanimacija=false;
                }
            }
            else if(gledagor)
            {
                herorect.x = 0;
                herorect.y += premiky;
                if(herorect.y >= (premiky+0)*9)
                {
                    herorect.y = 0;
                    napadanimacija = false;
                }
            }
            else if(gledadol)
            {
                herorect.x = premikx * 4;
                herorect.y = herorect.y + premiky;
                if(herorect.y >= premiky*9)
                {
                    herorect.y = 0;
                    napadanimacija = false;
                }
            }
        }
}

void Hero::lifebar()
{
    if(SDL_GetTicks()-casregen>100)
    {
        casregen = SDL_GetTicks();
        if(mana.w<600)
            mana.w += 1 + bonusmanaregen;

        if(life.w<600)
            life.w += 1 + bonushpregen;
    }

    SDL_Rect ozadje;
    ozadje.x = 0;
    ozadje.y = 850+25;
    ozadje.w = 1700;
    ozadje.h = 1000;

    life.x = 50;
    life.y = 875+25;


    mana.x = 50;
    mana.y = 940+25;
    ///rdeca


    SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);
    SDL_RenderFillRect(setup->vrnirender(), &ozadje);
    SDL_RenderDrawRect(setup->vrnirender(),&ozadje);

    if(life.w > 150)
        SDL_SetRenderDrawColor(setup->vrnirender(), 0, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(setup->vrnirender(), 255, 0, 0, 255);

    SDL_RenderFillRect(setup->vrnirender(), &life);
    SDL_RenderDrawRect(setup->vrnirender(),&life);

    SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 255, 255);
    SDL_RenderFillRect(setup->vrnirender(), &mana);
    SDL_RenderDrawRect(setup->vrnirender(),&mana);

    SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);
}

void Hero::bonuschesti(int r,int x1, int y1)
{

    int tmp = r;
    while(tmp == bonusst||tmp == predprejsni)
        tmp = rand()%3;

    predprejsni = bonusst;
    if(tmp == 0)
    {
        bonusdamage += 1;
        bonusst = 0;
        initsporocilo = false;
    }
    if(tmp == 1)
    {
        bonushpregen += 1;
        bonusst = 1;
        initsporocilo = false;
    }
    if(tmp == 2)
    {
        bonusmanaregen += 1;
        bonusst = 2;
        initsporocilo = false;
    }
    xsporocilo = x1;
    ysporocilo = y1;
}

void Hero::pisi(string kaj,int velikost,int x,int y)
{

    font = TTF_OpenFont("TTF/OpenSans-Regular.ttf",velikost);
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    textSurface = TTF_RenderText_Solid(font,kaj.c_str(),color);
    text = SDL_CreateTextureFromSurface(setup->vrnirender(),textSurface);


    textRect.x = x;
    textRect.y = y;

    SDL_QueryTexture(text,NULL,NULL,&textRect.w,&textRect.h);

    SDL_RenderCopy(setup->vrnirender(),text,NULL,&textRect);

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    SDL_DestroyTexture(text);

}

void Hero::sporocilo(int r,int x1,int y1)
{
    if(initsporocilo == false)
    {

        if(r == 0)
        {
            pisi("bonus DAMAGE",10,x1,y1);
        }
        if(r == 1)
        {
            pisi("bonus HP REGEN",10,x1,y1);
        }
        if(r == 2)
        {
            pisi("bonus MANA REGEN",10,x1,y1);
        }
    }

    if(SDL_GetTicks()-cassporocilo>6000)
    {
        initsporocilo = true;
        cassporocilo = SDL_GetTicks();

    }
}

bool Hero::viewmap()
{
    if(SDL_GetTicks() - resetzemljevid > 1000 *10 )
    {
        resetzemljevid = SDL_GetTicks();
        return true;
    }
    else
    {
        return false;
    }
}

void Hero::bosssobacollision()
{
    if(hero->rect.x+hero->rect.w>180)
    {
        hero->rect.x=180-hero->rect.w-2;
        hero->setx(hero->rect.x);


        //cout << "desno"<<endl;
    }

    if(hero->rect.x < 0)
    {
        hero->rect.x=hero->rect.x+2;
        hero->setx(hero->rect.x);
    }

    if(hero->rect.y+hero->rect.h>120)
    {
        hero->rect.y=120-hero->rect.h-2;
        hero->sety(hero->rect.y);
    }

    if(hero->rect.y<0)
    {
        hero->rect.y=2;
        hero->sety(hero->rect.y);
    }

}

