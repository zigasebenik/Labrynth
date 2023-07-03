#include "Tile.h"

Tile::Tile(SDL_Renderer* renderpass)
{
    render = renderpass;

    rect.x = 0;
    rect.y = 0;
    rect.w = 10;
    rect.h = 10;

    anirect.x = 0;
    anirect.y = 0;
    //anirect.w = 626/19;
    //anirect.h = 659/20;
    /*anirect.w = (626+20)/20;
    anirect.h = 678/20;
    premikX = anirect.w;
    premikY = anirect.h;*/

    anirect.w = (626+0)/19;
    anirect.h = 659/20;
    premikX = anirect.w+1;
    premikY = anirect.h+1;
}

Tile::~Tile()
{

}

void Tile::draw()
{
    SDL_RenderCopy(render, ResourceManager::resources[imeSlike], NULL, &rect);
}

void Tile::scale(int x,int y)
{
    SDL_Rect scale;
    scale.x = x;
    scale.y = y;
    scale.w = 100;
    scale.h = 100;
    //cout<<"scale x "<< scale.x<<endl;
    //cout<<"scale y "<< scale.y<<endl;
    SDL_RenderCopy(render, ResourceManager::resources[imeSlike], NULL, &scale);
}

void Tile::setposition(int x, int y)
{
    rect.x=x;
    rect.y=y;
}

int Tile::getx()
{
    return rect.x;
}

int Tile::gety()
{
    return rect.y;
}

int Tile::getw()
{
    return rect.w;
}

int Tile::geth()
{
    return rect.h;
}

void Tile::setx(int x)
{
    rect.x=x;
}

void Tile::sety(int y)
{
    rect.y=y;
}

SDL_Rect Tile::getrect()
{
    return rect;
}

void Tile::init(int vrsta)
{
    //vrste = 100 = zid
    //vrsta = 200 = pot

    switch(vrsta)
    {
    case 100:
        zid();
        break;
    case 200:
        pot();
        break;
    case 300:
        vrata();
        break;
    case 400:
        boss();
        break;
    case 500:
        soba();
        break;
    case 600:
        zidokolisobe();
        break;
    case 700:
        sobawinter();
        break;
    case 800:
        sobawasteland();
        break;

    case 1100:///morje == zid
        zidokolisobe();
        break;

    case 900:///morje == zid
        sobawinter();
        break;
    case 1000:///morje == zid
        sobawasteland();
        break;
    case 1200:
    {
        imeSlike  = "lava";
        if (ResourceManager::resources[imeSlike] == NULL)
        {
            cout << "slika ni nalovdana "<<endl;
        }
    }
    break;
    }
}


void Tile::zid()
{
    imeSlike  = "zid";

    if (ResourceManager::resources[imeSlike] == NULL)
    {
        cout << "slika ni nalovdana "<<endl;
    }
}

void Tile::zidokolisobe()
{
    imeSlike  = "zid1";

    if (ResourceManager::resources[imeSlike] == NULL)
    {
        cout << "slika ni nalovdana "<<endl;
    }
}

void Tile::soba()
{
    imeSlike  = "soba";

    if (ResourceManager::resources[imeSlike] == NULL)
    {
        cout << "slika ni nalovdana "<<endl;
    }
}

void Tile::pot()
{
    imeSlike  = "pot";

    if (ResourceManager::resources[imeSlike] == NULL)
    {
        cout << "slika ni nalovdana ";
    }
}

void Tile::vrata()
{
    imeSlike  = "vrata";

    if (ResourceManager::resources[imeSlike] == NULL)
    {
        cout << "slika ni nalovdana ";
    }
}


void Tile::boss()
{
    imeSlike  = "boss";

    if (ResourceManager::resources[imeSlike] == NULL)
    {
        cout << "slika ni nalovdana "<<endl;
    }
}

void Tile::sobawinter()
{
    imeSlike  = "winter";

    if (ResourceManager::resources[imeSlike] == NULL)
    {
        cout << "slika ni nalovdana "<<endl;
    }
}

void Tile::sobawasteland()
{
    imeSlike  = "wasteland";

    if (ResourceManager::resources[imeSlike] == NULL)
    {
        cout << "slika ni nalovdana "<<endl;
    }
}

void Tile::collisionzid(Hero *player, bool desno, bool levo, bool gor, bool dol)
{
    // cout <<"tile"<<rect.x<<endl;
    //cout <<"player"<<player->rect.x<<endl;

    if(desno)
        if(player->rect.x+player->rect.w>rect.x)
        {
            player->rect.x=player->rect.x-4;
            player->nastavix(player->rect.x);
            cout << "desno"<<endl;
        }

    if(levo)
        if(player->rect.x <= rect.w+rect.x)
        {
            player->rect.x=player->rect.x+4;
            player->nastavix(player->rect.x);
            cout<< "levo"<<endl;
        }

    if(gor)
        if(player->rect.y<rect.y+rect.h)
        {
            player->rect.y=player->rect.y+4;
            player->nastaviy(player->rect.y);
            cout<< "gor"<<endl;
        }

    if(dol)
        if(player->rect.y+player->rect.h>rect.y)
        {
            player->rect.y=player->rect.y-4;
            player->nastaviy(player->rect.y);
            cout<< "dol"<<endl;
        }




}

void Tile::desno(Hero* player)
{
    if(player->rect.x+player->rect.w>rect.x)
    {
        player->nastavix(player->rect.x-5);
    }
}

void Tile::levo(Hero* player)
{
    if(player->rect.x < rect.w+rect.x)
    {
        player->rect.x=player->rect.x+5;
        player->nastavix(player->rect.x);
        cout<< "levo"<<endl;
    }
}

void Tile::dol(Hero* player)
{
    if(player->rect.y<rect.h+rect.y)
    {
        player->rect.y=5;
        player->nastaviy(player->rect.y);
        cout<< "dol"<<endl;
    }
}

void Tile::gor(Hero* player)
{
    if(player->rect.y+player->rect.h>rect.h)
    {
        player->rect.y=1000-player->rect.h-5;
        player->nastaviy(player->rect.y);
        cout<< "gor"<<endl;
    }
}

void Tile::settileview(int x,int y)
{
    anirect.x = x;
    anirect.y = y;
}
