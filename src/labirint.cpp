#include "labirint.h"

labirint::labirint(SDL_Renderer* renderpass, int screenwpass, int screenhpass, SDLsetup *passsetup)
{
    setup = passsetup;

    TTF_Init();

    render = renderpass;
    screenw = screenwpass;
    screenh = screenhpass;
    izberitezavnost = false;

    //stsob = rand()%20+5;


    casodpiranja = SDL_GetTicks();

    caszemljevid = SDL_GetTicks();

    caszadetekzoge = SDL_GetTicks();

    maxcas = 0;

    trenutnicasigranja = -1;
    caszacetek = SDL_GetTicks();

    pavza = false;
    konec = false;
    izhod = false;
    zmaga = false;
    arenazbosom = false;
    zemljevid = false;
    initherocoordinates = false;
    startscreen = true;
    izberitezavnost = false;
    vnoshighscore = false;
    survival = false;




}

labirint::~labirint()
{
    TTF_Quit();
}

bool labirint::collision(SDL_Rect r1, SDL_Rect r2)
{
    /*if(prvi.x+prvi.w*10+20>drugi.x && prvi.x<drugi.x+drugi.w*10+20&&
       prvi.y+prvi.h*10+20>drugi.y && prvi.y<drugi.y+drugi.h*10+20)
        return true;
    else
        return false;
    int leftA = prvi.x ;
    int rightA = (prvi.x) + (prvi.w);
    int topA = prvi.y;
    int bottomA = (prvi.y) + (prvi.h);

    int leftB = drugi.x ;
    int rightB = (drugi.x ) + (drugi.w);
    int topB = drugi.y ;
    int bottomB = (drugi.y ) + (drugi.h);

    cout<<"drugi.y"<<drugi.y *10<<endl;
    cout<<"drugi.y"<<drugi.y *10<<endl;
    cout<<"drugi.y"<<drugi.y *10<<endl;
    cout<<"drugi.y"<<drugi.y *10<<endl;


    if( bottomA < topB )
    {
        return false;
    }
    if( topA > bottomB )
    {
        return false;
    }
    if( rightA < leftB )
    {
        return false;
    }
    if( leftA > rightB )
    {
        return false;
    }
    return true;*/



    /* r1.x *= kamera->scaleX;
     r1.y *= kamera->scaleY;
     r1.w *= kamera->scaleX;
     r1.h *= kamera->scaleY;

     r2.x *= kamera->scaleX;
     r2.y *= kamera->scaleY;
     r2.w *= kamera->scaleX;
     r2.h *= kamera->scaleY;*/

    r1.x *= 10;
    r1.y *= 10;
    r1.w *= 10;
    r1.h *= 10;

    r2.x *= 10;
    r2.y *= 10;
    r2.w *= 10;
    r2.h *= 10;
    cout<<"rect 1 X:"<<r1.x<<endl;
    cout<<"rect 1 Y:"<<r1.y<<endl;
    cout<<"rect 1 W:"<<r1.w<<endl;
    cout<<"rect 1 H:"<<r1.h<<endl;

    cout<<"rect 2 X:"<<r2.x<<endl;
    cout<<"rect 2 Y:"<<r2.y<<endl;
    cout<<"rect 2 W:"<<r2.w<<endl;
    cout<<"rect 2 H:"<<r2.h<<endl;

    if(r1.x + r1.w >= r2.x && r1.x <= r2.x + r2.w && r1.y + r1.h >= r2.y && r1.y <= r2.y + r2.h)
    {
        return true;
    }
    return false;

}

bool labirint::primerjajvrata(int i, int iplus1, char kordinata)
{
    if(kordinata == 'x')
        if(tabelasob[i]->stvrat[0]->vrata.x<tabelasob[iplus1]->stvrat[0]->vrata.x)
            return 1;
        else
            return 0;
    else if(kordinata == 'y')
        if(tabelasob[i]->stvrat[0]->vrata.y<tabelasob[iplus1]->stvrat[0]->vrata.y)
            return 1;
        else
            return 0;
}

void labirint::test()
{
    for(int i=0; i<100; i++)
        for(int j = 0; j<160; j+=2)
            nacrt[i][j]=100;

    for(int i=0; i<100; i++)
        for(int j = 1; j<160; j+=2)
            nacrt[i][j]=200;

    int i=0;
    for(int j=0; j<160; j++)
    {
        nacrt[i][j]=100;
    }

    i=99;
    for(int j=0; j<160; j++)
    {
        nacrt[i][j]=100;
    }

    int j=0;
    for(int i=0; i<100; i++)
    {
        nacrt[i][j]=100;
    }
    j=159;
    for(int i=0; i<100; i++)
    {
        nacrt[i][j]=100;
    }
}

void labirint::randomnacrt()
{
    player = new Hero(setup, screenw, screenh);
    kamera = new Camera(setup->vrnirender(), screenw,screenh);

    for(int i=0; i<50; i++)
        firebal[i] = new Fireball(setup);

    for(int i=0; i<10; i++)
        {
            zoga[i] = new Zoga(setup);
            zoga[i]->zoga->rect.x = i*10;
        }
    aktivnezoge = 0;

    switch(rand()%3)
    {
    case 0:
        for(int i=0; i<100; i++)
            for(int j=0; j<160; j++)
            {
                nacrt[i][j]=1100;
            }
        break;

    case 1:
        for(int i=0; i<100; i++)
            for(int j=0; j<160; j++)
            {
                nacrt[i][j]=900;
            }
        break;

    case 2:
        for(int i=0; i<100; i++)
            for(int j=0; j<160; j++)
            {
                nacrt[i][j]=1000;
            }
        break;
    }
    zacetek(0,0,screenw/10,screenh/10,300);
    ///////////SOBE///////////////

    SDL_Rect tmp;
    tmp.w = 1;
    tmp.h = 1;

    tabelasob[0] = new soba(setup,screenw,screenh,2);
    for(int j=0; j<tabelasob[0]->geth(); j++)
        for(int k=0; k<tabelasob[0]->getw(); k++)
        {
            nacrt[tabelasob[0]->gety()+j][tabelasob[0]->getx()+k]=500;
            //cout<<tabelasob[i]->gety()+j<<"  "<<tabelasob[i]->getx()+k<<endl;
        }

    tmp = nastavivrata(tabelasob[0]->getx(),tabelasob[0]->gety(),tabelasob[0]->getw(),tabelasob[0]->geth(),300);
    tabelasob[0]->stvrat[0]->setvrata(tmp);
    tmp.x ++;
    tmp.y ++;
    tabelasob[0]->stvrat[1]->setvrata(tmp);


    while(tabelasob[0]->stvrat[1]->getposition()==tabelasob[0]->stvrat[0]->getposition())
        tabelasob[0]->stvrat[1]->randomnov(tabelasob[0]->getx(),tabelasob[0]->gety(),tabelasob[0]->getw(),tabelasob[0]->geth(),300);

    int preveri = 0;
    for(int i=1; i<stsob; i++)
    {
        switch(rand()%3)
        {
        case 0:
            tabelasob[i] = new soba(setup,screenw,screenh,i+1);
            preveri = i;


            for(int j=0; j<i; j++)
                while(collision(tabelasob[preveri]->getrect(),tabelasob[j]->getrect()))
                {
                    tabelasob[preveri]->randomnov();
                }

            for(int j=0; j<tabelasob[i]->geth(); j++)
                for(int k=0; k<tabelasob[i]->getw(); k++)
                {
                    if(j>=0&&j<100 && k>=0 && k<160)
                        nacrt[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]=500;
                    //cout<<tabelasob[i]->gety()+j<<"  "<<tabelasob[i]->getx()+k<<endl;
                }
            cout<<"////////////////////////"<<i<<endl;

            // tabelasob[i]->stvrat[0]->setvrata(nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300));

            tmp = nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300);
            tabelasob[i]->stvrat[0]->setvrata(tmp);
            tmp.x ++;
            tmp.y ++;
            tabelasob[i]->stvrat[1]->setvrata(tmp);
            //tabelasob[i]->stvrat[1]->setvrata(nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300));
            while(tabelasob[i]->stvrat[1]->getposition()==tabelasob[i]->stvrat[0]->getposition())
                tabelasob[i]->stvrat[1]->randomnov(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300);

            break;

        case 1:
            tabelasob[i] = new soba(setup,screenw,screenh,i+1);
            preveri = i;


            for(int j=0; j<i; j++)
                while(collision(tabelasob[preveri]->getrect(),tabelasob[j]->getrect()))
                {
                    tabelasob[preveri]->randomnov();
                }

            for(int j=0; j<tabelasob[i]->geth(); j++)
                for(int k=0; k<tabelasob[i]->getw(); k++)
                {
                    if(j>=0&&j<100 && k>=0 && k<160)
                        nacrt[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]=800;
                    //cout<<tabelasob[i]->gety()+j<<"  "<<tabelasob[i]->getx()+k<<endl;
                }
            cout<<"////////////////////////"<<i<<endl;

            // tabelasob[i]->stvrat[0]->setvrata(nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300));

            tmp = nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300);
            tabelasob[i]->stvrat[0]->setvrata(tmp);
            tmp.x ++;
            tmp.y ++;
            tabelasob[i]->stvrat[1]->setvrata(tmp);
            //tabelasob[i]->stvrat[1]->setvrata(nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300));
            while(tabelasob[i]->stvrat[1]->getposition()==tabelasob[i]->stvrat[0]->getposition())
                tabelasob[i]->stvrat[1]->randomnov(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300);

            break;

        case 2:
            tabelasob[i] = new soba(setup,screenw,screenh,i+1);
            preveri = i;


            for(int j=0; j<i; j++)
                while(collision(tabelasob[preveri]->getrect(),tabelasob[j]->getrect()))
                {
                    tabelasob[preveri]->randomnov();
                }

            for(int j=0; j<tabelasob[i]->geth(); j++)
                for(int k=0; k<tabelasob[i]->getw(); k++)
                {
                    if(j>=0&&j<100 && k>=0 && k<160)
                        nacrt[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]=700;
                    //cout<<tabelasob[i]->gety()+j<<"  "<<tabelasob[i]->getx()+k<<endl;
                }
            cout<<"////////////////////////"<<i<<endl;

            // tabelasob[i]->stvrat[0]->setvrata(nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300));

            tmp = nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300);
            tabelasob[i]->stvrat[0]->setvrata(tmp);
            tmp.x ++;
            tmp.y ++;
            tabelasob[i]->stvrat[1]->setvrata(tmp);
            //tabelasob[i]->stvrat[1]->setvrata(nastavivrata(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300));
            while(tabelasob[i]->stvrat[1]->getposition()==tabelasob[i]->stvrat[0]->getposition())
                tabelasob[i]->stvrat[1]->randomnov(tabelasob[i]->getx(),tabelasob[i]->gety(),tabelasob[i]->getw(),tabelasob[i]->geth(),300);

            break;
        }
    }



    for(int i=0; i<stsob; i++)
    {
        for(int j=tabelasob[i]->gety();  j<tabelasob[i]->geth()+tabelasob[i]->gety();  j++)
        {
            //cout<<"j "<<j<<endl;
            //tabela[j][tabelasob[i]->getx()-1]->settileview(tabela[j][tabelasob[i]->getx()-1]->premikX*1,tabela[j][tabelasob[i]->getx()-1]->premikY*9);
            nacrt[j][tabelasob[i]->getx()-1] = 600;
        }

        for(int j=tabelasob[i]->gety();  j<tabelasob[i]->geth()+tabelasob[i]->gety();  j++)
        {
            //cout<<"j "<<j<<endl;
            //tabela[j][tabelasob[i]->getx()-1]->settileview(tabela[j][tabelasob[i]->getx()-1]->premikX*1,tabela[j][tabelasob[i]->getx()-1]->premikY*9);
            nacrt[j][tabelasob[i]->getx()+tabelasob[i]->getw()] = 600;
        }

        for(int j=tabelasob[i]->getx();  j<tabelasob[i]->getw()+tabelasob[i]->getx();  j++)
        {
            //cout<<"j "<<j<<endl;
            //tabela[j][tabelasob[i]->getx()-1]->settileview(tabela[j][tabelasob[i]->getx()-1]->premikX*1,tabela[j][tabelasob[i]->getx()-1]->premikY*9);
            nacrt[tabelasob[i]->gety()-1][j] = 600;
        }

        for(int j=tabelasob[i]->getx();  j<tabelasob[i]->getw()+tabelasob[i]->getx();  j++)
        {
            //cout<<"j "<<j<<endl;
            //tabela[j][tabelasob[i]->getx()-1]->settileview(tabela[j][tabelasob[i]->getx()-1]->premikX*1,tabela[j][tabelasob[i]->getx()-1]->premikY*9);
            nacrt[tabelasob[i]->gety()+tabelasob[i]->geth()][j] = 600;
        }

        nacrt[tabelasob[i]->gety()-1][tabelasob[i]->getx()-1] = 600;
        nacrt[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()] = 600;
        nacrt[tabelasob[i]->gety()-1][tabelasob[i]->getx()+tabelasob[i]->getw()] = 600;
        nacrt[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()-1] = 600;

    }

    povezivrata(tabela,0);
    povezivrata(tabela,1);
