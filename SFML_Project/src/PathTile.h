#include <SFML/Graphics.hpp>
#include "GameTile.h"

#ifndef PATHTILE_H
#define PATHTILE_H

using namespace sf;
using namespace std;

class PathTile : public GameTile{
public:
    bool isPassable = true;
    PathTile(float x,float y);
};

#endif