#include <SFML/Graphics.hpp>
#include "GameTile.h"

#ifndef STUMPTILE_H
#define STUMPTILE_H

using namespace sf;
using namespace std;

const string STUMP_TILE = "images/stump16x16.png";

class StumpTile : public GameTile {
public:
    bool isPassable;
    StumpTile(float x,float y);
};

#endif