//povezivrata(tabela,2);
//povezivrata(tabela,3);

    player->setrectx(tabelasob[0]->getx()*10+50);
    player->setrecty(tabelasob[0]->gety()*10+50);

///chesti//////////////////////////////////

    int xchest = 0;
    int ychest = 0;
    for(int i=0; i<stsob; i++)
    {
        xchest = (tabelasob[i]->dungeon.w/2 + tabelasob[i]->dungeon.x)*10;
        ychest = (tabelasob[i]->dungeon.h/2 + tabelasob[i]->dungeon.y)*10;
        stskrinj ++;
        chesti[i] = new Chest(setup,xchest,ychest);
    }

///////////////////////BOSS SOBE///////////////////////////////////////////////////////////////////////////////////////////
    /*SDL_Rect tocka;
    tocka.w = 1;
    tocka.h = 1;

    for(int i=0;i<stbosov;i++)
    {
        bosstabela[i] = new soba;
        int preveri = i;
        bosstabela[i]->boss=1;

        for(int j=0; j<i; j++)
            while(collision(bosstabela[preveri]->getrect(),tabelasob[j]->getrect()) || collision(bosstabela[preveri]->getrect(),bosstabela[j]->getrect()))
            {
                bosstabela[preveri]->randomnov();
            }

        for(int j=0; j<bosstabela[i]->geth(); j++)
            for(int k=0; k<bosstabela[i]->getw(); k++)
            {
                nacrt[bosstabela[i]->gety()+j][bosstabela[i]->getx()+k]=400;
            }
        cout<<"////////////////////////"<<i<<endl;

        bosstabela[i]->stvrat[0]->setvrata(nastavivrata(bosstabela[i]->getx(),bosstabela[i]->gety(),bosstabela[i]->getw(),bosstabela[i]->geth(),300));
        while(bosstabela[i]->stvrat[1]->getposition()==bosstabela[i]->stvrat[0]->getposition())
            bosstabela[i]->stvrat[1]->randomnov(bosstabela[i]->getx(),bosstabela[i]->gety(),bosstabela[i]->getw(),bosstabela[i]->geth(),300);


        bool gor=false, dol=false, levo=false, desno=false;
        int offset = 0;

        while(1)
            if(nacrt[bosstabela[i]->stvrat[0]->vrata.y][bosstabela[i]->stvrat[0]->vrata.x+offset] == 200)
            {
                desno = true;
                break;
            }
            else if(nacrt[bosstabela[i]->stvrat[0]->vrata.y][bosstabela[i]->stvrat[0]->vrata.x-offset] == 200)
            {
                levo = true;
                break;
            }
            else if(nacrt[bosstabela[i]->stvrat[0]->vrata.y+offset][bosstabela[i]->stvrat[0]->vrata.x] == 200)
            {
                dol = true;
                break;
            }
            else if(nacrt[bosstabela[i]->stvrat[0]->vrata.y-offset][bosstabela[i]->stvrat[0]->vrata.x] == 200)
            {
                gor = true;
                break;
            }
            else
                offset++;

        if(desno == true)
            for(int j=bosstabela[i]->stvrat[0]->vrata.x;j<bosstabela[i]->stvrat[0]->vrata.x+offset;j++)
                nacrt[bosstabela[i]->stvrat[0]->vrata.y][j];
        else if(levo = true)
            for(int j=bosstabela[i]->stvrat[0]->vrata.x;j<bosstabela[i]->stvrat[0]->vrata.x-offset;j++)
                nacrt[bosstabela[i]->stvrat[0]->vrata.y][j];
        else if(dol = true)
            for(int j=bosstabela[i]->stvrat[0]->vrata.y;j<bosstabela[i]->stvrat[0]->vrata.y+offset;j++)
                nacrt[j][bosstabela[i]->stvrat[0]->vrata.x];
        else if(gor = true)
            for(int j=bosstabela[i]->stvrat[0]->vrata.y;j<bosstabela[i]->stvrat[0]->vrata.y-offset;j++)
                nacrt[j][bosstabela[i]->stvrat[0]->vrata.x];
        else
            cout<<"ne dela"<<endl;
    }



    nakljucno = rand()%2;
    int xkonec = 0;

    for(int i=0; i<stsob-1; i++)
    if(tabelasob[i]->stvrat[0]->vrata.x<tabelasob[i+1]->stvrat[0]->vrata.x)
    for(int j=tabelasob[i]->stvrat[0]->vrata.x; j<=tabelasob[i+1]->stvrat[0]->vrata.x; j++)
    {
       if(nakljucno == 1)
       {
           nacrt[tabelasob[i]->stvrat[0]->vrata.y][j] = 200;
           xkonec = j;
       }
       else
       {
           nacrt[tabelasob[i+1]->stvrat[0]->vrata.y][j] = 200;
           xkonec = j;
       }

    }
    else
    for(int j=tabelasob[i+1]->stvrat[0]->vrata.x; j<=tabelasob[i]->stvrat[0]->vrata.x; j++)
    {
       if(nakljucno == 1)
           {
               nacrt[tabelasob[i]->stvrat[0]->vrata.y][j] = 200;
               xkonec = j;
           }
       else
       {
           nacrt[tabelasob[i+1]->stvrat[0]->vrata.y][j] = 200;
           xkonec = j;
       }
    }
    /////////NAVPICNI//////////
    nakljucno = rand()%2;
    for(int i=0; i<stsob-1; i++)
    if(tabelasob[i]->stvrat[0]->vrata.y<tabelasob[i+1]->stvrat[0]->vrata.y)
    for(int j=tabelasob[i]->stvrat[0]->vrata.y; j<=tabelasob[i+1]->stvrat[0]->vrata.y; j++)
    {
        if(nakljucno == 1)
            nacrt[j][tabelasob[i]->stvrat[0]->vrata.x] = 200;
        else
            nacrt[j][tabelasob[i+1]->stvrat[0]->vrata.x] = 200;
    }
    else
    for(int j=tabelasob[i+1]->stvrat[0]->vrata.y; j<=tabelasob[i]->stvrat[0]->vrata.y; j++)
    {
        if(nakljucno == 1)
            nacrt[j][tabelasob[i]->stvrat[0]->vrata.x] = 200;
        else
            nacrt[j][tabelasob[i+1]->stvrat[0]->vrata.x] = 200;
    }*/

}

