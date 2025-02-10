#include <SFML/Graphics.hpp>
#include "GameTile.h"

#ifndef PATHTILE_H
#define PATHTILE_H

using namespace sf;
using namespace std;

const string PATH_TILE = "images/map copy.png";

class PathTile : public GameTile{
public:
    bool isPassable = true;
    PathTile(Vector2f pos);
};

#endif