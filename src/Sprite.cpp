#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderpass, string filepath, int passx, int passy, int w, int h, int anix, int aniy, int aniw, int anih)
{
    render = renderpass;

    image=IMG_LoadTexture(render,filepath.c_str());

    if (image == NULL)
    {
        cout << "slika ni nalovdana "<<filepath.c_str();
    }
    rect.x = passx;
    rect.y = passy;
    rect.w = w;
    rect.h = h;

    anirect.x = anix;
    anirect.y = aniy;
    anirect.w = aniw;
    anirect.h = anih;


}

Sprite::~Sprite()
{
    SDL_DestroyTexture(image);
}

void Sprite::staticdraw(SDL_Rect *staticxy)
{
    SDL_RenderCopy(render, image, NULL, staticxy);
}

void Sprite::draw()
{
    SDL_RenderCopy(render, image, NULL, &rect);
}

void Sprite::drawanistatic(SDL_Rect passanirect,SDL_Rect staticxy)
{
    SDL_RenderCopy(render, image, &passanirect, &staticxy);
}

void Sprite::drawani(SDL_Rect passanirect )
{
    SDL_RenderCopy(render, image, &passanirect, &rect);
}

void Sprite::setx(int xpass)
{
    rect.x=xpass;
}

void Sprite::sety(int ypass)
{
    rect.y=ypass;
}

void Sprite::setposition(int passx, int passy)
{
    x=passx;
    y=passy;
    rect.x = x;
    rect.y = y;
}

int Sprite::getx()
{
    return rect.x;
}

int Sprite::gety()
{
    return rect.y;
}