void labirint::randomlabirint()
{
    for(int i=0; i<100; i++)
        for(int j=0; j<160; j++)
        {
            tabela[i][j]=new Tile(render);
            tabela[i][j]->init(nacrt[i][j]);
        }

    for(int i=0; i<99; i++)
    {
        for(int j=1; j<160; j++)
        {
            tabela[i][j]->setx(tabela[i][j-1]->getx()+tabela[i][j]->getw());
            tabela[i][j]->sety(tabela[i][j-1]->gety());
        }
        tabela[i+1][0]->sety(tabela[i][159]->gety()+tabela[i][0]->geth());
    }

    for(int j=1; j<160; j++)
    {
        tabela[99][j]->setx(tabela[99][j-1]->getx()+tabela[99][j]->getw());
        tabela[99][j]->sety(tabela[99][j-1]->gety());
    }
}

void labirint::drawlabirint()
{
    if(konec == false && zmaga == false && startscreen == false && izberitezavnost == false)
    {
        if(pavza == false)
        {
            if(arenazbosom == false && zemljevid==false)
            {
                //cout<<"arena z bosom"<<endl;
                int sety = 0;
                int setx = 0;

                for(int i=0; i<stsob; i++)
                {
                    chesti[i]->drawAni();

                }

                for(int i=0; i<100; i++)
                    for(int j=0; j<160; j++)
                    {
                        if(tabela[i][j]->imeSlike == "soba" ||tabela[i][j]->imeSlike == "zid1" ||tabela[i][j]->imeSlike == "winter"||tabela[i][j]->imeSlike == "wasteland")
                        {
                            kamera->render( ResourceManager::resources[tabela[i][j]->imeSlike],&tabela[i][j]->anirect,&tabela[i][j]->rect,0);
                        }
                        else
                            kamera->render( ResourceManager::resources[tabela[i][j]->imeSlike],NULL,&tabela[i][j]->rect,0);
                    }
                //kamera->cameraCoordinates(tabelasob[4]->grunt[0]->rect.x,tabelasob[4]->grunt[0]->rect.y);

                bool vsimrtvi = false;
                for(int i=0; i<stsob; i++)
                {
                    for(int j=0; j<tabelasob[i]->stenemy; j++)
                        /*if(tabelasob[i]->grunt[j]->ziv == true)
                             vsimrtvi = true;
                         else
                             vsimrtvi = false;*/

                        chesti[i]->skrita = vsimrtvi;
                }

                for(int i=0; i<stsob; i++)
                {
                    if(chesti[i]->skrita == false)
                        kamera->render(chesti[i]->zaklad->image,&chesti[i]->zaklad->anirect,&chesti[i]->rect,0);
                    chesti[i]->xkamera = kamera->r.x;
                    chesti[i]->ykamera = kamera->r.y;
                }



                for(int i=0; i<stsob; i++)
                {
                    for(int j=0; j<tabelasob[i]->stenemy; j++)
                    {
                        if(tabelasob[i]->grunt[j]->desno == true && tabelasob[i]->grunt[j]->ziv == false)
                            kamera->render(tabelasob[i]->grunt[j]->enemy->image,&tabelasob[i]->grunt[j]->anirect,&tabelasob[i]->grunt[j]->rect,0);
                        else if(tabelasob[i]->grunt[j]->mleft == true )
                            kamera->render(tabelasob[i]->grunt[j]->enemy->image,&tabelasob[i]->grunt[j]->anirect,&tabelasob[i]->grunt[j]->rect,1);
                        else
                            kamera->render(tabelasob[i]->grunt[j]->enemy->image,&tabelasob[i]->grunt[j]->anirect,&tabelasob[i]->grunt[j]->rect,0);
                    }
                }

                //SDL_RenderDrawRect(setup->vrnirender(),&kamera->r);
                //player->tipkovnica();
                ///gledanje zivecih enemyov v sobi
                for(int i=0; i<stsob; i++)
                    if(tabelasob[i]->vsimrtvi() == true)
                        chesti[i]->skrita = false;
                    else
                        chesti[i]->skrita = true;

                ///odpiranje chestov
                if(player->odpri == true)
                {
                    if(SDL_GetTicks()-casodpiranja>400)
                        for(int i=0; i<stsob; i++)
                        {
                            if(player->rect.x+player->rect.w+5>chesti[i]->rect.x && player->rect.x<chesti[i]->rect.x+chesti[i]->rect.w+5&&
                                    player->rect.y+player->rect.h+5>chesti[i]->rect.y && player->rect.y<chesti[i]->rect.y+chesti[i]->rect.h+5
                                    &&chesti[i]->skrita == false)
                            {
                                if(chesti[i]->odpri == false && chesti[i]->animacije<5)
                                {
                                    chesti[i]->odpri = true;
                                    chesti[i]->zapri = false;

                                    if(chesti[i]->bonus == true)
                                    {
                                        cout << chesti[i]->rect.x<<endl;
                                        cout << chesti[i]->rect.y << endl;
                                        player->bonuschesti(rand()%3,chesti[i]->xkamera,chesti[i]->ykamera);
                                        chesti[i]->bonus = false;
                                    }
                                }

                                else
                                {
                                    chesti[i]->odpri = false;
                                    chesti[i]->zapri = true;

                                }


                            }
                            cout << "/////////////odpri "<<chesti[i]->odpri<<endl;
                            cout << "/////////////zapri"<<chesti[i]->zapri<<endl;
                            casodpiranja = SDL_GetTicks();
                        }
                }



                for(int i=0; i<stsob; i++)
                {
                    tabelasob[i]->funkcije(player,kamera,firebal);
                    for(int j=0; j<tabelasob[i]->stenemy; j++)
                        if(tabelasob[i]->grunt[j]->ziv==true)
                            kamera->renderrect(&tabelasob[i]->grunt[j]->life);
                }


                if(int(floor(player->gety()/10)-1)<100 && int(floor(player->gety()/10)-1)>=0 && int(floor(player->getx()/10))<160 && int(floor(player->getx()/10))>=0)
                    if(tabela[int(floor(player->gety()/10)-1)][int(floor(player->getx()/10))]->gety()+ tabela[int(floor(player->gety()/10)-1)][int(floor(player->getx()/10))]->geth() +2 >=
                            player->rect.y
                            &&
                            (nacrt[int(floor(player->gety()/10)-1)][int(floor(player->getx()/10))] == 100
                             ||nacrt[int(floor(player->gety()/10)-1)][int(floor(player->getx()/10))] == 600
                             ||nacrt[int(floor(player->gety()/10)-1)][int(floor(player->getx()/10))] == 1100
                             ||nacrt[int(floor(player->gety()/10)-1)][int(floor(player->getx()/10))] == 900
                             ||nacrt[int(floor(player->gety()/10)-1)][int(floor(player->getx()/10))] == 1000
                             ||nacrtArena[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 1000)
                      )
                        player->nastaviy(player->gety()+1);
                if( int(floor(player->gety()/10)+1)<100 && int(floor(player->gety()/10)+1)>=0 && int(floor(player->getx()/10))<160 && int(floor(player->getx()/10))>=0)
                    if(tabela[int(floor(player->gety()/10)+1)][int(floor(player->getx()/10))]->gety()<=
                            player->rect.y + player->rect.h
                            &&(
                                nacrt[int(floor(player->gety()/10)+1)][int(floor(player->getx()/10))] == 100
                                ||nacrt[int(floor(player->gety()/10)+1)][int(floor(player->getx()/10))] == 600
                                ||nacrt[int(floor(player->gety()/10)+1)][int(floor(player->getx()/10))] == 1100
                                ||nacrt[int(floor(player->gety()/10)+1)][int(floor(player->getx()/10))] == 900
                                ||nacrt[int(floor(player->gety()/10)+1)][int(floor(player->getx()/10))] == 1000
                               ||nacrtArena[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 1000))
                        player->nastaviy(player->gety()-1);


                if( int(floor(player->gety()/10))<100 && int(floor(player->gety()/10))>=0 && int(floor(player->getx()/10)-1)<160 && int(floor(player->getx()/10)-1)>=0)
                    if(tabela[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)]->getx()+ tabela[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)]->getw() >=
                            player->rect.x
                            &&(
                                nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 100||
                                nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 600
                                ||nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 1100
                                ||nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 900
                                ||nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 1000
                               ||nacrtArena[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 1000))
                        player->nastavix(player->getx()+1);


                if( int(floor(player->gety()/10))<100 && int(floor(player->gety()/10))>=0 &&int(floor(player->getx()/10)+1)<160 && int(floor(player->getx()/10)+1)>=0)
                    if(tabela[int(floor(player->gety()/10))][int(floor(player->getx()/10)+1)]->getx()+ tabela[int(floor(player->gety()/10))][int(floor(player->getx()/10)+1)]->getw() >=
                            player->rect.x
                            &&(
                                nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)+1)] == 100
                                ||nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)+1)] == 600
                                ||nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)+1)] == 1100
                                ||nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)+1)] == 1000
                                ||nacrt[int(floor(player->gety()/10))][int(floor(player->getx()/10)+1)] == 900
                               ||nacrtArena[int(floor(player->gety()/10))][int(floor(player->getx()/10)-1)] == 1000))
                        player->nastavix(player->getx()-1);

                /*int tmp = 0;
                for(int i=0;i<stsob;i++)
                    for(int j=0;j<tabelasob[i]->stenemy;j++)
                        if(tabelasob[i]->grunt[j]->ziv == true)
                            tmp++;*/
                /*char *intStr = itoa(tmp);
                string str = string(intStr);*/

                int tmp = 0;
                for(int i=0; i<stsob; i++)
                    if(chesti[i]->bonus == true)
                        tmp++;

                ss.str("");
                ss << tmp;
                str = "";
                str = "St neodprtih skrinj: ";
                str += ss.str();
                pisi(str,20,10,10);

                if(tmp <= 0)
                {
                    player->life.w = 600;
                    player->mana.w = 600;
                    arenazbosom = true;
                }

            }
            else if(zemljevid == true)
            {
                //cout<<"zemlevid == true"<<endl;

                kamera->camerawh(1600,1000);

                for(int i=0; i<100; i++)
                    for(int j=0; j<160; j++)
                    {
                        if(tabela[i][j]->imeSlike == "soba" ||tabela[i][j]->imeSlike == "zid1" ||tabela[i][j]->imeSlike == "winter"||tabela[i][j]->imeSlike == "wasteland")
                        {
                            kamera->render( ResourceManager::resources[tabela[i][j]->imeSlike],&tabela[i][j]->anirect,&tabela[i][j]->rect,0);
                        }
                        else
                            kamera->render( ResourceManager::resources[tabela[i][j]->imeSlike],NULL,&tabela[i][j]->rect,0);
                    }


                if(SDL_GetTicks()-caszemljevid>5000)
                {
                    //cout << zemljevid <<endl;
                    zemljevidcooldown = SDL_GetTicks();
                    zemljevid = false;
                    kamera->camerawh(160,100);
                }


            }
            else if(arenazbosom == true)
            {
                player->bosssobacollision();
                //cout<<"arena z bosom == true"<<endl;
                if(initherocoordinates == false)
                {
                    player->setrectx(10);
                    player->setrecty(10);
                    bos->enemy->rect.x = player->x + 50;
                    bos->enemy->rect.y = player->y + 50;
                    initherocoordinates = true;

                    for(int i=0;i<aktivnezoge;i++)
                        zoga[i]->aktivna = true;
                }
                cout << "aktivne zoge "<<aktivnezoge<<endl;

                caszemljevid = SDL_GetTicks();
                ///risi areno
                for(int i=0; i<100; i++)
                    for(int j=0; j<160; j++)
                    {
                        kamera->render(ResourceManager::resources[tArena[i][j]->imeSlike],&tArena[i][j]->anirect,&tArena[i][j]->rect,0);
                    }

                for(int i=0; i<10;i++)
                {
                    zoga[i]->funkcije();

                    if( zoga[i]->zoga->rect.x + zoga[i]->zoga->rect.w > player->rect.x&&
                        player->rect.x + player->rect.w - zoga[i]->zoga->rect.w> zoga[i]->zoga->rect.x&&
                        zoga[i]->zoga->rect.y + zoga[i]->zoga->rect.h > player->rect.y&&
                        player->rect.y + player->rect.h - zoga[i]->zoga->rect.h> zoga[i]->zoga->rect.y &&
                        zoga[i]->aktivna == true
                        && SDL_GetTicks() - caszadetekzoge>1000)
                        {
                            player->life.w -=80;
                            caszadetekzoge = SDL_GetTicks();
                        }
                }
                pisi("Boss",20,10,10);

                bos->funkcije(player,kamera,firebal);

                if(bos->ziv == false)
                    zmaga = true;
                SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);



                for(int i=0;i<10;i++)
                {
                    if(zoga[i]->aktivna == true)
                    {
                        kamera->render(ResourceManager::resources["zoga"],NULL,&zoga[i]->zoga->rect,0);
                    }
                }

            }

            ///fireball////////////////////

            if(arenazbosom == true)
            {
                //cout<<"arena z bosom == true"<<endl;
                SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);
                if(bos->desno == true && bos->ziv == false)
                    kamera->render(bos->enemy->image,&bos->anirect,&bos->rect,0);
                else if(bos->mleft == true )
                    kamera->render(bos->enemy->image,&bos->anirect,&bos->rect,1);
                else
                    kamera->render(bos->enemy->image,&bos->anirect,&bos->rect,0);

            }
            //////////////////////////////////////////////////



            if(zemljevid == false)
            {
                SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);
                if(player->orozja[1] == true)
                    firebal[player->streljaj]->aktivna=1;
                SDL_Rect tmp;
                for(int i=0; i<40; i++)
                {
                    firebal[i]->funkcije(player,screenw,screenh,player->cameraX,player->cameraY);
                    tmp.x = firebal[i]->firebal->rect.x;
                    tmp.y = firebal[i]->firebal->rect.y;
                    tmp.w = firebal[i]->firebal->rect.w;
                    tmp.h = firebal[i]->firebal->rect.h;
                    if(firebal[i]->aktivna == true)
                        kamera->render(firebal[i]->firebal->image,NULL,&tmp,0);
                }

                kamera->render(player->hero->image,&player->herorect,&player->rect,player->mleft||player->gledalevo);
                player->cameraX = kamera->r.x;
                player->cameraY = kamera->r.y;
                kamera->cameraCoordinates(player->x+player->w/2,player->y+player->h/2);



                if(setup->vrnievent()->type == SDL_KEYDOWN)
                    if(setup->vrnievent()->key.keysym.sym == SDLK_r)
                    {
                        if(SDL_GetTicks() - zemljevidcooldown>1000 * 10)
                        {
                            zemljevid = true;
                        }
                    }

                if(zemljevid == true)
                    caszemljevid = SDL_GetTicks();


                player->lifebar();
            }

            if(setup->vrnievent()->type == SDL_KEYDOWN)
                if(setup->vrnievent()->key.keysym.sym == SDLK_p)
                {
                    pavza = true;
                }

        }
        else if(pavza == true)
        {
            //cout<<"pavza == true"<<endl;
            SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);
            if(setup->vrnievent()->type == SDL_KEYDOWN)
                if(setup->vrnievent()->key.keysym.sym == SDLK_p)
                {
                    pavza = false;
                }
            pisi("Pause",60,700,400);
            pisi("IZHOD",50,1400,900);
            pisi("SEENKRAT",50,25,900);

            int mouseX = 0;
            int mouseY = 0;
            SDL_GetMouseState(&mouseX,&mouseY);
            if(mouseX>1400 && mouseY>900 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
                izhod = true;
            else if(mouseX<300 && mouseY>900 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
            {
                cout << "zacetek seenkrat"<<endl;
                delete bos;
                delete player;
                delete kamera;

                for(int i=0; i<50; i++)
                    delete firebal[i];

                for(int i=0; i<stsob; i++)
                    delete chesti[i];

                for(int i=0; i<stsob; i++)
                    delete tabelasob[i];

                for(int i=0; i<100; i++)
                    for(int j=0; j<160; j++)
                        delete tabela[i][j];

                for(int i=0; i<100; i++)
                    for(int j=0; j<160; j++)
                        delete tArena[i][j];
                cout << "konec brisanja"<<endl;


                pavza = false;
                konec = false;
                izhod = false;
                zmaga = false;
                arenazbosom = false;
                zemljevid = false;
                initherocoordinates = false;
                startscreen = false;
                izberitezavnost = false;
                vnoshighscore = false;

                izberitezavnost = true;
                pavza = false;
                cout << "konec seenkrat"<<endl;
            }
        }

        if(izberitezavnost == false)
        {

            player->funkcije();

            if(player->life.w < 0)
                konec = true;
        }

        //cout <<"konec game loopa"<<endl;
    }
    else if(konec == true || zmaga == true && survival==false)
    {
        SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);
        gameover();
        pisi("SEENKRAT",50,1100,900);

        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX,&mouseY);
        if(mouseX>1100 && mouseX<1350  && mouseY>900 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
        {
            cout << "zacetek seenkrat"<<endl;
            delete bos;
            delete player;
            delete kamera;

            for(int i=0; i<50; i++)
                delete firebal[i];

            for(int i=0; i<stsob; i++)
                delete chesti[i];

            for(int i=0; i<stsob; i++)
                delete tabelasob[i];

            for(int i=0; i<100; i++)
                for(int j=0; j<160; j++)
                    delete tabela[i][j];

            for(int i=0; i<100; i++)
                for(int j=0; j<160; j++)
                    delete tArena[i][j];
            cout << "konec brisanja"<<endl;


            pavza = false;
            konec = false;
            izhod = false;
            zmaga = false;
            arenazbosom = false;
            zemljevid = false;
            initherocoordinates = false;
            startscreen = false;
            izberitezavnost = false;
            vnoshighscore = false;

            izberitezavnost = true;
            pavza = false;
            cout << "konec seenkrat"<<endl;
        }
    }
    else if(konec == true || zmaga == true && survival==true)
    {
        delete bos;
            delete player;
            delete kamera;

            for(int i=0; i<50; i++)
                delete firebal[i];

            for(int i=0; i<stsob; i++)
                delete chesti[i];

            for(int i=0; i<stsob; i++)
                delete tabelasob[i];

            for(int i=0; i<100; i++)
                for(int j=0; j<160; j++)
                    delete tabela[i][j];

            for(int i=0; i<100; i++)
                for(int j=0; j<160; j++)
                    delete tArena[i][j];
            cout << "konec brisanja"<<endl;

            pavza = false;
            konec = false;
            izhod = false;
            zmaga = false;
            arenazbosom = false;
            zemljevid = false;
            initherocoordinates = false;
            startscreen = false;
            izberitezavnost = false;
            vnoshighscore = false;

            izberitezavnost = false;
            pavza = false;

            stsob++;
            zemljevid = true;
            izberitezavnost = false;
            survival = true;
            caszacetek = SDL_GetTicks();
            tezavnost = 1;
            stbosov = 1;


            //test();
            cout <<"randomnacrt"<<endl;
            randomnacrt();
            cout <<"randomlabirint"<<endl;
            randomlabirint();
            cout <<"settiles"<<endl;
            settiles();
            cout <<"setarena"<<endl;
            setarena();

            bos = new Boss(setup,screenw,screenh,"ogre.png",10,20,370,820,5,11,tezavnost,stsob-1);
            cout<<"bos"<<endl;
            caszemljevid = SDL_GetTicks();
            if(stsob % 4 == 0)
                aktivnezoge = stsob / 4;

    }
    else if(startscreen == true)
    {
        SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);
        pisi("RANDOM DUNGEON GENERATOR",60,350,400);
        pisi("START",50,25,900);
        pisi("IZHOD",50,1400,900);

        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX,&mouseY);
        if(mouseX>1400 && mouseY>900 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
            izhod = true;
        else if(mouseX<300 && mouseY>900 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
        {
            izberitezavnost = true;
            startscreen = false;
        }
    }
    else if(izberitezavnost == true)
    {
        cout<<endl <<"izberi tezavnost "<<endl;
        SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX,&mouseY);

        SDL_Rect tmp;
        pisi("EASY",50,25,500);
        pisi("MEDIUM",50,700,500);
        pisi("SURVIVAL",50,700,900);
        pisi("HARD",50,1450,500);

        if(mouseX<900 && mouseX>700 && mouseX>500 && mouseY>900 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
        {
            zemljevid = true;
            izberitezavnost = false;
            survival = true;
            caszacetek = SDL_GetTicks();
            tezavnost = 1;
            stsob = 4;
            stbosov = 1;


            //test();
            cout <<"randomnacrt"<<endl;
            randomnacrt();
            cout <<"randomlabirint"<<endl;
            randomlabirint();
            cout <<"settiles"<<endl;
            settiles();
            cout <<"setarena"<<endl;
            setarena();

            bos = new Boss(setup,screenw,screenh,"ogre.png",10,20,370,820,5,11,tezavnost,0);
            cout<<"bos"<<endl;
            caszemljevid = SDL_GetTicks();

            if(stsob % 4 == 0)
                aktivnezoge = stsob / 4;
        }

        if(mouseX<300 && mouseY>500 && mouseY<600 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
        {
            zemljevid = true;
            izberitezavnost = false;
            caszacetek = SDL_GetTicks();
            tezavnost = 1;
            stsob = 4;
            stbosov = 1;


            //test();
            cout <<"randomnacrt"<<endl;
            randomnacrt();
            cout <<"randomlabirint"<<endl;
            randomlabirint();
            cout <<"settiles"<<endl;
            settiles();
            cout <<"setarena"<<endl;
            setarena();

            bos = new Boss(setup,screenw,screenh,"ogre.png",10,20,370,820,5,11,tezavnost,0);
            cout<<"bos"<<endl;
            caszemljevid = SDL_GetTicks();

             if(stsob % 4 == 0)
                aktivnezoge = stsob / 4;
        }

        if(mouseX<900 && mouseX>700 && mouseY>500 && mouseY<600 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
        {
            zemljevid = true;
            izberitezavnost = false;
            caszacetek = SDL_GetTicks();
            tezavnost = 2;

            stsob = 8;
            stbosov = 1;


            //test();
            cout <<"randomnacrt"<<endl;
            randomnacrt();
            cout <<"randomlabirint"<<endl;
            randomlabirint();
            cout <<"settiles"<<endl;
            settiles();
            cout <<"setarena"<<endl;
            setarena();
            bos = new Boss(setup,screenw,screenh,"ogre.png",10,20,370,820,5,11,tezavnost,0);
            caszemljevid = SDL_GetTicks();

            if(stsob % 4 == 0)
                aktivnezoge = stsob / 4;
        }
        if(mouseX<1600 && mouseX>1450 && mouseY>500 && mouseY<600 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
        {
            zemljevid = true;
            izberitezavnost = false;
            caszacetek = SDL_GetTicks();
            tezavnost = 3;

            stsob = 12;
            stbosov = 1;

            //test();
            cout <<"randomnacrt"<<endl;
            randomnacrt();
            cout <<"randomlabirint"<<endl;
            randomlabirint();
            cout <<"settiles"<<endl;
            settiles();
            cout <<"setarena"<<endl;
            setarena();
            bos = new Boss(setup,screenw,screenh,"ogre.png",10,20,370,820,5,11,tezavnost,0);
            caszemljevid = SDL_GetTicks();

             if(stsob % 4 == 0)
                aktivnezoge = stsob / 4;
        }
    }


}

SDL_Rect labirint::nastavivrata(int x, int y, int w, int h, int vrednost)
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
    /* cout<<"w"<<w<<endl;
     cout<<"h"<<h<<endl;
     cout<<"x"<<x<<endl;
     cout<<"y"<<y<<endl;*/
    int kordinatex = jzacetek+x;
    int kordinatey = izacetek+y;
    /* cout<<"kordinatex"<<kordinatex<<endl;
     cout<<"kordinatey"<<kordinatey<<endl;*/
    nacrt[kordinatey][kordinatex]=vrednost;

    SDL_Rect vrataxy;

    vrataxy.x = kordinatex;
    vrataxy.y = kordinatey;

    vrataxy.w = 1;
    vrataxy.h = 1;

    return vrataxy;
}


void labirint::zacetek(int x, int y, int w, int h, int vrednost)
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
    /* cout<<"w"<<w<<endl;
     cout<<"h"<<h<<endl;
     cout<<"x"<<x<<endl;
     cout<<"y"<<y<<endl;*/
    int kordinatex = jzacetek+x;
    int kordinatey = izacetek+y;
    /*cout<<"kordinatex"<<kordinatex<<endl;
    cout<<"kordinatey"<<kordinatey<<endl;*/
    nacrt[kordinatey][kordinatex]=vrednost;
}

void labirint::settiles()
{

    int nakljucno = 0;
    int svetlotemno = 0;

    for(int i=0; i<100; i++)
        for(int j=0; j<160; j++)
        {
            if(nacrt[i][j]==1100)
            {
                switch(rand()%19)
                {
                case 0:
                    tabela[i][j]->settileview(0,tabela[i][j]->premikY*16);
                    break;
                case 1:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*1,tabela[i][j]->premikY*16);
                    break;
                case 2:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*2,tabela[i][j]->premikY*16);
                    break;
                case 3:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*3,tabela[i][j]->premikY*16);
                    break;
                case 4:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*4,tabela[i][j]->premikY*16);
                    break;
                case 5:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*5,tabela[i][j]->premikY*16);
                    break;
                case 6:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*6,tabela[i][j]->premikY*16);
                    break;
                case 7:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*7,tabela[i][j]->premikY*16);
                    break;
                case 8:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*8,tabela[i][j]->premikY*16);
                    break;
                case 9:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*9,tabela[i][j]->premikY*16);
                    break;
                case 10:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*10,tabela[i][j]->premikY*16);
                    break;
                case 11:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*11,tabela[i][j]->premikY*16);
                    break;
                case 12:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*12,tabela[i][j]->premikY*16);
                    break;
                case 13:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*13,tabela[i][j]->premikY*16);
                    break;
                case 14:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*14,tabela[i][j]->premikY*16);
                    break;
                case 15:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*15,tabela[i][j]->premikY*16);
                    break;
                case 16:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*16,tabela[i][j]->premikY*16);
                    break;
                case 17:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*17,tabela[i][j]->premikY*16);
                    break;
                case 18:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*18,tabela[i][j]->premikY*16);
                    break;
                default:
                    break;
                }
            }
            else if(nacrt[i][j]==900)
            {
                switch(rand()%24)
                {
                case 0:
                    tabela[i][j]->settileview(0,tabela[i][j]->premikY*16);
                    break;
                case 1:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*1,tabela[i][j]->premikY*16);
                    break;
                case 2:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*2,tabela[i][j]->premikY*16);
                    break;
                case 3:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*3,tabela[i][j]->premikY*16);
                    break;
                case 4:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*4,tabela[i][j]->premikY*16);
                    break;
                case 5:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*5,tabela[i][j]->premikY*16);
                    break;
                case 6:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*6,tabela[i][j]->premikY*16);
                    break;
                case 7:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*7,tabela[i][j]->premikY*16);
                    break;
                case 8:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*8,tabela[i][j]->premikY*16);
                    break;
                case 9:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*9,tabela[i][j]->premikY*16);
                    break;
                case 10:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*10,tabela[i][j]->premikY*16);
                    break;
                case 11:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*11,tabela[i][j]->premikY*16);
                    break;
                case 12:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*12,tabela[i][j]->premikY*16);
                    break;
                case 13:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*13,tabela[i][j]->premikY*16);
                    break;
                case 14:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*14,tabela[i][j]->premikY*16);
                    break;
                case 15:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*15,tabela[i][j]->premikY*16);
                    break;
                case 16:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*16,tabela[i][j]->premikY*16);
                    break;
                case 17:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*17,tabela[i][j]->premikY*16);
                    break;
                case 18:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*18,tabela[i][j]->premikY*16);
                    break;
                case 19:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*0,tabela[i][j]->premikY*17);
                    break;
                case 20:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*1,tabela[i][j]->premikY*17);
                    break;
                case 21:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*2,tabela[i][j]->premikY*17);
                    break;
                case 22:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*6,tabela[i][j]->premikY*17);
                    break;
                case 23:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*7,tabela[i][j]->premikY*17);
                    break;
                default:
                    break;
                }
            }
            else if(nacrt[i][j]==1000)
            {
                switch(rand()%19)
                {
                case 0:
                    tabela[i][j]->settileview(0,tabela[i][j]->premikY*16);
                    break;
                case 1:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*1,tabela[i][j]->premikY*16);
                    break;
                case 2:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*2,tabela[i][j]->premikY*16);
                    break;
                case 3:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*3,tabela[i][j]->premikY*16);
                    break;
                case 4:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*4,tabela[i][j]->premikY*16);
                    break;
                case 5:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*5,tabela[i][j]->premikY*16);
                    break;
                case 6:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*6,tabela[i][j]->premikY*16);
                    break;
                case 7:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*7,tabela[i][j]->premikY*16);
                    break;
                case 8:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*8,tabela[i][j]->premikY*16);
                    break;
                case 9:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*9,tabela[i][j]->premikY*16);
                    break;
                case 10:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*10,tabela[i][j]->premikY*16);
                    break;
                case 11:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*11,tabela[i][j]->premikY*16);
                    break;
                case 12:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*12,tabela[i][j]->premikY*16);
                    break;
                case 13:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*13,tabela[i][j]->premikY*16);
                    break;
                case 14:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*14,tabela[i][j]->premikY*16);
                    break;
                case 15:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*15,tabela[i][j]->premikY*16);
                    break;
                case 16:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*16,tabela[i][j]->premikY*16);
                    break;
                case 17:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*17,tabela[i][j]->premikY*16);
                    break;
                case 18:
                    tabela[i][j]->settileview(tabela[i][j]->premikX*18,tabela[i][j]->premikY*16);
                    break;
                default:
                    break;
                }
            }
        }

    cout <<"konec1"<<endl;
    for(int i=0; i<stsob; i++)
    {
        nakljucno = rand()%2;
        svetlotemno = rand()%2;
        for(int j=0; j<tabelasob[i]->geth(); j++)
            for(int k=0; k<tabelasob[i]->getw(); k++)
            {
                //nacrt[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]=500;
                if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                    if(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->imeSlike == "soba")
                    {
                        if(nakljucno == 1)
                        {
                            if(svetlotemno == 1)
                            {
                                if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                    switch(rand()%8)
                                    {
                                    case 0:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(0,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 1:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 2:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*2,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 3:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*14,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 4:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*15,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 5:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*16,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 6:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*17,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 7:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*18,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    default:
                                        break;
                                    }
                            }
                            else
                            {
                                if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                    switch(rand()%8+1)
                                    {
                                    case 1:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*3,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 2:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*4,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 3:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*5,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 4:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*6,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 5:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*7,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 6:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*8,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 7:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*9,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    case 8:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*10,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                        break;
                                    default:
                                        break;
                                    }
                            }
                        }

                        else if(nakljucno == 0)
                        {
                            if(svetlotemno == 1)
                            {
                                if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                    switch(rand()%11)
                                    {
                                    case 0:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*3,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 1:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*4,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 2:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*5,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 3:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*6,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 4:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*7,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 5:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*8,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 6:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*9,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 7:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*10,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 8:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*11,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 9:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*12,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 10:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*13,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    default:
                                        break;
                                    }
                            }
                            else
                            {
                                if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                    switch(rand()%11)
                                    {
                                    case 0:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(0,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 1:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 2:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*2,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                        break;
                                    case 3:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*11,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                        break;
                                    case 4:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*12,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                        break;
                                    case 5:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*13,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                        break;
                                    case 6:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*14,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                        break;
                                    case 7:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*15,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                        break;
                                    case 8:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*16,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                        break;
                                    case 9:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*17,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                        break;
                                    case 10:
                                        tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*18,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                        break;


                                    default:
                                        break;
                                    }
                            }

                        }
                    }
                    else if(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->imeSlike == "winter")
                    {
                        if(j>=0 && j<100 && k>=0 && k<160)
                            if(nakljucno == 1)
                            {
                                if(svetlotemno == 0)
                                {
                                    if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                        switch(rand()%9)
                                        {
                                        case 0:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*3,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 1:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*4,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 2:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*5,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 3:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*6,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 4:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*7,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 5:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*8,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 6:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*9,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 7:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*10,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 8:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*11,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;

                                        default:
                                            break;
                                        }
                                }
                                else
                                {
                                    if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                        switch(rand()%11)
                                        {

                                        case 0:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*0,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 1:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*1,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 2:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*7,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 3:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*8,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 4:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*9,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 5:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*10,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 6:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*11,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 7:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*12,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 8:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*13,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 9:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*14,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 10:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*15,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;

                                        default:
                                            break;
                                        }
                                }

                            }

                            else if(nakljucno == 0)
                            {
                                if(svetlotemno == 1)
                                {
                                    if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                        switch(rand()%9)
                                        {
                                        case 0:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*8,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 1:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*9,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 2:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*10,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 3:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*11,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 4:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*12,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 5:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*13,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 6:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*14,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 7:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*15,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 8:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*16,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        default:
                                            break;
                                        }
                                }

                                else
                                {
                                    if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                        switch(rand()%9)
                                        {

                                        case 0:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*17,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 1:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*18,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 2:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*0,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 3:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*1,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 4:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*2,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 5:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*3,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 6:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*4,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 7:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*5,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 8:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*6,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        default:
                                            break;
                                        }
                                }

                            }
                    }
                    else if(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->imeSlike == "wasteland" )
                    {
                        if(j>=0 && j<100 && k>=0 && k<160)
                            if(nakljucno == 1)
                            {
                                if(svetlotemno == 1)
                                {
                                    if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                        switch(rand()%11)
                                        {
                                        case 0:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(0,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 1:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 2:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*2,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 3:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*3,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 4:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*4,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 5:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*5,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 6:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*6,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 7:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*7,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 8:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*8,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 9:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*9,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;
                                        case 10:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*10,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*19);
                                            break;

                                        }
                                }
                                else
                                {
                                    if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                        switch(rand()%15)
                                        {
                                        case 0:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*4,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 1:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*5,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 2:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*6,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 3:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*7,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 4:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*8,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 5:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*9,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 6:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*10,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 7:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*11,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 8:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*12,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 9:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*13,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 10:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*14,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 11:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*15,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 12:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*16,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 13:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*17,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 14:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*18,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;

                                        default:
                                            break;
                                        }

                                }
                            }

                            else if(nakljucno == 0)
                            {
                                if(svetlotemno == 1)
                                {
                                    if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                        switch(rand()%9)
                                        {

                                        case 0:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*7,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 1:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*8,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 2:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*9,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 3:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*10,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 4:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*11,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 5:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*12,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 6:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*13,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 7:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*14,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 8:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*15,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;

                                        default:
                                            break;
                                        }
                                }
                                else
                                {
                                    if(tabelasob[i]->gety()+j<100 && tabelasob[i]->gety()+j>=0 && tabelasob[i]->getx()+k<160 && tabelasob[i]->getx()+k>0)
                                        switch(rand()%7)
                                        {
                                        case 0:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*0,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 1:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*2,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 2:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*2,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 3:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*3,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*18);
                                            break;
                                        case 4:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*16,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 5:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*17,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        case 6:
                                            tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->settileview(tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikX*18,tabela[tabelasob[i]->gety()+j][tabelasob[i]->getx()+k]->premikY*17);
                                            break;
                                        default:
                                            break;
                                        }
                                }

                            }
                    }
            }
    }
    cout << "konec tilov v sobi"<<endl;
    for(int i=0; i<stsob; i++)
    {
        for(int j=tabelasob[i]->gety();  j<tabelasob[i]->geth()+tabelasob[i]->gety();  j++)
        {

            nakljucno = rand()%3;
            if(j>=0 && j<100)
            {
                if((tabelasob[i]->getx()-1) > 0 && (tabelasob[i]->getx()-1)<160)
                {
                    switch(nakljucno)
                    {

                    case 0:
                        tabela[j][tabelasob[i]->getx()-1]->settileview(tabela[j][tabelasob[i]->getx()-1]->premikX*2,tabela[j][tabelasob[i]->getx()-1]->premikY*1);
                        break;
                    case 1:
                        tabela[j][tabelasob[i]->getx()-1]->settileview(tabela[j][tabelasob[i]->getx()-1]->premikX*0,tabela[j][tabelasob[i]->getx()-1]->premikY*3);
                        break;
                    case 2:
                        tabela[j][tabelasob[i]->getx()-1]->settileview(tabela[j][tabelasob[i]->getx()-1]->premikX*1,tabela[j][tabelasob[i]->getx()-1]->premikY*3);
                        break;
                    }
                }
            }
        }

        for(int j=tabelasob[i]->gety();  j<tabelasob[i]->geth()+tabelasob[i]->gety();  j++)
        {
            nakljucno = rand()%3;
            if(j>=0 && j<100)
            {

                if((tabelasob[i]->getx()+tabelasob[i]->getw()) > 0 && (tabelasob[i]->getx()+tabelasob[i]->getw())<160)
                {
                    switch(nakljucno)
                    {

                    case 0:
                        tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->settileview(tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*2,tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikY*1);
                        break;
                    case 1:
                        tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->settileview(tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*0,tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikY*3);
                        break;
                    case 2:
                        tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->settileview(tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*1,tabela[j][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikY*3);
                        break;
                    }
                }
            }
        }

        for(int j=tabelasob[i]->getx();  j<tabelasob[i]->getw()+tabelasob[i]->getx();  j++)
        {
            nakljucno = rand()%4;
            if(j>=0 && j<160)
            {
                if((tabelasob[i]->gety()-1)<100 && (tabelasob[i]->gety()-1)>=0)
                {
                    switch(nakljucno)
                    {
                    case 0:
                        tabela[tabelasob[i]->gety()-1][j]->settileview(tabela[tabelasob[i]->gety()-1][j]->premikX*8,tabela[tabelasob[i]->gety()-1][j]->premikY*1);
                        break;
                    case 1:
                        tabela[tabelasob[i]->gety()-1][j]->settileview(tabela[tabelasob[i]->gety()-1][j]->premikX*9,tabela[tabelasob[i]->gety()-1][j]->premikY*1);
                        break;
                    case 2:
                        tabela[tabelasob[i]->gety()-1][j]->settileview(tabela[tabelasob[i]->gety()-1][j]->premikX*7,tabela[tabelasob[i]->gety()-1][j]->premikY*3);
                        break;
                    case 3:
                        tabela[tabelasob[i]->gety()-1][j]->settileview(tabela[tabelasob[i]->gety()-1][j]->premikX*6,tabela[tabelasob[i]->gety()-1][j]->premikY*3);
                        break;
                    }
                }
            }

            for(int j=tabelasob[i]->getx();  j<tabelasob[i]->getw()+tabelasob[i]->getx();  j++)
            {
                nakljucno = rand()%4;
                if(j>=0 && j<160)
                {
                    if(tabelasob[i]->gety()+tabelasob[i]->geth()>=0 && tabelasob[i]->gety()+tabelasob[i]->geth()<100)
                    {
                        switch(nakljucno)
                        {
                        case 0:
                            tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->settileview(tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->premikX*8,tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->premikY*1);
                            break;
                        case 1:
                            tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->settileview(tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->premikX*9,tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->premikY*1);
                            break;
                        case 2:
                            tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->settileview(tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->premikX*7,tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->premikY*3);
                            break;
                        case 3:
                            tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->settileview(tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->premikX*6,tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][j]->premikY*3);
                            break;
                        }
                    }
                }
            }

            cout << "konec robov"<<endl;
            cout<<"0"<<endl;


            if((tabelasob[i]->gety()-1)<100 && (tabelasob[i]->gety()-1)>=0 && (tabelasob[i]->getx()-1)>=0 && (tabelasob[i]->getx()-1)<160 && tabelasob[i]->gety()+tabelasob[i]->geth()<100 && tabelasob[i]->gety()+tabelasob[i]->geth()>=0 && tabelasob[i]->getx()+tabelasob[i]->getw()>=0 &&tabelasob[i]->getx()+tabelasob[i]->getw()<160)
                tabela[tabelasob[i]->gety()-1][tabelasob[i]->getx()-1]->settileview(tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*0,
                        tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*1);
            cout<<"1"<<endl;

            if(tabelasob[i]->gety()+tabelasob[i]->geth()<100 && tabelasob[i]->gety()+tabelasob[i]->geth()>=0 && tabelasob[i]->getx()+tabelasob[i]->getw()<160 && tabelasob[i]->getx()+tabelasob[i]->getw()>=0)
                tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->settileview(tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*11,
                        tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*1);
            cout<<"2"<<endl;

            if(tabelasob[i]->gety()-1>=0 && tabelasob[i]->gety()-1<100 && tabelasob[i]->getx()+tabelasob[i]->getw()>= 0 && tabelasob[i]->getx()+tabelasob[i]->getw()<160 && tabelasob[i]->gety()+tabelasob[i]->geth()>=0 && tabelasob[i]->gety()+tabelasob[i]->geth()<100 && tabelasob[i]->getx()+tabelasob[i]->getw()>=0 && tabelasob[i]->getx()+tabelasob[i]->getw()<160)
                tabela[tabelasob[i]->gety()-1][tabelasob[i]->getx()+tabelasob[i]->getw()]->settileview(tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*7,
                        tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*1);
            cout<<"3"<<endl;

            if(tabelasob[i]->gety()+tabelasob[i]->geth()>=0 && tabelasob[i]->gety()+tabelasob[i]->geth()< 100 && tabelasob[i]->getx()>=1 && tabelasob[i]->getx()-1<160)
                tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()-1]->settileview(tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*4,
                        tabela[tabelasob[i]->gety()+tabelasob[i]->geth()][tabelasob[i]->getx()+tabelasob[i]->getw()]->premikX*1);
            cout<<"4"<<endl;
            cout << "konec kotov"<<endl;
        }

        cout << "konec settiles"<<endl;
    }
}


