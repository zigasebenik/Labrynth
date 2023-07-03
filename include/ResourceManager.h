#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <string>
#include <SDL.h>

using namespace std;

class ResourceManager
{
public:
    static map <string, SDL_Texture*> resources;
};

#endif // RESOURCEMANAGER_H
