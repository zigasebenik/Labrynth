#include "MainClass.h"
#define MAXFPS 120

MainClass::MainClass(int passscreen_w, int passscreen_h)
{
    setup = new SDLsetup(&quit, screenw, screenh);

    ResourceManager::resources.insert(make_pair("zid",IMG_LoadTexture(setup->vrnirender(),"zid.png")));
    ResourceManager::resources.insert(make_pair("soba",IMG_LoadTexture(setup->vrnirender(),"wc2tiles.png")));
    ResourceManager::resources.insert(make_pair("vrata",IMG_LoadTexture(setup->vrnirender(),"vrata.png")));
    ResourceManager::resources.insert(make_pair("boss",IMG_LoadTexture(setup->vrnirender(),"boss.png")));
    ResourceManager::resources.insert(make_pair("pot",IMG_LoadTexture(setup->vrnirender(),"pot100.png")));
    ResourceManager::resources.insert(make_pair("zid1",IMG_LoadTexture(setup->vrnirender(),"wc2tiles.png")));
    ResourceManager::resources.insert(make_pair("winter",IMG_LoadTexture(setup->vrnirender(),"wc2winter.png")));
    ResourceManager::resources.insert(make_pair("wasteland",IMG_LoadTexture(setup->vrnirender(),"wc2wastelands.png")));
    ResourceManager::resources.insert(make_pair("lava",IMG_LoadTexture(setup->vrnirender(),"lava.jpg")));
     ResourceManager::resources.insert(make_pair("zoga",IMG_LoadTexture(setup->vrnirender(),"zoga.png")));

    srand(time(NULL));
    screenw = passscreen_w;
    screenh = passscreen_h;

    TTF_Init();
    quit = false;

    dungeon = new labirint(setup->vrnirender(), screenw, screenh, setup);
    srand(time(NULL));
}

MainClass::~MainClass()
{
    TTF_Quit();
}

void MainClass::gameloop()
{
    long long deltatime=SDL_GetTicks();
    int counter=0;
    long long deltaFrameCounter = SDL_GetTicks();

    SDL_SetWindowSize(setup->window, screenw, screenh);
    srand(time(NULL));

    while (quit == false && setup->vrnievent()->type != SDL_QUIT) //okno dela
    {
        setup->start();

        dungeon->drawlabirint();
        quit = dungeon->izhod;

        deltatime=SDL_GetTicks()-deltatime;

        long long delay=1000.0/MAXFPS-deltatime;
        if(delay < 0)
            delay=0;
        SDL_Delay(delay);



        if(SDL_GetTicks()- deltaFrameCounter>=1000)
        {
            deltaFrameCounter = SDL_GetTicks();
            stringstream ss;
            ss<<counter;
            string title;
            ss>>title;
            SDL_SetWindowTitle(setup->window, title.c_str());
            counter = 0;
        }
        counter++;


        setup->konec();
        deltatime=SDL_GetTicks();
    }

}