void labirint::povezivrata(Tile * tabela[100][160],int n)
{
    ////////////////////////HODNIKI/////////////////////
    ////VODORAVNI/////
    int nakljucno = rand()%2;
    xkonec = 0;

    for(int i=0; i<stsob-1; i++)
    {
        if(primerjajvrata(i,i+1,'x') && primerjajvrata(i,i+1,'y'))
            for(int j=tabelasob[i]->stvrat[n]->vrata.x; j<=tabelasob[i+1]->stvrat[n]->vrata.x; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[tabelasob[i]->stvrat[n]->vrata.y][j] = 200;
                    xkonec = tabelasob[i+1]->stvrat[n]->vrata.x;
                    //cout<<xkonec<<endl;
                }
                else
                {
                    nacrt[tabelasob[i+1]->stvrat[n]->vrata.y][j] = 200;
                    xkonec = tabelasob[i]->stvrat[n]->vrata.x;
                    //cout<<xkonec<<endl;
                }

            }
        if(primerjajvrata(i+1,i,'x') && primerjajvrata(i+1,i,'y'))
            for(int j=tabelasob[i+1]->stvrat[n]->vrata.x; j<=tabelasob[i]->stvrat[n]->vrata.x; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[tabelasob[i]->stvrat[n]->vrata.y][j] = 200;
                    xkonec = tabelasob[i+1]->stvrat[n]->vrata.x;
                    //cout<<xkonec<<endl;
                }
                else
                {
                    nacrt[tabelasob[i+1]->stvrat[n]->vrata.y][j] = 200;
                    xkonec = tabelasob[i]->stvrat[n]->vrata.x;
                    //cout<<xkonec<<endl;
                }
            }
        if(primerjajvrata(i,i+1,'x') && primerjajvrata(i+1,i,'y'))
        {
            for(int j=tabelasob[i]->stvrat[n]->vrata.x; j<=tabelasob[i+1]->stvrat[n]->vrata.x; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[tabelasob[i]->stvrat[n]->vrata.y][j] = 200;
                    xkonec = tabelasob[i+1]->stvrat[n]->vrata.x;
                    //cout<<xkonec<<endl;
                }
                else
                {
                    nacrt[tabelasob[i+1]->stvrat[n]->vrata.y][j] = 200;
                    xkonec = tabelasob[i]->stvrat[n]->vrata.x;
                    //cout<<xkonec<<endl;
                }
            }
        }
        if(primerjajvrata(i+1,i,'x') && primerjajvrata(i,i+1,'y'))
        {
            for(int j=tabelasob[i+1]->stvrat[n]->vrata.x; j<=tabelasob[i]->stvrat[n]->vrata.x; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[tabelasob[i]->stvrat[n]->vrata.y][j] = 200;
                    xkonec = tabelasob[i+1]->stvrat[n]->vrata.x;
                    //cout<<xkonec<<endl;
                }
                else
                {
                    nacrt[tabelasob[i+1]->stvrat[n]->vrata.y][j] = 200;
                    xkonec = tabelasob[i]->stvrat[n]->vrata.x;
                    //cout<<xkonec<<endl;
                }
            }
        }






        /////////NAVPICNI//////////
        nakljucno = rand()%2;
        if(primerjajvrata(i,i+1,'x') && primerjajvrata(i,i+1,'y'))
            for(int j=tabelasob[i]->stvrat[n]->vrata.y; j<=tabelasob[i+1]->stvrat[n]->vrata.y; j++)
            {
                //cout<<"tale1"<<endl;
                if(nakljucno == 1)
                {
                    nacrt[j][xkonec] = 200;
                }
                else
                {
                    nacrt[j][xkonec] = 200;
                }

            }
        if(primerjajvrata(i+1,i,'x') && primerjajvrata(i+1,i,'y'))
            for(int j=tabelasob[i+1]->stvrat[n]->vrata.y; j<=tabelasob[i]->stvrat[n]->vrata.y; j++)
            {
                //cout<<"tale2"<<endl;
                if(nakljucno == 1)
                {
                    nacrt[j][xkonec] = 200;
                }
                else
                {
                    nacrt[j][xkonec] = 200;
                }
            }
        if(primerjajvrata(i,i+1,'x') && primerjajvrata(i+1,i,'y'))
        {
            for(int j=tabelasob[i+1]->stvrat[n]->vrata.y; j<=tabelasob[i]->stvrat[n]->vrata.y; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[j][xkonec] = 200;
                }
                else
                {
                    nacrt[j][xkonec] = 200;
                }
            }
        }
        if(primerjajvrata(i+1,i,'x') && primerjajvrata(i,i+1,'y'))
        {
            for(int j=tabelasob[i]->stvrat[n]->vrata.y; j<=tabelasob[i+1]->stvrat[n]->vrata.y; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[j][xkonec] = 200;
                }
                else
                {
                    nacrt[j][xkonec] = 200;
                }
            }
        }

    }
}

