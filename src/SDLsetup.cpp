#include "SDLsetup.h"

SDLsetup::SDLsetup(bool *quit, int screenw, int screenh)
{
    window = NULL;
    render = NULL;
    mainevent = new SDL_Event;

    window = SDL_CreateWindow("Game window", 300, 25,
                              screenw, screenh, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        cout << "okno ne dela";
        *quit = true;
    }

    render = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED);

}

SDLsetup::~SDLsetup()
{
    SDL_DestroyWindow(window); //unici vsa okna
    SDL_DestroyRenderer(render);
    delete mainevent;
}

SDL_Renderer* SDLsetup::vrnirender()
{
    return render;
}

SDL_Event* SDLsetup::vrnievent()
{
    return mainevent;
}

void SDLsetup::start()
{
    SDL_PollEvent(mainevent);
    SDL_RenderClear(render);
}

void SDLsetup::konec()
{
    SDL_RenderPresent(render);
}
