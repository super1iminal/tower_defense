#include <SFML/Graphics.hpp>
#include "GameTile.h"

#ifndef TOWERTILE_H
#define TOWERTILE_H

using namespace sf;
using namespace std;

const string TOWER_TILE = "images/map.png";

class TowerTile : public GameTile{
public:
    bool isPassable = false;
    TowerTile(float x, float y);
};

#endif