/*////////////////////////HODNIKI/////////////////////
    ////VODORAVNI/////
    int nakljucno = rand()%2;
    xkonec = 0;

    for(int i=0; i<stsob-1; i++)
    {
        if(primerjajvrata(i,i+1,'x') && primerjajvrata(i,i+1,'y'))
            for(int j=tabelasob[i]->stvrat[0]->vrata.x; j<=tabelasob[i+1]->stvrat[0]->vrata.x; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[tabelasob[i]->stvrat[0]->vrata.y][j] = 200;
                    xkonec = tabelasob[i+1]->stvrat[0]->vrata.x;
                    //cout<<xkonec<<endl;
                }
                else
                {
                    nacrt[tabelasob[i+1]->stvrat[0]->vrata.y][j] = 200;
                    xkonec = tabelasob[i]->stvrat[0]->vrata.x;
                    //cout<<xkonec<<endl;
                }

            }
        if(primerjajvrata(i+1,i,'x') && primerjajvrata(i+1,i,'y'))
            for(int j=tabelasob[i+1]->stvrat[0]->vrata.x; j<=tabelasob[i]->stvrat[0]->vrata.x; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[tabelasob[i]->stvrat[0]->vrata.y][j] = 200;
                    xkonec = tabelasob[i+1]->stvrat[0]->vrata.x;
                    //cout<<xkonec<<endl;
                }
                else
                {
                    nacrt[tabelasob[i+1]->stvrat[0]->vrata.y][j] = 200;
                    xkonec = tabelasob[i]->stvrat[0]->vrata.x;
                    //cout<<xkonec<<endl;
                }
            }
        if(primerjajvrata(i,i+1,'x') && primerjajvrata(i+1,i,'y'))
        {
            for(int j=tabelasob[i]->stvrat[0]->vrata.x; j<=tabelasob[i+1]->stvrat[0]->vrata.x; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[tabelasob[i]->stvrat[0]->vrata.y][j] = 200;
                    xkonec = tabelasob[i+1]->stvrat[0]->vrata.x;
                    //cout<<xkonec<<endl;
                }
                else
                {
                    nacrt[tabelasob[i+1]->stvrat[0]->vrata.y][j] = 200;
                    xkonec = tabelasob[i]->stvrat[0]->vrata.x;
                    //cout<<xkonec<<endl;
                }
            }
        }
        if(primerjajvrata(i+1,i,'x') && primerjajvrata(i,i+1,'y'))
        {
            for(int j=tabelasob[i+1]->stvrat[0]->vrata.x; j<=tabelasob[i]->stvrat[0]->vrata.x; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[tabelasob[i]->stvrat[0]->vrata.y][j] = 200;
                    xkonec = tabelasob[i+1]->stvrat[0]->vrata.x;
                    //cout<<xkonec<<endl;
                }
                else
                {
                    nacrt[tabelasob[i+1]->stvrat[0]->vrata.y][j] = 200;
                    xkonec = tabelasob[i]->stvrat[0]->vrata.x;
                    //cout<<xkonec<<endl;
                }
            }
        }






        /////////NAVPICNI//////////
        nakljucno = rand()%2;
        if(primerjajvrata(i,i+1,'x') && primerjajvrata(i,i+1,'y'))
            for(int j=tabelasob[i]->stvrat[0]->vrata.y; j<=tabelasob[i+1]->stvrat[0]->vrata.y; j++)
            {
                //cout<<"tale1"<<endl;
                if(nakljucno == 1)
                {
                    nacrt[j][xkonec] = 200;
                }
                else
                {
                    nacrt[j][xkonec] = 200;
                }

            }
        if(primerjajvrata(i+1,i,'x') && primerjajvrata(i+1,i,'y'))
            for(int j=tabelasob[i+1]->stvrat[0]->vrata.y; j<=tabelasob[i]->stvrat[0]->vrata.y; j++)
            {
                //cout<<"tale2"<<endl;
                if(nakljucno == 1)
                {
                    nacrt[j][xkonec] = 200;
                }
                else
                {
                    nacrt[j][xkonec] = 200;
                }
            }
        if(primerjajvrata(i,i+1,'x') && primerjajvrata(i+1,i,'y'))
        {
            for(int j=tabelasob[i+1]->stvrat[0]->vrata.y; j<=tabelasob[i]->stvrat[0]->vrata.y; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[j][xkonec] = 200;
                }
                else
                {
                    nacrt[j][xkonec] = 200;
                }
            }
        }
        if(primerjajvrata(i+1,i,'x') && primerjajvrata(i,i+1,'y'))
        {
            for(int j=tabelasob[i]->stvrat[0]->vrata.y; j<=tabelasob[i+1]->stvrat[0]->vrata.y; j++)
            {
                if(nakljucno == 1)
                {
                    nacrt[j][xkonec] = 200;
                }
                else
                {
                    nacrt[j][xkonec] = 200;
                }
            }
        }


    }*/


