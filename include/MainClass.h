#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <stdlib.h>
#include <set>
#include <SDL_mixer.h>
#include <fstream>
#include <SDL_ttf.h>
#include <sstream>
#include <SDLsetup.h>
#include <ResourceManager.h>
#include <labirint.h>
#include <map>
#include <SDL_ttf.h>

using namespace std;

class labirint;
class MainClass
{
private:
    SDLsetup *setup;
    bool quit;
    int screenw, screenh;


    labirint *dungeon;

public:
    MainClass(int passscreen_w, int passscreen_h);
    ~MainClass();

    void gameloop();
};

#endif // MAINCLASS_H