void labirint::pisi(string kaj,int velikost,int x,int y)
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

void labirint::setarena()
{
    for(int i=0; i<12; i++)
        for(int j=0; j<18; j++)
        {
            nacrtArena[i][j] = 800;
        }

    for(int i=0; i<18; i++)
        nacrtArena[0][i] = 1000;

    for(int i=0; i<18; i++)
        nacrtArena[11][i] = 1000;

    for(int i=0; i<12; i++)
        nacrtArena[i][0] = 1000;

    for(int i=0; i<12; i++)
        nacrtArena[i][17] = 1000;


    for(int i=0; i<100; i++)
        for(int j=0; j<160; j++)
        {
            tArena[i][j]=new Tile(render);
            tArena[i][j]->init(nacrtArena[i][j]);
            tArena[i][j]->anirect.x =  tArena[i][j]->premikX*(rand()%9+7);
            tArena[i][j]->anirect.y =  tArena[i][j]->premikY*17;
        }

    for(int i=0; i<99; i++)
    {
        for(int j=1; j<160; j++)
        {
            tArena[i][j]->setx(tArena[i][j-1]->getx()+tArena[i][j]->getw());
            tArena[i][j]->sety(tArena[i][j-1]->gety());
        }
        tArena[i+1][0]->sety(tArena[i][159]->gety()+tArena[i][0]->geth());
    }

    for(int j=1; j<160; j++)
    {
        tArena[99][j]->setx(tArena[99][j-1]->getx()+tArena[99][j]->getw());
        tArena[99][j]->sety(tArena[99][j-1]->gety());
    }
}

void labirint::gameover()
{
    SDL_SetRenderDrawColor(setup->vrnirender(), 0, 0, 0, 255);


    if(vnoshighscore == false)
    {
        if(tezavnost == 1)
        {
            casigranja = SDL_GetTicks() - caszacetek;

            ofstream dat("highscore1.txt", ios::app);
            if(dat.is_open() && zmaga == true)
            {
                dat<<casigranja;
                dat<<endl;
                dat.close();

            }
            else cout<<"highscore ni vnesen"<<endl;

            ifstream dat1("highscore1.txt",ios::app);

            if(dat1.is_open())
            {
                int s[1000];
                maxcas = 10000000;
                int st=0;
                dat1.seekg(0,dat1.beg);
                while(dat1>>s[st])
                {
                    cout<<s[st]<<endl;
                    st++;
                }

                dat1.close();
                for(int i=0; i<st; i++)
                {
                    if(s[i]<maxcas)
                    {
                        maxcas=s[i];
                    }
                }
                cout<<"dela"<<endl;

                if(maxcas ==  10000000)
                    maxcas = 0;
            }
            else cout<<"bralna datoteka ni odprta"<<endl;


            vnoshighscore = true;
        }
        else if(tezavnost == 2)
        {
            casigranja = SDL_GetTicks() - caszacetek;

            ofstream dat("highscore2.txt", ios::app);
            if(dat.is_open() && zmaga == true)
            {
                dat<<casigranja;
                dat<<endl;
                dat.close();

            }
            else cout<<"highscore ni vnesen"<<endl;

            ifstream dat1("highscore2.txt",ios::app);

            if(dat1.is_open())
            {
                int s[1000];
                maxcas = 10000000;
                int st=0;
                dat1.seekg(0,dat1.beg);
                while(dat1>>s[st])
                {
                    cout<<s[st]<<endl;
                    st++;
                }

                dat1.close();
                for(int i=0; i<st; i++)
                {
                    if(s[i]<maxcas)
                    {
                        maxcas=s[i];
                    }
                }
                cout<<"dela"<<endl;

                if(maxcas ==  10000000)
                    maxcas = 0;
            }
            else cout<<"bralna datoteka ni odprta"<<endl;


            vnoshighscore = true;
        }
        else if(tezavnost == 3)
        {
            casigranja = SDL_GetTicks() - caszacetek;

            ofstream dat("highscore3.txt", ios::app);
            if(dat.is_open() && zmaga == true)
            {
                dat<<casigranja;
                dat<<endl;
                dat.close();

            }
            else cout<<"highscore ni vnesen"<<endl;

            ifstream dat1("highscore3.txt",ios::app);

            if(dat1.is_open())
            {
                int s[1000];
                maxcas = 10000000;
                int st=0;
                dat1.seekg(0,dat1.beg);
                while(dat1>>s[st])
                {
                    cout<<s[st]<<endl;
                    st++;
                }

                dat1.close();
                for(int i=0; i<st; i++)
                {
                    if(s[i]<maxcas)
                    {
                        maxcas=s[i];
                    }
                }
                cout<<"dela"<<endl;

                if(maxcas ==  10000000)
                    maxcas = 0;
            }
            else cout<<"bralna datoteka ni odprta"<<endl;


            vnoshighscore = true;
        }
    }

    int minute = 0;
    float Number = casigranja/1000;
    minute = Number/60;
    minute = floor(minute);
    string Result;
    ostringstream convert;
    convert << minute;
    Result = convert.str();

    string tmp ="TVOJ CAS IGRANJA: "+Result+"min ";
    ostringstream convert4;
    Number = Number - (minute*60);
    convert4 << Number;
    Result = convert4.str();

    tmp = tmp+Result+"s";

    pisi(tmp.c_str(),40,25,800);

    Number = maxcas/1000;
    minute = Number/60;
    minute = floor(minute);
    ostringstream convert1;
    convert1 << minute;
    Result = convert1.str();

    tmp ="NAJBOLJSI CAS IGRANJA: "+Result+"min ";

    Number = Number - (minute*60);
    ostringstream convert3;
    convert3 << Number;
    Result = convert3.str();

    tmp = tmp+Result+"s";

    pisi(tmp.c_str(),40,25,900);


    if(konec == true)
    {
        pisi("GAME OVER",60,625,400);
        pisi("IZHOD",50,1400,900);

        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX,&mouseY);
        if(mouseX>1400 && mouseY>900 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
            izhod = true;
    }
    else if(zmaga == true)
    {
        pisi("ZMAGAL SI",60,625,400);
        pisi("IZHOD",50,1400,900);

        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX,&mouseY);
        if(mouseX>1400 && mouseY>900 && setup->vrnievent()->type == SDL_MOUSEBUTTONDOWN)
            izhod = true;
    }
}

